#pragma once

#include "tokens.hpp"

struct UnaryExpr;
struct BinaryExpr;
struct LiteralExpr;
struct GroupingExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual int visitUnaryExpr(UnaryExpr& expr) = 0;
    virtual int visitBinaryExpr(BinaryExpr& expr) = 0;
    virtual int visitLiteralExpr(LiteralExpr& expr) = 0;
    virtual int visitGroupingExpr(GroupingExpr& expr) = 0;
};

struct PrintStmt;

class StmtVisitor {
public:
    virtual ~StmtVisitor() = default;
    virtual void visitPrintStmt(PrintStmt& stmt) = 0;
};

struct ASTNode {};

struct Expr : ASTNode {
    virtual int accept(ExprVisitor& visitor) = 0;
};

struct UnaryExpr : Expr {
    TokenType op;
    Expr *operand;

    UnaryExpr(TokenType opP, Expr *operandP) : op(opP), operand(operandP) {}

    virtual int accept(ExprVisitor& visitor) override { return visitor.visitUnaryExpr(*this); }
};

struct BinaryExpr : Expr {
    TokenType op;
    Expr *left, *right;

    BinaryExpr(TokenType opP, Expr *leftP, Expr *rightP) : op(opP), left(leftP), right(rightP) {}

    virtual int accept(ExprVisitor& visitor) override { return visitor.visitBinaryExpr(*this); };
};

struct LiteralExpr : Expr {
    TokenType type;
    int val;

    LiteralExpr(TokenType typeP, int valP) : type(typeP), val(valP) {}

    virtual int accept(ExprVisitor& visitor) override { return visitor.visitLiteralExpr(*this); };
};

struct GroupingExpr : Expr {
    Expr* expr;

    GroupingExpr(Expr* exprP) : expr(exprP) {}

    virtual int accept(ExprVisitor& visitor) override { return visitor.visitGroupingExpr(*this); };
};

// For debugging syntax trees.
class ExprPrinter : ExprVisitor {
private:
    std::string buf;
    std::string temp;
    
    void space();
public:
    virtual int visitUnaryExpr(UnaryExpr& expr) override;
    virtual int visitBinaryExpr(BinaryExpr& expr) override;
    virtual int visitLiteralExpr(LiteralExpr& expr) override;
    virtual int visitGroupingExpr(GroupingExpr& expr) override;

    ExprPrinter() {}
    ~ExprPrinter() {}

    void print(Expr* expr);
};

struct Stmt {};

struct PrintStmt : Stmt {
    Expr* value;

    PrintStmt(Expr* valueP) : value(valueP) {}
};

struct AST {
    std::vector<Stmt*> stmts;
};
