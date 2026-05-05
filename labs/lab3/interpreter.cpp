#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "ast.hpp"
#include <nlohmann/json.hpp>
#include <map>
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

extern std::map<std::string, struct SymbolInfo> global_symbols;
extern std::map<std::string, FuncDecl> functions;



class Interpreter {
private:
    FILE* go_stdin = nullptr;

    std::mt19937 rng;
    std::vector<std::map<std::string, SymbolInfo>> scopes_;

    int robot_x = 0;
    int robot_y = 0;
    int drone_count = 100;
    bool robot_broken = false;
    bool robot_escaped = false;

    int FIELD_WIDTH = 10;
    int FIELD_HEIGHT = 10;

    std::vector<std::vector<int>> field;

    void send_to_go(const json& cmd) const {
        if (go_stdin) {
            std::string cmd_str = cmd.dump();
            fprintf(go_stdin, "%s\n", cmd_str.c_str());
            fflush(go_stdin);
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
    Value eval_expr(expr_ptr node) {
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

    Value eval_var_ref(expr_ptr node) {
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

        int flat_index = 0;
        int multiplier = 1;

        for (int i = node->indices_.size() - 1; i >= 0; i--) {
            Value idx = eval_expr(node->indices_[i]);
            if (idx.int_val_ < 0 || idx.int_val_ >= sym.decl_.dimensions_[i]) {
                throw std::runtime_error("Index out of bounds");
            }
            flat_index += idx.int_val_ * multiplier;
            if (i > 0)
                multiplier *= sym.decl_.dimensions_[i];
        }

        if (flat_index < 0 || flat_index >= sym.array_value_.size()) {
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

    Value eval_senddrons(expr_ptr node) {
        int num_drones = eval_expr(node->args_[0]).int_val_;

        if (drone_count <= 0) {
            throw std::runtime_error("No drones available");
        }
        if (num_drones > drone_count) {
            num_drones = drone_count;
        }

        std::uniform_int_distribution<int> dir_dist(0, 3);  // рандомная дистанция
        std::uniform_int_distribution<int> step_dist(3, 5); // рандомное количество шагов

        std::vector<json> drone_paths;

        for (int i = 0; i < num_drones; i++) {
            int dr_x = robot_x, dr_y = robot_y;
            int steps = step_dist(rng);

            std::vector<std::pair<int,int>> path;

            for (int s = 0; s < steps; s++) {
                int dir = dir_dist(rng);
                int nx = dr_x, ny = dr_y;

                switch (dir) {
                case 0: nx--; break;
                case 1: nx++; break;
                case 2: ny--; break;
                case 3: ny++; break;
                }

                if (nx >= 0 && nx < FIELD_WIDTH &&
                    ny >= 0 && ny < FIELD_HEIGHT) {
                    dr_x = nx;
                    dr_y = ny;
                    path.push_back({dr_x, dr_y});
                }
            }

            json drone_path = json::array();
            for (auto& p : path) {
                drone_path.push_back({{"x", p.first}, {"y", p.second}});
            }

            drone_paths.push_back(drone_path);
        }

        drone_count -= num_drones;

        send_to_go({
            {"command", "drones_launched"},
            {"count", num_drones},
            {"drones_remaining", drone_count},
            {"start_x", robot_x},
            {"start_y", robot_y},
            {"paths", drone_paths}
        });


        std::vector<int> scan(FIELD_WIDTH * FIELD_HEIGHT, static_cast<int>(CellValue::UNDEF));

        for (auto& drone_path : drone_paths) {
            for (auto& p : drone_path) {
                int x = p["x"];
                int y = p["y"];
                scan[y * FIELD_WIDTH + x] = field[y][x];
            }
        }

        Value result;
        result.type_ = Value::ARRAY;
        result.array_val_ = scan;
        result.dims_ = {FIELD_HEIGHT, FIELD_WIDTH};

        return result;
    }

    Value eval_call_expr(expr_ptr node) {
        auto it = functions.find(node->var_name_);
        if (it == functions.end()) {
            throw std::runtime_error("Function not found: " + node->var_name_);
        }

        scopes_.push_back({});

        execute_stmt_list(it->second.body_);

        // удаляем область
        scopes_.pop_back();

        Value v;
        v.type_ = Value::INT;
        v.int_val_ = 0;
        return v;
    }









    void assign_value(expr_ptr target, const Value& value) {
        SymbolInfo& sym = find_variable(target->var_name_);


        if (value.type_ == Value::ARRAY && target->indices_.empty()) {
            int expected_size = 1;
            for (int d : sym.decl_.dimensions_)
                expected_size *= d;
            if (expected_size != value.array_val_.size()) {
                throw std::runtime_error("Array size mismatch in assignment");
            }

            sym.array_value_ = value.array_val_;
            sym.initialized_ = true;
            return;
        }
        if (sym.decl_.type_ == VarDecl::INT && value.type_ != Value::INT)
            throw std::runtime_error("Type mismatch INT");

        if (sym.decl_.type_ == VarDecl::BOOL && value.type_ != Value::BOOL)
            throw std::runtime_error("Type mismatch BOOL");

        if (sym.decl_.type_ == VarDecl::CELL && value.type_ != Value::CELL)
            throw std::runtime_error("Type mismatch CELL");


        int int_val = 0;
        if (value.type_ == Value::INT) int_val = value.int_val_;
        else if (value.type_ == Value::BOOL) int_val = value.bool_val_;
        else if (value.type_ == Value::CELL) int_val = (int)value.cell_val_;

        if (target->indices_.empty()) {
            if (sym.array_value_.empty()) {
                sym.array_value_.push_back(int_val);
            } else
                sym.array_value_[0] = int_val;
        } else {
            int flat_index = 0;
            int multiplier = 1;

            for (int i = target->indices_.size() - 1; i >= 0; i--) {
                Value idx = eval_expr(target->indices_[i]);
                flat_index += idx.int_val_ * multiplier;
                if (i > 0)
                    multiplier *= sym.decl_.dimensions_[i];
            }

            sym.array_value_[flat_index] = int_val;
        }

        sym.initialized_ = true;
    }


    void execute_stmt(stmt_ptr stmt) {
        if (!stmt || robot_broken || robot_escaped) return;

        switch (stmt->type_) {
        case StmtNode::ASSIGN: {
            Value val = eval_expr(stmt->value_);
            for (auto& target : stmt->targets_) {
                assign_value(target, val);
            }
            break;
        }

        case StmtNode::WHILE: {
            while (!robot_broken && !robot_escaped) {
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
        for (auto stmt : stmts) {
            if (robot_broken || robot_escaped) break;
            execute_stmt(stmt);
        }
    }

    void execute_move(stmt_ptr stmt) {
        int distance = eval_expr(stmt->distance_).int_val_;
        int dx = 0, dy = 0;
        std::string dir_name;

        switch (stmt->direction_) {
            case StmtNode::LEFT:  dx = -1; dir_name = "left"; break;
            case StmtNode::RIGHT: dx = 1;  dir_name = "right"; break;
            case StmtNode::UP:    dy = -1; dir_name = "up"; break;
            case StmtNode::DOWN:  dy = 1;  dir_name = "down"; break;
        }

        for (int i = 0; i < distance; i++) {
            int new_x = robot_x + dx;
            int new_y = robot_y + dy;

            if (new_x < 0 || new_x >= FIELD_WIDTH ||
                new_y < 0 || new_y >= FIELD_HEIGHT) {

                send_to_go({
                    {"command", "robot_status"},
                    {"status", "broken"},
                    {"x", robot_x},
                    {"y", robot_y},
                    {"message", "Hit the boundary wall"}
                });

                std::cout << "Robot hit the boundary and broke at ("
                          << robot_x << "," << robot_y << ")!" << std::endl;
                robot_broken = true;
                return;
            }

            if (field[new_y][new_x] == 1) {
                send_to_go({
                    {"command", "robot_status"},
                    {"status", "broken"},
                    {"x", robot_x},
                    {"y", robot_y},
                    {"message", "Hit a wall"}
                });

                std::cout << "Robot hit a wall and broke at ("
                          << robot_x << "," << robot_y << ")!" << std::endl;
                robot_broken = true;
                return;
            }

            robot_x = new_x;
            robot_y = new_y;

            send_to_go({
                {"command", "robot_move"},
                {"x", robot_x},
                {"y", robot_y},
                {"direction", dir_name}
            });

            std::cout << "Robot moved to (" << robot_x << ","
                      << robot_y << ")" << std::endl;

            if (field[robot_y][robot_x] == 2) {
                send_to_go({
                    {"command", "robot_status"},
                    {"status", "exit_found"},
                    {"x", robot_x},
                    {"y", robot_y},
                    {"message", "Exit found!"}
                });
                robot_escaped = true;
                std::cout << "Robot found the exit! Success!" << std::endl;
                return;
            }
        }
    }

    void execute_call(stmt_ptr stmt) {
        auto it = functions.find(stmt->call_name_);

        std::cout << "Calling function: " << stmt->call_name_ << std::endl;

        send_to_go({
            {"command", "function_call"},
            {"name", stmt->call_name_}
        });

        scopes_.push_back({});
        for (auto& s : it->second.body_) {
            if (s->type_ == StmtNode::EXPR && s->expr_val_ &&
                s->expr_val_->var_name_ == "__vardecl__") {
                // Пропускаем (объявления уже в scopes_.back())
                }
        }

        execute_stmt_list(it->second.body_);

        scopes_.pop_back();
    }

    void execute_getdronscount(stmt_ptr stmt) {
        Value v;
        v.type_ = Value::INT;
        v.int_val_ = drone_count;
        assign_value(stmt->dron_target_, v);

        send_to_go({
            {"command", "drone_count_queried"},
            {"count", drone_count}
        });
    }

public:
    Interpreter(FILE* go_stdin = nullptr)
        : go_stdin(go_stdin), rng(std::random_device{}()) {

        load_field("map.txt");

        json field_json = json::array();
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            json row = json::array();
            for (int x = 0; x < FIELD_WIDTH; x++) {
                row.push_back(field[y][x]);
            }
            field_json.push_back(row);
        }

        scopes_.push_back({});
        send_to_go({
            {"command", "init"},
            {"width", FIELD_WIDTH},
            {"height", FIELD_HEIGHT},
            {"field", field_json},
            {"robot_x", robot_x},
            {"robot_y", robot_y},
            {"drone_count", drone_count}
        });

        std::cout << "Interpreter initialized. Field: " << FIELD_WIDTH << "x"
                  << FIELD_HEIGHT << ", Drones: " << drone_count
                  << ", Robot at: (0,0)" << std::endl;
    }

    void initialize_variables() {
        for (auto& [name, sym] : global_symbols) {
            if (!sym.decl_.init_values_.empty()) {
                if (sym.decl_.dimensions_.empty()) {
                    Value v = eval_expr(sym.decl_.init_values_[0]);
                    sym.array_value_.push_back(v.int_val_);
                } else {
                    for (auto& init_expr : sym.decl_.init_values_) {
                        Value v = eval_expr(init_expr);
                        sym.array_value_.push_back(v.int_val_);
                    }
                }
                sym.initialized_ = true;
            } else {
                if (sym.decl_.dimensions_.empty()) {
                    sym.array_value_.push_back(0);
                } else {
                    int total_size = 1;
                    for (int dim : sym.decl_.dimensions_) {
                        total_size *= dim;
                    }
                    sym.array_value_.resize(total_size, 0);
                }
            }
        }
    }

    void run() {
        auto it = functions.find("main");
        if (it == functions.end()) {
            throw std::runtime_error("No 'main' function found");
        }

        std::cout << "\n=== STARTING PROGRAM EXECUTION ===" << std::endl;

        send_to_go({{"command", "start"}});


        execute_stmt_list(it->second.body_);

        std::cout << "=== PROGRAM EXECUTION FINISHED ===" << std::endl;

        send_to_go({
            {"command", "finished"},
            {"robot_broken", robot_broken},
            {"final_x", robot_x},
            {"final_y", robot_y},
            {"drones_remaining", drone_count}
        });

        if (!robot_broken) {
            std::cout << "Final robot position: (" << robot_x << "," << robot_y << ")" << std::endl;
            std::cout << "Drones remaining: " << drone_count << std::endl;
        }
    }
    void load_field(const std::string& filename) {
        std::ifstream file(filename);
        file >> FIELD_HEIGHT;
        file >> FIELD_WIDTH;
        file >> robot_x;
        file >> robot_y;
        field.resize(FIELD_HEIGHT, std::vector<int>(FIELD_WIDTH));
        for (int y = 0; y < FIELD_HEIGHT; y++) {
            for (int x = 0; x < FIELD_WIDTH; x++) {
                file >> field[y][x];
            }
        }
    }

    SymbolInfo& find_variable(const std::string& name) {
        for (auto it = scopes_.rbegin(); it != scopes_.rend(); ++it) {
            auto found = it->find(name);
            if (found != it->end()) {
                return found->second;
            }
        }
        auto found = global_symbols.find(name);
        if (found != global_symbols.end()) {
            return found->second;
        }
        throw std::runtime_error("Undefined variable: " + name);
    }
};


#endif