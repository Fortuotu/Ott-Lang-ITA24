#pragma once

#include "tokens.hpp"

struct Expr {
    
};

struct UnaryExpr : Expr {
    TokenType op;
    Expr *operand;

    UnaryExpr(TokenType opP, Expr *operandP) : op(opP), operand(operandP) {}
};

struct BinaryExpr : Expr {
    TokenType op;
    Expr *left, *right;

    BinaryExpr(TokenType opP, Expr *leftP, Expr *rightP) : op(opP), left(leftP), right(rightP) {}
};

struct LiteralExpr : Expr {
    TokenType type;
    int val;

    LiteralExpr(TokenType typeP, int valP) : type(typeP), val(valP) {}
};
