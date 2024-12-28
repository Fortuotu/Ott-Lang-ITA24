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
    if (global_tab_entry.count(expr.name) == 0) {
        // error
        printf("Global not defined\n");
        exit(1);
    }

    emitOpByte(Opcode::LOAD_GLOBAL);

    int global_id = global_tab_entry[expr.name];
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

void Compiler::visitVarDecl(VarDecl& stmt) {
    if (global_tab_entry.count(stmt.identifier) == 0) {
        global_tab_entry[stmt.identifier] = global_count;

        compileExpr(stmt.initializer);
        emitOpByte(Opcode::STORE_GLOBAL);
        emitByte((byte)global_count);

        ++global_count;
    }

    // Redefinition of variable, do nothing
}

void Compiler::visitAssignStmt(AssignStmt& stmt) {
    if (global_tab_entry.count(stmt.left) == 0) {
        // error
        printf("Identifier doesnt exist.");
        exit(1);
    }

    compileExpr(stmt.right);
    emitOpByte(Opcode::STORE_GLOBAL);
    emitByte((byte)global_tab_entry[stmt.left]);
} 

void Compiler::compileStmt(Stmt* stmt) {
    stmt->accept(*this);
}

void Compiler::compile(const char* filename) {
    for (Stmt* stmt : ast->stmts) {
        compileStmt(stmt);
    }

    std::ofstream f(filename, std::ios::binary);

    int temp;

    temp = const_tab.size();
    f.write(reinterpret_cast<const char*>(&temp), sizeof(int));

    temp = bytes.size();
    f.write(reinterpret_cast<const char*>(&temp), sizeof(int));

    f.write(reinterpret_cast<const char*>(const_tab.data()), const_tab.size() * sizeof(RtVal));
    
    f.write(reinterpret_cast<const char*>(bytes.data()), bytes.size() * sizeof(byte));

    if (!f) {
        std::cerr << "Error writing to file!" << std::endl;
        exit(1);
    }
}
