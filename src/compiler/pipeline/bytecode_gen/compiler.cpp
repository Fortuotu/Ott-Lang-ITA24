#include "compiler/pipeline/bytecode_gen/compiler.hpp"

void Compiler::compile(AST* ast) {
    for (Stmt* stmt : ast->stmts) {
        stmt->accept(*this);
    }
}

void Compiler::write_to_file(std::string& filename) {
    std::ofstream of(filename, std::ios::binary | std::ios::app);
    if (!of) {
        std::cerr << "Compiler: Error opening or creating file\n";
        std::exit(EXIT_FAILURE);
    }

    of.write(reinterpret_cast<char*>(bytecode.bytes.data()), bytecode.bytes.size());
}

void Compiler::visit_binary_expr(BinaryExpr& expr) {

}

void Compiler::visit_unary_expr(UnaryExpr& expr) {

}

void Compiler::visit_literal_expr(LiteralExpr& expr) {
    if (const_idx.find(expr.literal.val) == const_idx.end()) {
        const_idx.insert(std::make_pair(expr.literal.val, const_table.size()));
        const_table.push_back(std::stoll(expr.literal.val));
    }

    bytecode.write_opcode(Opcode::LOAD_CONST);
    bytecode.write_arg8(const_idx.at(expr.literal.val));
}

void Compiler::visit_idf_expr(IdfExpr& expr) {
    static_cast<void>(env.find_defined(expr.name));

    if (env.is_global()) {
        bytecode.write_opcode(Opcode::LOAD_GLOBAL);
        bytecode.write_arg8(env.get());
    } else if (env.is_local()) {
        bytecode.write_opcode(Opcode::LOAD_LOCAL);
        bytecode.write_arg8(env.get());
    }
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
    if (!env.find_defined(stmt.left_operand)) {
        env.define(stmt.left_operand);
    }

    if (env.is_global()) {
        bytecode.write_opcode(Opcode::STORE_GLOBAL);
        bytecode.write_arg8(env.get());
    } else if (env.is_local()) {
        bytecode.write_opcode(Opcode::STORE_LOCAL);
        bytecode.write_arg8(env.get());
    }
}

void Compiler::visit_call_stmt(CallStmt& stmt) {

}

void Compiler::visit_print_stmt(PrintStmt& stmt) {

}
