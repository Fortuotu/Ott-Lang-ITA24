#pragma once

#include "ast.hpp"

class Interpreter : ExprVisitor, StmtVisitor {
public:
    Interpreter() {}
    ~Interpreter() {}

    virtual int visitUnaryExpr(UnaryExpr& expr) override;
    virtual int visitBinaryExpr(BinaryExpr& expr) override;
    virtual int visitLiteralExpr(LiteralExpr& expr) override;
    virtual int visitGroupingExpr(GroupingExpr& expr) override;

    int evalExpr(Expr* expr);

    virtual void visitPrintStmt(PrintStmt& stmt) override;

    void executeStmt(Stmt& stmt);
};
