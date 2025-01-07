#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <fstream>

#include "compiler/ast/ast.hpp"
#include "compiler/environment/environment.hpp"
#include "compiler/pipeline/bytecode_gen/byte_buffer.hpp"
#include "runtime/bytecode.hpp"

class Compiler : StmtVisitor, ExprVisitor {
private:
    EnvironmentEx env;

    ByteBuffer main;
    
    std::vector<ByteBuffer> funcs;

    std::vector<std::uint16_t> func_table;
    std::unordered_map<std::string, std::uint8_t> func_idx;

    ByteBuffer* buffer;

    std::vector<Value> const_table;
    std::unordered_map<std::string, std::uint8_t> const_idx;

    void compile_stmt(Stmt* stmt) { stmt->accept(*this); }
    void compile_expr(Expr* expr) { expr->accept(*this); }

    void fill_func_table(std::size_t starting_offset);
public:
    Compiler() : buffer(&main) {}

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

    void compile(AST* ast);
    void write_to_file(std::string& filename);
};
