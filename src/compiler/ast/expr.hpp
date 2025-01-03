#pragma once

#include "compiler/token/token.hpp"

struct BinaryExpr;
struct UnaryExpr;
struct LiteralExpr;
struct IdfExpr;
struct CallExpr;
struct GroupingExpr;

struct ExprVisitor {
    virtual ~ExprVisitor() = default;
    virtual void visit_binary_expr(BinaryExpr& expr) = 0;
    virtual void visit_unary_expr(UnaryExpr& expr) = 0;
    virtual void visit_literal_expr(LiteralExpr& expr) = 0; 
    virtual void visit_idf_expr(IdfExpr& expr) = 0;
    virtual void visit_call_expr(CallExpr& expr) = 0;
    virtual void visit_grouping_expr(GroupingExpr& expr) = 0;
};

struct Expr {
    virtual ~Expr() = default;
    virtual void accept(ExprVisitor& visitor) = 0;
};

struct BinaryExpr : Expr {
    TokenType op;

    Expr* left_operand;
    Expr* right_operand;

    BinaryExpr(TokenType op, Expr* left_operand, Expr* right_operand)
        :
        op(op),
        left_operand(left_operand),
        right_operand(right_operand) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visit_binary_expr(*this); }
};

struct UnaryExpr : Expr {
    TokenType op;

    Expr* operand;

    UnaryExpr(TokenType op, Expr* operand) : op(op), operand(operand) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visit_unary_expr(*this); }
};

struct LiteralExpr : Expr {
    Token literal;

    LiteralExpr(Token&& literal) : literal(std::move(literal)) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visit_literal_expr(*this); }
};

struct IdfExpr : Expr {
    Token name;

    IdfExpr(Token&& name) : name(std::move(name)) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visit_idf_expr(*this); }
};

struct CallExpr : Expr {
    Token name;

    std::vector<Expr*> args;

    virtual void accept(ExprVisitor& visitor) override { visitor.visit_call_expr(*this); }
};

struct GroupingExpr : Expr {
    Expr* expr;

    GroupingExpr(Expr* expr) : expr(expr) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visit_grouping_expr(*this); }
};
