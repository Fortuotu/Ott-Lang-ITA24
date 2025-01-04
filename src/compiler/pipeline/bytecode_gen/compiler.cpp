#include "compiler/pipeline/bytecode_gen/compiler.hpp"

void Compiler::compile(AST* ast) {
    for (Stmt* stmt : ast->stmts) {
        stmt->accept(*this);
    }
}

void Compiler::visit_binary_expr(BinaryExpr& expr) {
    expr.left_operand->accept(*this);
    expr.right_operand->accept(*this);
}

void Compiler::visit_unary_expr(UnaryExpr& expr) {
    expr.operand->accept(*this);
}

void Compiler::visit_literal_expr(LiteralExpr& expr) {
    constants.push_back(RuntimeValue{std::stoi(expr.literal.val)});
}

void Compiler::visit_idf_expr(IdfExpr& expr) {

}

void Compiler::visit_call_expr(CallExpr& expr) {

}

void Compiler::visit_grouping_expr(GroupingExpr& expr) {
    
}


void Compiler::visit_func_decl(FuncDecl& stmt) {
    
}

void Compiler::visit_block_stmt(BlockStmt& stmt) {
    
}

void Compiler::visit_ret_stmt(RetStmt& stmt) {
    
}

void Compiler::visit_if_stmt(IfStmt& stmt) {
    
}

void Compiler::visit_assign_stmt(AssignStmt& stmt) {
    
}

void Compiler::visit_call_stmt(CallStmt& stmt) {
    
}

void Compiler::visit_print_stmt(PrintStmt& stmt) {
    
}
