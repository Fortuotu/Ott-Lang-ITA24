#pragma once

#include "tokens.hpp"

struct UnaryExpr;
struct BinaryExpr;
struct LiteralExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual void visitUnaryExpr(UnaryExpr& expr) = 0;
    virtual void visitBinaryExpr(BinaryExpr& expr) = 0;
    virtual void visitLiteralExpr(LiteralExpr& expr) = 0;
};

struct ASTNode {
    virtual TokenType GetType() = 0;
};

struct Expr : ASTNode {
    virtual void accept(ExprVisitor& visitor) = 0;
};

struct UnaryExpr : Expr {
    TokenType op;
    Expr *operand;

    UnaryExpr(TokenType opP, Expr *operandP) : op(opP), operand(operandP) {}
    TokenType GetType() override { return op; }

    virtual void accept(ExprVisitor& visitor) override { visitor.visitUnaryExpr(*this); }
};

struct BinaryExpr : Expr {
    TokenType op;
    Expr *left, *right;

    BinaryExpr(TokenType opP, Expr *leftP, Expr *rightP) : op(opP), left(leftP), right(rightP) {}
    TokenType GetType() override { return op; }

    virtual void accept(ExprVisitor& visitor) override { visitor.visitBinaryExpr(*this); };
};

struct LiteralExpr : Expr {
    TokenType type;
    int val;

    LiteralExpr(TokenType typeP, int valP) : type(typeP), val(valP) {}
    TokenType GetType() override { return type; }

    virtual void accept(ExprVisitor& visitor) override { visitor.visitLiteralExpr(*this); };
};

class ExprPrinter : ExprVisitor {
private:
    std::string buf;
    std::string temp;
    
    void space();
public:
    void visitUnaryExpr(UnaryExpr& expr) override;
    void visitBinaryExpr(BinaryExpr& expr) override;
    void visitLiteralExpr(LiteralExpr& expr) override;

    ExprPrinter() {}
    ~ExprPrinter() {}

    void print(Expr* expr);
};
