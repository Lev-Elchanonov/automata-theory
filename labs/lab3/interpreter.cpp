#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"
#include <nlohmann/json.hpp>
#include <map>
#include <ranges>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <random>

using json = nlohmann::json;

extern std::map<std::string, SymbolInfo> global_symbols_;
extern std::map<std::string, FuncDecl> functions_;



class Interpreter {
private:
    FILE* go_stdin_ = nullptr;

    std::mt19937 rng;
    std::vector<std::map<std::string, SymbolInfo>> scopes_;

    int robot_x_ = 0;
    int robot_y_ = 0;
    int drone_count_ = 0;
    bool robot_broken_ = false;
    bool robot_escaped_ = false;

    int FIELD_WIDTH_ = 0;
    int FIELD_HEIGHT_ = 0;

    std::vector<std::vector<int>> field_;

    void send_to_go(const json& cmd) const {
        if (go_stdin_) {
            std::string cmd_str = cmd.dump();
            fprintf(go_stdin_, "%s\n", cmd_str.c_str());
            fflush(go_stdin_);
        }
    }

    struct Value {
        enum Type { INT, BOOL, CELL, UNDEF, ARRAY };
        Type type_;
        int int_val_ = 0;
        bool bool_val_ = false;
        CellValue cell_val_ = CellValue::UNDEF;

        std::vector<int> array_val_;    // для дронов
        std::vector<int> dims_;
    };

    Value eval_expr(const expr_ptr& node) {
        if (!node) {
            throw std::runtime_error("Expression == NULL");
        }
        switch (node->type_) {
        case ExprNode::INT_LIT: {
            Value val;
            val.type_ = Value::INT;
            val.int_val_ = node->int_value_;
            return val;
        }
        case ExprNode::BOOL_LIT: {
            Value v;
            v.type_ = Value::BOOL;
            v.bool_val_ = node->bool_value_;
            return v;
        }

        case ExprNode::CELL_LIT: {
            Value v;
            v.type_ = Value::CELL;
            v.cell_val_ = node->cell_value_;
            return v;
        }
        case ExprNode::VAR_REF: {
            return eval_var_ref(node);
        }
        case ExprNode::ADD: {
            Value result;
            result.type_ = Value::INT;
            result.int_val_ = 0;
            for (auto& arg : node->args_) {
                result.int_val_ += eval_expr(arg).int_val_;
            }
            return result;
        }
        case ExprNode::MUL: {
            Value result;
            result.type_ = Value::INT;
            result.int_val_ = 1;
            for (auto& arg : node->args_) {
                result.int_val_ *= eval_expr(arg).int_val_;
            }
            return result;
        }
        case ExprNode::SUB: {
            Value v1 = eval_expr(node->args_[0]);
            Value v2 = eval_expr(node->args_[1]);
            Value result;
            result.type_ = Value::INT;
            result.int_val_ = v1.int_val_ - v2.int_val_;
            return result;
        }
        case ExprNode::DIV: {
            Value v1 = eval_expr(node->args_[0]);
            Value v2 = eval_expr(node->args_[1]);
            Value result;
            result.type_ = Value::INT;
            result.int_val_ = v1.int_val_ / v2.int_val_;
            return result;
        }
        case ExprNode::AND: {
            Value result;
            result.type_ = Value::BOOL;
            result.bool_val_ = true;
            for (auto& arg : node->args_) {
                if (!eval_expr(arg).bool_val_) {
                    result.bool_val_ = false;
                    break;
                }
            }
            return result;
        }
        case ExprNode::OR: {
            Value result;
            result.type_ = Value::BOOL;
            result.bool_val_ = false;
            for (auto& arg : node->args_) {
                if (eval_expr(arg).bool_val_) {
                    result.bool_val_ = true;
                    break;
                }
            }
            return result;
        }
        case ExprNode::NOT: {
            Value v = eval_expr(node->args_.front());
            Value result;
            result.type_ = Value::BOOL;
            result.bool_val_ = !v.bool_val_;
            return result;
        }
        case ExprNode::EQ: {
            Value first = eval_expr(node->args_[0]);
            Value result;
            result.type_ = Value::BOOL;
            result.bool_val_ = true;

            for (size_t i = 1; i < node->args_.size(); i++) {
                Value v = eval_expr(node->args_[i]);
                if (first.type_ != v.type_) {
                    result.bool_val_ = false;
                    break;
                }
                if (first.type_ == Value::INT && first.int_val_ != v.int_val_) {
                    result.bool_val_ = false;
                    break;
                }
                if (first.type_ == Value::BOOL && first.bool_val_ != v.bool_val_) {
                    result.bool_val_ = false;
                    break;
                }
                if (first.type_ == Value::CELL && first.cell_val_ != v.cell_val_) {
                    result.bool_val_ = false;
                    break;
                }
            }
            return result;
        }
        case ExprNode::MAX: {
            Value result = eval_expr(node->args_[0]);
            for (size_t i = 1; i < node->args_.size(); i++) {
                Value v = eval_expr(node->args_[i]);
                if (v.int_val_ > result.int_val_)
                    result = v;
            }
            return result;
        }
        case ExprNode::MIN: {
            Value result = eval_expr(node->args_[0]);
            for (size_t i = 1; i < node->args_.size(); i++) {
                Value v = eval_expr(node->args_[i]);
                if (v.int_val_ < result.int_val_)
                    result = v;
            }
            return result;
        }

        case ExprNode::SENDDRONS:
            return eval_senddrons(node);

        case ExprNode::CALL:
            return eval_call_expr(node);

        default:
            throw std::runtime_error("Unknown expression type");
        }
    }

    Value eval_var_ref(const expr_ptr& node) {
        SymbolInfo& sym = find_variable(node->var_name_);

        if (!sym.initialized_) {
            throw std::runtime_error("Variable not initialized: " + node->var_name_);
        }

        if (node->indices_.empty()) {
            Value v;
            switch (sym.decl_.type_) {
            case VarDecl::INT:
                v.type_ = Value::INT;
                v.int_val_ = sym.array_value_[0];
                break;
            case VarDecl::BOOL:
                v.type_ = Value::BOOL;
                v.bool_val_ = static_cast<bool>(sym.array_value_[0]);
                break;
            case VarDecl::CELL:
                v.type_ = Value::CELL;
                v.cell_val_ = static_cast<CellValue>(sym.array_value_[0]);
                break;
            default:
                v.type_ = Value::UNDEF;
            }
            return v;
        }

        size_t flat_index = 0;
        int multiplier = 1;

        for (size_t i = node->indices_.size() - 1; static_cast<int>(i) >= 0; i--) {
            const Value idx = eval_expr(node->indices_[i]);
            if (idx.int_val_ < 0 || idx.int_val_ >= sym.decl_.dimensions_[i]) {
                throw std::runtime_error("Index out of bounds");
            }
            flat_index += idx.int_val_ * multiplier;
            if (i > 0)
                multiplier *= sym.decl_.dimensions_[i];
        }

        if (flat_index >= sym.array_value_.size()) {
            throw std::runtime_error("Index out of bounds");
        }

        Value v;
        switch (sym.decl_.type_) {
        case VarDecl::INT:
            v.type_ = Value::INT;
            v.int_val_ = sym.array_value_[flat_index];
            break;

        case VarDecl::BOOL:
            v.type_ = Value::BOOL;
            v.bool_val_ = static_cast<bool>(sym.array_value_[flat_index]);
            break;

        case VarDecl::CELL:
            v.type_ = Value::CELL;
            v.cell_val_ = static_cast<CellValue>(sym.array_value_[flat_index]);
            break;

        default:
            v.type_ = Value::UNDEF;
        }
        return v;
    }

    Value eval_senddrons(const expr_ptr& node) {
        int num_drones = eval_expr(node->args_[0]).int_val_;

        if (drone_count_ <= 0) {
            throw std::runtime_error("No drones available");
        }
        if (num_drones > drone_count_) {
            num_drones = drone_count_;
        }

        std::uniform_int_distribution<int> dir_dist(0, 3);  // рандомная дистанция
        std::uniform_int_distribution<int> step_dist(3, 5); // рандомное количество шагов

        std::vector<json> drone_paths;

        for (int i = 0; i < num_drones; i++) {
            int dr_x = robot_x_, dr_y = robot_y_;
            int steps = step_dist(rng);

            std::vector<std::pair<int,int>> path;

            for (int s = 0; s < steps; s++) {
                int dir = dir_dist(rng);
                int nx = dr_x, ny = dr_y;

                switch (dir) {
                    case 0:
                        nx--;
                        break;
                    case 1:
                        nx++;
                        break;
                    case 2:
                        ny--;
                        break;
                    case 3:
                        ny++;
                        break;
                    default:
                        break;
                }

                if (nx >= 0 && nx < FIELD_WIDTH_ && ny >= 0 && ny < FIELD_HEIGHT_) {
                    dr_x = nx;
                    dr_y = ny;
                    path.emplace_back(dr_x, dr_y);
                }
            }

            json drone_path = json::array();
            for (auto& p : path) {
                drone_path.push_back({{"x", p.first}, {"y", p.second}});
            }

            drone_paths.push_back(drone_path);
        }

        drone_count_ -= num_drones;

        send_to_go({
            {"command", "drones_launched"},
            {"count", num_drones},
            {"drones_remaining", drone_count_},
            {"start_x", robot_x_},
            {"start_y", robot_y_},
            {"paths", drone_paths}
        });


        std::vector<int> scan(FIELD_WIDTH_ * FIELD_HEIGHT_, static_cast<int>(CellValue::UNDEF));

        for (auto& drone_path : drone_paths) {
            for (auto& p : drone_path) {
                int x = p["x"];
                int y = p["y"];
                scan[y * FIELD_WIDTH_ + x] = field_[y][x];
            }
        }

        Value result;
        result.type_ = Value::ARRAY;
        result.array_val_ = scan;
        result.dims_ = {FIELD_HEIGHT_, FIELD_WIDTH_};

        return result;
    }

    Value eval_call_expr(const expr_ptr& node) {
        const auto it = functions_.find(node->var_name_);
        if (it == functions_.end()) {
            throw std::runtime_error("Function not found: " + node->var_name_);
        }

        scopes_.emplace_back();

        execute_stmt_list(it->second.body_);

        scopes_.pop_back();

        Value v;
        v.type_ = Value::INT;
        v.int_val_ = 0;
        return v;
    }









    void assign_value(const expr_ptr& target, const Value& value) {
        auto& [decl_, array_value_, initialized_] = find_variable(target->var_name_);


        if (value.type_ == Value::ARRAY && target->indices_.empty()) {
            size_t expected_size = 1;
            for (int d : decl_.dimensions_)
                expected_size *= d;
            if (expected_size != value.array_val_.size()) {
                throw std::runtime_error("Array size mismatch in assignment");
            }

            array_value_ = value.array_val_;
            initialized_ = true;
            return;
        }
        if (decl_.type_ == VarDecl::INT && value.type_ != Value::INT)
            throw std::runtime_error("Type mismatch INT");

        if (decl_.type_ == VarDecl::BOOL && value.type_ != Value::BOOL)
            throw std::runtime_error("Type mismatch BOOL");

        if (decl_.type_ == VarDecl::CELL && value.type_ != Value::CELL)
            throw std::runtime_error("Type mismatch CELL");


        int int_val = 0;
        if (value.type_ == Value::INT) int_val = value.int_val_;
        else if (value.type_ == Value::BOOL) int_val = value.bool_val_;
        else if (value.type_ == Value::CELL) int_val = static_cast<int>(value.cell_val_);

        if (target->indices_.empty()) {
            if (array_value_.empty()) {
                array_value_.push_back(int_val);
            } else
                array_value_[0] = int_val;
        } else {
            int flat_index = 0;
            int multiplier = 1;

            for (auto i = target->indices_.size() - 1; static_cast<int>(i) >= 0; i--) {
                Value idx = eval_expr(target->indices_[i]);
                flat_index += idx.int_val_ * multiplier;
                if (i > 0)
                    multiplier *= decl_.dimensions_[i];
            }

            array_value_[flat_index] = int_val;
        }

        initialized_ = true;
    }


    void execute_stmt(const stmt_ptr& stmt) {
        if (!stmt || robot_broken_ || robot_escaped_) return;

        switch (stmt->type_) {
        case StmtNode::ASSIGN: {
            Value val = eval_expr(stmt->value_);
            for (auto& target : stmt->targets_) {
                assign_value(target, val);
            }
            break;
        }

        case StmtNode::WHILE: {
            while (!robot_broken_ && !robot_escaped_) {
                Value cond = eval_expr(stmt->while_cond_);
                if (!cond.bool_val_) break;
                execute_stmt_list(stmt->while_body_);
            }
            break;
        }

        case StmtNode::SWITCH: {
            for (auto& case_branch : stmt->switch_cases_) {
                Value cond = eval_expr(case_branch.condition_);
                if (cond.bool_val_) {
                    execute_stmt_list(case_branch.body_);
                    break;
                }
            }
            break;
        }

        case StmtNode::MOVE:
            execute_move(stmt);
            break;

        case StmtNode::CALL:
            execute_call(stmt);
            break;

        case StmtNode::GETDRONSCOUNT:
            execute_getdronscount(stmt);
            break;

        case StmtNode::EXPR:
            if (stmt->expr_val_ && stmt->expr_val_->var_name_ == "__vardecl__") {
            } else {
                eval_expr(stmt->expr_val_);
            }
            break;

        case StmtNode::VARDECL:
            for (const auto& decl : stmt->var_decls_) {
                SymbolInfo info;
                info.decl_ = decl;
                scopes_.back()[decl.name_] = info;
            }
            break;
        }
    }

    void execute_stmt_list(std::vector<stmt_ptr>& stmts) {
        for (const auto& stmt : stmts) {
            if (robot_broken_ || robot_escaped_) break;
            execute_stmt(stmt);
        }
    }

    void execute_move(const stmt_ptr& stmt) {
        int distance = eval_expr(stmt->distance_).int_val_;
        int dx = 0, dy = 0;
        std::string dir_name;

        switch (stmt->direction_) {
            case StmtNode::LEFT:
                dx = -1;
                dir_name = "left";
                break;
            case StmtNode::RIGHT:
                dx = 1;
                dir_name = "right";
                break;
            case StmtNode::UP:
                dy = -1;
                dir_name = "up";
                break;
            case StmtNode::DOWN:
                dy = 1;
                dir_name = "down";
                break;
        }

        for (int i = 0; i < distance; i++) {
            int new_x = robot_x_ + dx;
            int new_y = robot_y_ + dy;

            if (new_x < 0 || new_x >= FIELD_WIDTH_ || new_y < 0 || new_y >= FIELD_HEIGHT_) {
                send_to_go({
                    {"command", "robot_status"},
                    {"status", "broken"},
                    {"x", robot_x_},
                    {"y", robot_y_},
                    {"message", "Hit the boundary wall"}
                });

                std::cout << "Robot hit the boundary and broke at ("
                          << robot_x_ << "," << robot_y_ << ")!" << std::endl;
                robot_broken_ = true;
                return;
            }

            if (field_[new_y][new_x] == 1) {
                send_to_go({
                    {"command", "robot_status"},
                    {"status", "broken"},
                    {"x", robot_x_},
                    {"y", robot_y_},
                    {"message", "Hit a wall"}
                });

                std::cout << "Robot hit a wall and broke at (" << robot_x_ << "," << robot_y_ << ")!" << std::endl;
                robot_broken_ = true;
                return;
            }

            robot_x_ = new_x;
            robot_y_ = new_y;

            send_to_go({
                {"command", "robot_move"},
                {"x", robot_x_},
                {"y", robot_y_},
                {"direction", dir_name}
            });

            std::cout << "Robot moved to (" << robot_x_ << "," << robot_y_ << ")" << std::endl;

            if (field_[robot_y_][robot_x_] == 2) {
                send_to_go({
                    {"command", "robot_status"},
                    {"status", "exit_found"},
                    {"x", robot_x_},
                    {"y", robot_y_},
                    {"message", "Exit found!"}
                });
                robot_escaped_ = true;
                std::cout << "Robot found the exit! Success!" << std::endl;
                return;
            }
        }
    }

    void execute_call(const stmt_ptr& stmt) {
        auto it = functions_.find(stmt->call_name_);

        std::cout << "Calling function: " << stmt->call_name_ << std::endl;

        send_to_go({
            {"command", "function_call"},
            {"name", stmt->call_name_}
        });

        scopes_.emplace_back();

        execute_stmt_list(it->second.body_);

        scopes_.pop_back();
    }

    void execute_getdronscount(const stmt_ptr& stmt) {
        Value v;
        v.type_ = Value::INT;
        v.int_val_ = drone_count_;
        assign_value(stmt->dron_target_, v);

        send_to_go({
            {"command", "drone_count_queried"},
            {"count", drone_count_}
        });
    }

public:
    explicit Interpreter(FILE* go_stdin = nullptr)
        : go_stdin_(go_stdin), rng(std::random_device{}()) {

        load_field("map.txt");

        json field_json = json::array();
        for (int y = 0; y < FIELD_HEIGHT_; y++) {
            json row = json::array();
            for (int x = 0; x < FIELD_WIDTH_; x++) {
                row.push_back(field_[y][x]);
            }
            field_json.push_back(row);
        }

        scopes_.emplace_back();
        send_to_go({
            {"command", "init"},
            {"width", FIELD_WIDTH_},
            {"height", FIELD_HEIGHT_},
            {"field", field_json},
            {"robot_x", robot_x_},
            {"robot_y", robot_y_},
            {"drone_count", drone_count_}
        });

        std::cout << "Interpreter initialized. Field: " << FIELD_WIDTH_ << "x"
                  << FIELD_HEIGHT_ << ", Drones: " << drone_count_
                  << ", Robot at: (0,0)" << std::endl;
    }

    void initialize_variables() {
        for (auto& [name_, sym_] : global_symbols_) {
            if (!sym_.decl_.init_values_.empty()) {
                if (sym_.decl_.dimensions_.empty()) {
                    Value v = eval_expr(sym_.decl_.init_values_[0]);
                    sym_.array_value_.push_back(v.int_val_);
                } else {
                    for (auto& init_expr : sym_.decl_.init_values_) {
                        Value v = eval_expr(init_expr);
                        sym_.array_value_.push_back(v.int_val_);
                    }
                }
                sym_.initialized_ = true;
            } else {
                if (sym_.decl_.dimensions_.empty()) {
                    sym_.array_value_.push_back(0);
                } else {
                    int total_size = 1;
                    for (const int dim : sym_.decl_.dimensions_) {
                        total_size *= dim;
                    }
                    sym_.array_value_.resize(total_size, 0);
                }
            }
        }
    }

    void run() {
        const auto it = functions_.find("main");
        if (it == functions_.end()) {
            throw std::runtime_error("No 'main' function found");
        }

        std::cout << "\n=== STARTING PROGRAM EXECUTION ===" << std::endl;

        send_to_go({{"command", "start"}});


        execute_stmt_list(it->second.body_);

        std::cout << "=== PROGRAM EXECUTION FINISHED ===" << std::endl;

        send_to_go({
            {"command", "finished"},
            {"robot_broken", robot_broken_},
            {"final_x", robot_x_},
            {"final_y", robot_y_},
            {"drones_remaining", drone_count_}
        });

        if (!robot_broken_) {
            std::cout << "Final robot position: (" << robot_x_ << "," << robot_y_ << ")" << std::endl;
            std::cout << "Drones remaining: " << drone_count_ << std::endl;
        }
    }
    void load_field(const std::string& filename) {
        std::ifstream file(filename);
        file >> FIELD_HEIGHT_;
        file >> FIELD_WIDTH_;
        file >> robot_x_;
        file >> robot_y_;
        file >> drone_count_;
        field_.resize(FIELD_HEIGHT_, std::vector<int>(FIELD_WIDTH_));
        for (int y = 0; y < FIELD_HEIGHT_; y++) {
            for (int x = 0; x < FIELD_WIDTH_; x++) {
                file >> field_[y][x];
            }
        }
    }

    SymbolInfo& find_variable(const std::string& name) {
        for (auto & scope : std::ranges::reverse_view(scopes_)) {
            auto found = scope.find(name);
            if (found != scope.end()) {
                return found->second;
            }
        }
        auto found = global_symbols_.find(name);
        if (found != global_symbols_.end()) {
            return found->second;
        }
        throw std::runtime_error("Undefined variable: " + name);
    }
};


#endif