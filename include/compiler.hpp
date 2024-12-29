#pragma once

#include "ast.hpp"
#include "bytecode.hpp"

#include <unordered_map>

// Compiles the AST to instructions for the stack machine. 
class Compiler : ExprVisitor, StmtVisitor {
private:
    struct Local {
        int nest = -1;
        std::string name;

        Local(int nestP, std::string& nameP) : nest(nestP), name(nameP) {}
    };
    int getLocalIdx(std::string& name);

    std::vector<Local> locals__;
    std::vector<Local> func_locals__;
    std::vector<Local>* locals = &locals__;
    int cur_nest = 0;

    AST* ast = nullptr;
    std::vector<byte> bytes;

    std::vector<RtVal> const_tab;
    std::unordered_map<std::string, int> const_tab_entry;
    int global_count = 0;
    std::unordered_map<std::string, int> global_tab_entry;

    void compileExpr(Expr* expr);
    void compileStmt(Stmt* stmt);

    void emitOpByte(Opcode op);
    void emitByte(byte b);
public:
    Compiler(AST* astP) : ast(astP) {}
    ~Compiler() {}

    virtual void visitUnaryExpr(UnaryExpr& expr) override;
    virtual void visitBinaryExpr(BinaryExpr& expr) override;
    virtual void visitLiteralExpr(LiteralExpr& expr) override;
    virtual void visitGroupingExpr(GroupingExpr& expr) override;
    virtual void visitIdfExpr(IdfExpr& expr) override;

    virtual void visitPrintStmt(PrintStmt& stmt) override;
    virtual void visitAssignStmt(AssignStmt& stmt) override;
    virtual void visitVarDecl(VarDecl& stmt) override;
    virtual void visitIfStmt(IfStmt& stmt) override;
    virtual void visitBlock(Block& stmt) override;
    virtual void visitFuncDecl(FuncDecl& stmt) override;

    void compile(const char* filename);
};
