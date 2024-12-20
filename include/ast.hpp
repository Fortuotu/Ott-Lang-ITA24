#pragma once

#include "tokens.hpp"

struct ASTNode {
    virtual TokenType GetType() { return TokenType::TOKENS_END; }
};

struct UnaryExpr : ASTNode {
    TokenType op;
    ASTNode *operand;

    UnaryExpr(TokenType opP, ASTNode *operandP) : op(opP), operand(operandP) {}
    TokenType GetType() override { return op; }
};

struct BinaryExpr : ASTNode {
    TokenType op;
    ASTNode *left, *right;

    BinaryExpr(TokenType opP, ASTNode *leftP, ASTNode *rightP) : op(opP), left(leftP), right(rightP) {}
    TokenType GetType() override { return op; }
};

struct LiteralExpr : ASTNode {
    TokenType type;
    int val;

    LiteralExpr(TokenType typeP, int valP) : type(typeP), val(valP) {}
    TokenType GetType() override { return type; }
};
