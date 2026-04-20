#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <variant>

// Forward declaration
struct ExprNode;
using expr_ptr = std::shared_ptr<ExprNode>;

enum class CellValue {
    EMPTY = 0,
    WALL = 1,
    EXIT = 2,
    UNDEF = 3
};

// Узел выражения
struct ExprNode {
    enum Type {
        INT_LIT, BOOL_LIT, CELL_LIT,
        VAR_REF,
        CALL,
        ADD, MUL, SUB, DIV,
        AND, OR, NOT,
        EQ, MAX, MIN,
        SENDDRONS
    };
    Type type_;

    int int_value_ = 0;
    bool bool_value_ = false;
    CellValue cell_value_ = CellValue::UNDEF;

    std::string var_name_;
    std::vector<expr_ptr> indices_;
    std::vector<expr_ptr> args_;

    ExprNode(Type t) : type_(t) {}

    static expr_ptr make_int(int val) {
        auto node = std::make_shared<ExprNode>(INT_LIT);
        node->int_value_ = val;
        return node;
    }
    static expr_ptr make_bool(bool val) {
        auto node = std::make_shared<ExprNode>(BOOL_LIT);
        node->bool_value_ = val;
        return node;
    }
    static expr_ptr make_cell(CellValue val) {
        auto node = std::make_shared<ExprNode>(CELL_LIT);
        node->cell_value_ = val;
        return node;
    }
    static expr_ptr make_var_ref(const std::string& name) {
        auto node = std::make_shared<ExprNode>(VAR_REF);
        node->var_name_ = name;
        return node;
    }
};

// Описание переменной
struct VarDecl {
    std::string name_;
    bool is_const_ = false;
    enum VarType { INT, BOOL, CELL, UNDEF }
    type_ = UNDEF;
    std::vector<int> dimensions_;
    std::vector<expr_ptr> init_values_;

    VarDecl() = default;
    VarDecl(const std::string& n, bool c, VarType t) : name_(n), is_const_(c), type_(t) {}
};

// Forward declaration
struct StmtNode;
using stmt_ptr = std::shared_ptr<StmtNode>;

struct ConditionBranch {
    expr_ptr condition;
    std::vector<stmt_ptr> body;
};

struct StmtNode {
    enum Type {
        ASSIGN,
        WHILE,
        SWITCH,
        MOVE,
        CALL,
        GETDRONSCOUNT,
        EXPR
    };
    Type type_;

    // ASSIGN
    expr_ptr value_;
    std::vector<expr_ptr> targets_;

    // WHILE
    expr_ptr while_cond_;
    std::vector<stmt_ptr> while_body_;

    // SWITCH
    std::vector<ConditionBranch> switch_cases_;

    // MOVE
    enum Direction { LEFT, RIGHT, UP, DOWN };
    Direction direction_;
    expr_ptr distance_;

    // CALL
    std::string call_name_;

    // GETDRONSCOUNT
    expr_ptr dron_target_;

    // EXPR
    expr_ptr expr_val_;

    StmtNode(Type t) : type_(t) {}
};

struct FuncDecl {
    std::string name_;
    std::vector<stmt_ptr> body_;
    bool is_main_ = false;
};

#endif