#pragma once

#include <vector>

#include "compiler/token/token.hpp"

struct Expr;

struct FuncDecl;
struct BlockStmt;
struct RetStmt;
struct IfStmt;
struct AssignStmt;
struct CallStmt;

struct StmtVisitor {
    virtual ~StmtVisitor() = default;
    virtual void visit_func_decl(FuncDecl& stmt) = 0;
    virtual void visit_block_stmt(BlockStmt& stmt) = 0;
    virtual void visit_ret_stmt(RetStmt& stmt) = 0;
    virtual void visit_if_stmt(IfStmt& stmt) = 0;
    virtual void visit_assign_stmt(AssignStmt& stmt) = 0;
    virtual void visit_call_stmt(CallStmt& stmt) = 0;
};

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor& visitor) = 0;
};

struct FuncDecl : Stmt {
    Token name;
    std::vector<Token> params;

    BlockStmt* body;

    virtual void accept(StmtVisitor& visitor) override { visitor.visit_func_decl(*this); }
};

struct BlockStmt : Stmt {
    std::vector<Stmt*> stmts;

    virtual void accept(StmtVisitor& visitor) override { visitor.visit_block_stmt(*this); }
};

struct RetStmt : Stmt {
    Expr* val;

    virtual void accept(StmtVisitor& visitor) override { visitor.visit_ret_stmt(*this); }
};

struct IfStmt : Stmt {
    Expr* cond;
    BlockStmt* body;

    virtual void accept(StmtVisitor& visitor) override { visitor.visit_if_stmt(*this); }
};

struct AssignStmt : Stmt {
    Token left_operand;
    Expr* right_operand;

    virtual void accept(StmtVisitor& visitor) override { visitor.visit_assign_stmt(*this); }
};

struct CallStmt : Stmt {
    Token name;
    std::vector<Expr*> args;

    virtual void accept(StmtVisitor& visitor) override { visitor.visit_call_stmt(*this); }
};
