#include "compiler.hpp"

#include <iostream>
#include <fstream>

void Compiler::emitOpByte(Opcode op) {
    bytes.push_back((byte)op);
}

void Compiler::emitByte(byte b) {
    bytes.push_back(b);
}

void Compiler::visitBinaryExpr(BinaryExpr& expr) {
    expr.left->accept(*this);
    expr.right->accept(*this);

    switch (expr.op) {
    case TokenType::ADD:
        emitOpByte(Opcode::ADD);
        break;
    case TokenType::SUBTRACT:
       emitOpByte(Opcode::SUB);
        break;
    case TokenType::MULTIPLY:
        emitOpByte(Opcode::MUL);
        break;
    case TokenType::DIVIDE:
        emitOpByte(Opcode::DIV);
        break;
    default:
        break;
    }
}

void Compiler::visitUnaryExpr(UnaryExpr& expr) {
    expr.operand->accept(*this);

    switch (expr.op) {
    case TokenType::SUBTRACT:
        emitOpByte(Opcode::NEG);
        break;
    case TokenType::NOT:
        emitOpByte(Opcode::NOT);
        break;
    default:
        break;
    }
}

void Compiler::visitLiteralExpr(LiteralExpr& expr) {
    if (const_tab_entry.count(expr.val) == 0) {
        const_tab.push_back(std::atoi(expr.val.c_str()));
        const_tab_entry[expr.val] = const_tab.size() - 1;
    }

    int tab_offset = const_tab_entry[expr.val];

    emitOpByte(Opcode::LOAD_CONST);
    emitByte((byte)tab_offset);
}

void Compiler::visitIdfExpr(IdfExpr& expr) {
    int idx = 0;

    // Identifier is local
    if ((idx = getLocalIdx(expr.name)) >= 0) {
        emitOpByte(Opcode::LOAD_LOC);
        emitByte((byte)idx);
        return;
    }

    // Global is not defined
    if (global_tab_entry.count(expr.name) == 0) {
        printf("Global not defined\n");
        exit(1);
    }

    int global_id = global_tab_entry[expr.name];
    emitOpByte(Opcode::LOAD_GLOBAL);
    emitByte((byte)global_id);
}

void Compiler::visitGroupingExpr(GroupingExpr& expr) {
    compileExpr(expr.expr);
}

void Compiler::compileExpr(Expr* expr) {
    expr->accept(*this);
}

void Compiler::visitPrintStmt(PrintStmt& stmt) {
    compileExpr(stmt.value);
    emitOpByte(Opcode::PRINT);
}

int Compiler::getLocalIdx(std::string& name) {
    for (int i = locals.size() - 1; i >= 0; --i) {
        if (name.length() == locals[i].name.length() &&
            name == locals[i].name) {
            
            return i;
        }
    }
    return -1;
}

void Compiler::visitVarDecl(VarDecl& stmt) {
    int idx = 0;

    // Variable is local and doesn't exist
    if (cur_nest > 0) {
        if (getLocalIdx(stmt.identifier) < 0) {
            locals.push_back(Local(cur_nest, stmt.identifier));

            idx = locals.size() - 1;

            compileExpr(stmt.initializer);
            emitOpByte(Opcode::STORE_LOC);
            emitByte((byte)idx);

            return;
        }

        // Some obscure error idk
        printf("Some weird error\n");
        exit(1);
    }

    // Variable is global and doesn't exist
    if (global_tab_entry.count(stmt.identifier) == 0) {
        global_tab_entry[stmt.identifier] = global_count;

        compileExpr(stmt.initializer);
        emitOpByte(Opcode::STORE_GLOBAL);
        emitByte((byte)global_count);

        ++global_count;
    } else {
        // Redefinition of variable, do nothing
        return;
    }
}

void Compiler::visitAssignStmt(AssignStmt& stmt) {
    int idx = 0;

    // Lvalue is local
    if ((idx = getLocalIdx(stmt.left)) >= 0) {
        compileExpr(stmt.right);
        emitOpByte(Opcode::STORE_LOC);
        emitByte((byte)idx);
        return;
    }

    // Lvalue isn't local nor global
    if (global_tab_entry.count(stmt.left) == 0) {
        printf("Identifier doesn't exist.");
        exit(1);
    }

    // Lvalue is global
    emitOpByte(Opcode::STORE_GLOBAL);
    emitByte((byte)global_tab_entry[stmt.left]);
}

void Compiler::visitIfStmt(IfStmt& stmt) {
    int backpatch_idx = 0;
    int instruction_offset = 0;

    compileExpr(stmt.cond);

    emitOpByte(Opcode::JUMP_IFF);
    instruction_offset = bytes.size() - 1;

    emitByte((byte)0);
    backpatch_idx = bytes.size() - 1;

    compileStmt(stmt.stmt);

    bytes[backpatch_idx] = bytes.size() - instruction_offset;
}

void Compiler::visitBlock(Block& stmt) {
    ++cur_nest;
    for (Stmt* st : stmt.stmts) { compileStmt(st); }
    --cur_nest;

    // Cleanup stack
    if (cur_nest == 0) {
        locals.clear();
        return;
    }
    while (locals[locals.size() - 1].nest != cur_nest) {
        locals.pop_back();
    }
}

void Compiler::compileStmt(Stmt* stmt) {
    stmt->accept(*this);
}

void Compiler::compile(const char* filename) {
    for (Stmt* stmt : ast->stmts) {
        compileStmt(stmt);
    }
    emitOpByte(Opcode::EXIT);

    std::ofstream f(filename, std::ios::binary);

    int temp;

    // Write contents to file
    temp = const_tab.size();
    f.write(reinterpret_cast<const char*>(&temp), sizeof(int));
    temp = bytes.size();
    f.write(reinterpret_cast<const char*>(&temp), sizeof(int));
    f.write(reinterpret_cast<const char*>(const_tab.data()), const_tab.size() * sizeof(RtVal));
    f.write(reinterpret_cast<const char*>(bytes.data()), bytes.size() * sizeof(byte));

    // Check for errors
    if (!f) {
        std::cerr << "Error writing to file!" << std::endl;
        exit(1);
    }
}
