#pragma once

#include "ast.hpp"

class Interpreter : ExprVisitor, StmtVisitor {
private:
    AST* ast = nullptr;

    int evalExpr(Expr* expr);
    void executeStmt(Stmt* stmt);
public:
    Interpreter(AST* astP) : ast(astP) {}
    ~Interpreter() {}

    virtual int visitUnaryExpr(UnaryExpr& expr) override;
    virtual int visitBinaryExpr(BinaryExpr& expr) override;
    virtual int visitLiteralExpr(LiteralExpr& expr) override;
    virtual int visitGroupingExpr(GroupingExpr& expr) override;

    virtual void visitPrintStmt(PrintStmt& stmt) override;

    void exec();
};
