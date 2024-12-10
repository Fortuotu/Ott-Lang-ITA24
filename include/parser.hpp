#pragma once

#include <vector>
#include <string>

#include "tokens.hpp"

enum class ASTNodeType {
    ROOT,

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

struct ASTNode;

struct FuncDefData {
    ASTNode *name;
    std::vector<ASTNode*> args;
    ASTNode *body;
};

struct RootData {
    ASTNode *next;
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
    ASTNode *oprnd;
};

union ASTNodeData {
    RootData root;
    FuncDefData func_def;

    StmtSeqData stmt_seq;
    IfStmtData if_stmt;
    WhileStmtData while_stmt;
    RetStmtData ret_stmt;
    AssignStmtData assign_stmt;

    IdentifierData idfier;
    LiteralData lit;

    UnaryExprData unary_expr;
    BinaryExprData bin_expr;

    ASTNodeData() {}
    ~ASTNodeData() {}
};

struct ASTNode {
    ASTNodeType type;
    ASTNodeData data;

    ASTNode(ASTNodeType typeP) : type(typeP) {}
    ASTNode() {}
    ~ASTNode() {}
};

class Parser {
private:
public:
    Parser();
    ~Parser();

    ASTNode *GenerateAST(std::vector<Token>& tokens);
};
