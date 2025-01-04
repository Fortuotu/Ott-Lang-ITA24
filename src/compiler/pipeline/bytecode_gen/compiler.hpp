#pragma once

#include <cstdint>
#include <string>

#include "compiler/ast/ast.hpp"
#include "compiler/environment/environment.hpp"
#include "runtime/bytecode.hpp"

class Compiler : StmtVisitor, ExprVisitor {
private:
    Environment env;

    std::vector<RuntimeValue> constants;
    std::vector<std::uint8_t> bytecode;

    void compile_stmt(Stmt* stmt) { stmt->accept(*this); }
    void compile_expr(Expr* expr) { expr->accept(*this); }

    void emit(Opcode opcode) {  bytecode.push_back(static_cast<std::uint8_t>(opcode)); }
    void emit(Opcode opcode, std::uint8_t arg) { bytecode.push_back(static_cast<std::uint8_t>(opcode)); bytecode.push_back(arg); }
    void emit(Opcode opcode, std::uint16_t arg) { bytecode.push_back(static_cast<std::uint8_t>(opcode));
                                                  bytecode.push_back(static_cast<std::uint8_t>(arg >> 8));
                                                  bytecode.push_back(static_cast<std::uint8_t>(arg & 0xff)); }
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
    virtual void visit_assign_stmt(AssignStmt& stmt) override;
    virtual void visit_call_stmt(CallStmt& stmt) override;
    virtual void visit_print_stmt(PrintStmt& stmt) override;

    void compile(AST* ast);
};
