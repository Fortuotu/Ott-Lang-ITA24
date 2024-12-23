#include "runtime.hpp"

#include <iostream>

int Interpreter::visitBinaryExpr(BinaryExpr& expr) {
    switch (expr.op) {
    case TokenType::ADD:
        return expr.left->accept(*this) + expr.right->accept(*this);
    case TokenType::SUBTRACT:
        return expr.left->accept(*this) - expr.right->accept(*this);
    case TokenType::MULTIPLY:
        return expr.left->accept(*this) * expr.right->accept(*this);
    case TokenType::DIVIDE:
        return expr.left->accept(*this) / expr.right->accept(*this);
    default:
        return 0;
    }
}

int Interpreter::visitUnaryExpr(UnaryExpr& expr) {
    if (expr.op == TokenType::NOT) {
        return !expr.operand->accept(*this);
    } else if (expr.op == TokenType::SUBTRACT) {
        return -expr.operand->accept(*this);
    }
    return 0;
}

int Interpreter::visitLiteralExpr(LiteralExpr& expr) {
    return expr.val;
}

int Interpreter::visitGroupingExpr(GroupingExpr& expr) {
    return evalExpr(expr.expr);
}

int Interpreter::evalExpr(Expr* expr) {
    return expr->accept(*this);
}


void Interpreter::visitPrintStmt(PrintStmt& stmt) {
    std::cout << evalExpr(stmt.value) << std::endl;
}

void Interpreter::executeStmt(Stmt* stmt) {
    stmt->accept(*this);
}

void Interpreter::exec() {
    for (Stmt* stmt : ast->stmts) {
        executeStmt(stmt);
    }
}
