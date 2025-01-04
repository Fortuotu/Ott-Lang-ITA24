#include "parse_analyzer.hpp"

void ParseAnalyser::analyze(AST* ast) {
    for (Stmt* stmt : ast->stmts) {
        analyze_stmt(stmt);
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
        std::exit(EXIT_FAILURE);
    }
}

void ParseAnalyser::visit_call_expr(CallExpr& expr) {
    if (funcs.find(expr.name.val) == funcs.end()) {
        std::cout << "Undefined function: " << expr.name.val << "\n";
        std::exit(EXIT_FAILURE);
    }

    if (funcs.at(expr.name.val)->params.size() != expr.args.size()) {
        std::cout << expr.name.val << " takes " << funcs.at(expr.name.val)->params.size() << " arguments, but " << expr.args.size() << " were given.\n";
        std::exit(EXIT_FAILURE);
    }

    for (Expr* arg : expr.args) {
        analyze_expr(arg);
    }

    env.start_scope_with(funcs.at(expr.name.val)->params);
    analyze_stmt(funcs.at(expr.name.val)->body);
    env.end_scope();
}

void ParseAnalyser::visit_grouping_expr(GroupingExpr& expr) {
    analyze_expr(expr.expr);
}


void ParseAnalyser::visit_func_decl(FuncDecl& stmt) {
    funcs.insert(std::make_pair(stmt.name.val, &stmt));
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
    if (funcs.find(stmt.name.val) == funcs.end()) {
        std::cout << "Undefined function: " << stmt.name.val << "\n";
        std::exit(EXIT_FAILURE);
    }

    if (funcs.at(stmt.name.val)->params.size() != stmt.args.size()) {
        std::cout << stmt.name.val << " takes " << funcs.at(stmt.name.val)->params.size() << " arguments, but " << stmt.args.size() << " were given.\n";
        std::exit(EXIT_FAILURE);
    }

    for (Expr* arg : stmt.args) {
        analyze_expr(arg);
    }

    env.start_scope_with(funcs.at(stmt.name.val)->params);
    analyze_stmt(funcs.at(stmt.name.val)->body);
    env.end_scope();
}

void ParseAnalyser::visit_print_stmt(PrintStmt& stmt) {
    analyze_expr(stmt.expr);
}
