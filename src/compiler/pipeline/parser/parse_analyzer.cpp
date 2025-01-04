#include "parse_analyzer.hpp"

void ParseAnalyser::analyze(AST* ast) {
    for (Stmt* stmt : ast->stmts) {
        analyze_stmt(stmt);
    }

    for (FuncDecl* func : funcs) {
        env.start_scope_with(func->params);
        analyze_stmt(func->body);
        env.end_scope();
    }
}

void ParseAnalyser::analyze_expr(Expr* expr) {
    expr->accept(*this);
}

void ParseAnalyser::analyze_stmt(Stmt* stmt) {
    stmt->accept(*this);
}

void ParseAnalyser::visit_binary_expr(BinaryExpr& expr) {
    analyze_expr(expr.left_operand);
    analyze_expr(expr.right_operand);
}

void ParseAnalyser::visit_unary_expr(UnaryExpr& expr) {
    analyze_expr(expr.operand);
}

void ParseAnalyser::visit_literal_expr(LiteralExpr& expr) {
}

void ParseAnalyser::visit_idf_expr(IdfExpr& expr) {
    if (!env.is_name_defined(expr.name)) {
        std::cout << "Undefined variable: " << expr.name.val << "\n";
    }
}

void ParseAnalyser::visit_call_expr(CallExpr& expr) {
    if (!env.is_name_defined(expr.name)) {
        std::cout << "Undefined function: " << expr.name.val << "\n";
    }

    for (Expr* arg : expr.args) {
        analyze_expr(arg);
    }
}

void ParseAnalyser::visit_grouping_expr(GroupingExpr& expr) {
    analyze_expr(expr.expr);
}


void ParseAnalyser::visit_func_decl(FuncDecl& stmt) {
    env.define_name(stmt.name);
    funcs.push_back(&stmt);
}

void ParseAnalyser::visit_block_stmt(BlockStmt& stmt) {
    for (Stmt* s : stmt.stmts) {
        analyze_stmt(s);
    }
}

void ParseAnalyser::visit_ret_stmt(RetStmt& stmt) {
    analyze_expr(stmt.val);
}

void ParseAnalyser::visit_if_stmt(IfStmt& stmt) {
    analyze_expr(stmt.cond);
    analyze_stmt(stmt.body);
}

void ParseAnalyser::visit_assign_stmt(AssignStmt& stmt) {
    analyze_expr(stmt.right_operand);

    if (!env.is_name_defined(stmt.left_operand)) {
        env.define_name(stmt.left_operand);
    }
}

void ParseAnalyser::visit_call_stmt(CallStmt& stmt) {
    if (!env.is_name_defined(stmt.name)) {
        std::cout << "Undefined function: " << stmt.name.val << "\n";
    }

    for (Expr* arg : stmt.args) {
        analyze_expr(arg);
    }
}
