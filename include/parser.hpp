#pragma once

#include <vector>
#include <string>

#include "tokens.hpp"

enum class ASTNodeType {
    FUNC_DEF,

    STMT_SEQ,
    IF_STMT,
    WHILE_STMT,
    RET_STMT,
    ASSIGN_STMT,

    IDENTIFIER,
    LITERAL,

    UNARY_EXPR,
    BINARY_EXPR
};

enum class ExprOperator {
    NEGATE,

    EQUAL,
    NOT_EQUAL,
    GREATER_THAN,
    LESS_THAN,
};

struct FuncDefData {
    ASTNode *name;
    std::vector<ASTNode*> args;
    ASTNode *body;
};

struct StmtSeqData {
    std::vector<ASTNode*> children;
};

struct IfStmtData {
    ASTNode *cond;
    ASTNode *if_body;
    ASTNode *else_body;
};

struct WhileStmtData {
    ASTNode *cond;
    ASTNode *body;
};

struct RetStmtData {
    ASTNode *expr;
};

struct AssignStmtData {
    ASTNode *var;
    ASTNode *expr;
};

struct IdentifierData {
    std::string name;
};

struct LiteralData {
    std::string data;
};

struct UnaryExprData {
    ExprOperator op;
    ASTNode* oprnd;
};

struct BinaryExprData {
    ExprOperator op;
    ASTNode *oprnd1;
    ASTNode *oprnd1;
};

union ASTNodeData {
    FuncDefData func_def;
    StmtSeqData stmt_seq;
    UnaryExprData unary_expr;
    BinaryExprData bin_expr;
};

struct ASTNode {
    ASTNodeType type;
    ASTNodeData data;
};

class Parser {
private:
public:
    Parser();
    ~Parser();

    ASTNode *GenerateAST(std::vector<Token>& tokens);
};
