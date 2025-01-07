#pragma once

#include <unordered_map>

#include "compiler/ast/ast.hpp"
#include "compiler/environment/environment.hpp"

class ParseAnalyser : StmtVisitor, ExprVisitor {
private:
    Environment env;

    struct FuncInfo {
        FuncDecl* stmt;
        bool analyzed;
    };
    std::unordered_map<std::string, FuncInfo> funcs;

    void analyze_expr(Expr* expr);
    void analyze_stmt(Stmt* stmt);

    void analyze_func_decl(FuncInfo& stmt);
public:
    virtual void visit_binary_expr(BinaryExpr& expr) override;
    virtual void visit_unary_expr(UnaryExpr& expr) override;
    virtual void visit_literal_expr(LiteralExpr& expr) override;
    virtual void visit_idf_expr(IdfExpr& expr) override;
    virtual void visit_call_expr(CallExpr& expr) override;
    virtual void visit_grouping_expr(GroupingExpr& expr) override;

    virtual void visit_func_decl(FuncDecl& stmt) override;
    virtual void visit_block_stmt(BlockStmt& stmt) override;
    virtual void visit_ret_stmt(RetStmt& stmt) override;
    virtual void visit_if_stmt(IfStmt& stmt) override;
    virtual void visit_while_stmt(WhileStmt& stmt) override;
    virtual void visit_assign_stmt(AssignStmt& stmt) override;
    virtual void visit_call_stmt(CallStmt& stmt) override;
    virtual void visit_print_stmt(PrintStmt& stmt) override;

    void analyze(AST* ast);
};
