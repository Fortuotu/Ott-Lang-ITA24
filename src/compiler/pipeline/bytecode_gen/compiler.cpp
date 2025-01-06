#include "compiler/pipeline/bytecode_gen/compiler.hpp"

void Compiler::compile(AST* ast) {
    for (Stmt* stmt : ast->stmts) {
        stmt->accept(*this);
    }

    fill_func_table(main.bytes.size());
}

void Compiler::write_to_file(std::string& filename) {
    std::ofstream of(filename, std::ios::binary);
    if (!of) {
        std::cerr << "Compiler: Error opening or creating file\n";
        std::exit(EXIT_FAILURE);
    }

    std::size_t size = 0;

    size = const_table.size() * sizeof(Value);
    of.write(reinterpret_cast<char*>(size), sizeof(size));

    size = func_table.size() * sizeof(std::uint16_t);
    of.write(reinterpret_cast<char*>(size), sizeof(size));

    of.write(reinterpret_cast<char*>(const_table.data()), size);

    of.write(reinterpret_cast<char*>(func_table.data()), size);

    of.write(reinterpret_cast<char*>(main.bytes.data()), main.bytes.size());
    for (ByteBuffer& func : funcs) {
        of.write(reinterpret_cast<char*>(func.bytes.data()), func.bytes.size());
    }
}

void Compiler::fill_func_table(std::size_t starting_offset) {
    std::size_t offset = starting_offset;

    func_table.resize(funcs.size());
    for (std::size_t i = 0; i < func_table.size(); ++i) {
        offset += funcs.at(i).bytes.size();

        func_table.at(i) = offset;
    }
}

void Compiler::visit_binary_expr(BinaryExpr& expr) {
    compile_expr(expr.left_operand);
    compile_expr(expr.right_operand);

    switch (expr.op) {
    case TokenType::OP_ADD:
        buffer->write_opcode(Opcode::ADD);
        break;
    case TokenType::OP_SUB:
        buffer->write_opcode(Opcode::SUB);
        break;
    case TokenType::OP_MUL:
        buffer->write_opcode(Opcode::MUL);
        break;
    case TokenType::OP_DIV:
        buffer->write_opcode(Opcode::DIV);
        break;
    case TokenType::OP_GREATER:
        buffer->write_opcode(Opcode::GT);
        break;
    case TokenType::OP_LESS:
        buffer->write_opcode(Opcode::LT);
        break;
    case TokenType::OP_EQUALS:
        buffer->write_opcode(Opcode::EQ);
        break;
    case TokenType::OP_NOT_EQUALS:
        buffer->write_opcode(Opcode::NEQ);
        break;
    case TokenType::OP_GREATER_EQUALS:
        buffer->write_opcode(Opcode::GTE);
        break;
    case TokenType::OP_LESS_EQUALS:
        buffer->write_opcode(Opcode::LTE);
        break;
    default:
        break;
    }
}

void Compiler::visit_unary_expr(UnaryExpr& expr) {
    compile_expr(expr.operand);

    switch (expr.op) {
    case TokenType::OP_NOT:
        buffer->write_opcode(Opcode::NOT);
        break;
    case TokenType::OP_SUB:
        buffer->write_opcode(Opcode::NEG);
        break;
    default:
        break;
    }
}

void Compiler::visit_literal_expr(LiteralExpr& expr) {
    if (const_idx.find(expr.literal.val) == const_idx.end()) {
        const_idx.insert(std::make_pair(expr.literal.val, const_table.size()));
        const_table.push_back(std::stoll(expr.literal.val));
    }
    
    buffer->write_opcode(Opcode::LOAD_CONST);
    buffer->write_arg8(const_idx.at(expr.literal.val));
}

void Compiler::visit_idf_expr(IdfExpr& expr) {
    static_cast<void>(env.find_defined(expr.name));

    if (env.is_global()) {
        buffer->write_opcode(Opcode::LOAD_GLOBAL);
        buffer->write_arg8(env.get());
    } else if (env.is_local()) {
        buffer->write_opcode(Opcode::LOAD_LOCAL);
        buffer->write_arg8(env.get());
    }
}

void Compiler::visit_call_expr(CallExpr& expr) {
    for (Expr* arg : expr.args) {
        compile_expr(arg);
    }

    buffer->write_opcode(Opcode::CALL);
    buffer->write_arg8(func_idx.at(expr.name.val));
    buffer->write_arg8(static_cast<std::uint8_t>(expr.args.size()));
}

void Compiler::visit_grouping_expr(GroupingExpr& expr) {
    compile_expr(expr.expr);
}

void Compiler::visit_func_decl(FuncDecl& stmt) {
    funcs.push_back(ByteBuffer());
    buffer = &funcs.back();

    func_idx.insert(std::make_pair(
        stmt.name.val,
        static_cast<std::uint8_t>(funcs.size() - 1)
    ));

    env.start_scope_with(stmt.params);
    compile_stmt(stmt.body);
    env.end_scope();

    buffer = &main;
}

void Compiler::visit_block_stmt(BlockStmt& stmt) {
    for (Stmt* s : stmt.stmts) {
        compile_stmt(s);
    }
}

void Compiler::visit_ret_stmt(RetStmt& stmt) {
    compile_expr(stmt.val);

    buffer->write_opcode(Opcode::RET);
}

void Compiler::visit_if_stmt(IfStmt& stmt) {
    compile_expr(stmt.cond);

    buffer->write_opcode(Opcode::JUMP_IF_FALSE);
    std::size_t jmp_backpatch = buffer->write_arg8(0xff);

    compile_stmt(stmt.body);

    buffer->backpatch_arg8(jmp_backpatch, buffer->get_last_idx() - jmp_backpatch);
}

void Compiler::visit_assign_stmt(AssignStmt& stmt) {
    if (!env.find_defined(stmt.left_operand)) {
        env.define(stmt.left_operand);
    }

    compile_expr(stmt.right_operand);

    if (env.is_global()) {
        buffer->write_opcode(Opcode::STORE_GLOBAL);
        buffer->write_arg8(env.get());
    } else if (env.is_local()) {
        buffer->write_opcode(Opcode::STORE_LOCAL);
        buffer->write_arg8(env.get());
    }
}

void Compiler::visit_call_stmt(CallStmt& stmt) {
    for (auto& arg : stmt.args) {
        compile_expr(arg);
    }

    buffer->write_opcode(Opcode::CALL);
    
}

void Compiler::visit_print_stmt(PrintStmt& stmt) {
    compile_expr(stmt.expr);

    buffer->write_opcode(Opcode::PRINT);
}
