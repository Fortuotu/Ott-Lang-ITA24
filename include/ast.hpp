#pragma once

#include "tokens.hpp"

struct CallExprStmt;

struct UnaryExpr;
struct BinaryExpr;
struct LiteralExpr;
struct GroupingExpr;
struct IdfExpr;

class ExprVisitor {
public:
    virtual ~ExprVisitor() = default;
    virtual void visitUnaryExpr(UnaryExpr& expr) = 0;
    virtual void visitBinaryExpr(BinaryExpr& expr) = 0;
    virtual void visitLiteralExpr(LiteralExpr& expr) = 0;
    virtual void visitIdfExpr(IdfExpr& expr) = 0;
    virtual void visitGroupingExpr(GroupingExpr& expr) = 0;
    virtual void visitCallExpr(CallExprStmt& expr) = 0;
};

struct PrintStmt;
struct VarDecl;
struct AssignStmt;
struct Block;
struct IfStmt;
struct FuncDecl;

class StmtVisitor {
public:
    virtual ~StmtVisitor() = default;
    virtual void visitPrintStmt(PrintStmt& stmt) = 0;
    virtual void visitVarDecl(VarDecl& stmt) = 0;
    virtual void visitAssignStmt(AssignStmt& stmt) = 0;
    virtual void visitBlock(Block& stmt) = 0;
    virtual void visitIfStmt(IfStmt& stmt) = 0;
    virtual void visitFuncDecl(FuncDecl& stmt) = 0;
    virtual void visitCallStmt(CallExprStmt& expr) = 0;
};

struct ASTNode {};

struct Expr : ASTNode {
    virtual void accept(ExprVisitor& visitor) = 0;
};

struct UnaryExpr : Expr {
    TokenType op;
    Expr *operand;

    UnaryExpr(TokenType opP, Expr *operandP) : op(opP), operand(operandP) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visitUnaryExpr(*this); }
};

struct BinaryExpr : Expr {
    TokenType op;
    Expr *left, *right;

    BinaryExpr(TokenType opP, Expr *leftP, Expr *rightP) : op(opP), left(leftP), right(rightP) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visitBinaryExpr(*this); };
};

struct LiteralExpr : Expr {
    TokenType type;
    std::string val;

    LiteralExpr(TokenType typeP, std::string& valP) : type(typeP), val(valP) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visitLiteralExpr(*this); };
};

struct IdfExpr : Expr {
    std::string name;

    IdfExpr(std::string& nameP) : name(nameP) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visitIdfExpr(*this); };
};

struct GroupingExpr : Expr {
    Expr* expr;

    GroupingExpr(Expr* exprP) : expr(exprP) {}

    virtual void accept(ExprVisitor& visitor) override { visitor.visitGroupingExpr(*this); };
};

struct Stmt {
    virtual void accept(StmtVisitor& visitor) = 0;
};

struct FuncDecl : Stmt {
    std::string name;
    std::vector<VarDecl*> params;
    Stmt* body = nullptr;

    FuncDecl() {}

    virtual void accept(StmtVisitor& visitor) override { visitor.visitFuncDecl(*this); }
};

struct Block : Stmt {
    std::vector<Stmt*> stmts;

    Block() {}

    virtual void accept(StmtVisitor& visitor) override { visitor.visitBlock(*this); };    
};

struct PrintStmt : Stmt {
    Expr* value;

    PrintStmt(Expr* valueP) : value(valueP) {}

    virtual void accept(StmtVisitor& visitor) override { visitor.visitPrintStmt(*this); };
};

struct VarDecl : Stmt {
    std::string identifier;

    Expr* initializer;

    VarDecl() {}
    VarDecl(std::string& identifierP, Expr* initializerP) : identifier(identifierP), initializer(initializerP) {}

    virtual void accept(StmtVisitor& visitor) override { visitor.visitVarDecl(*this); };
};

struct AssignStmt : Stmt {
    std::string left;
    Expr* right;

    AssignStmt() {}
    AssignStmt(std::string& leftP, Expr* rightP) : left(leftP), right(rightP) {}

    virtual void accept(StmtVisitor& visitor) override { visitor.visitAssignStmt(*this); };
};

struct IfStmt : Stmt {
    Expr* cond;
    Stmt* stmt;

    IfStmt() {}
    IfStmt(Expr* condP, Stmt* stmtP) : cond(condP), stmt(stmtP) {}

    virtual void accept(StmtVisitor& visitor) override { visitor.visitIfStmt(*this); };
};

struct CallExprStmt : Expr, Stmt {
    std::string calle_idf;
    std::vector<Expr*> args;

    virtual void accept(ExprVisitor& visitor) override { visitor.visitCallExpr(*this); };
    virtual void accept(StmtVisitor& visitor) override { visitor.visitCallStmt(*this); };
};

struct AST {
    std::vector<Stmt*> stmts;
};

// For debugging expression syntax trees.
class ExprPrinter : ExprVisitor {
private:
    std::string buf;
    std::string temp;
    
    void space();
public:
    virtual void visitUnaryExpr(UnaryExpr& expr) override;
    virtual void visitBinaryExpr(BinaryExpr& expr) override;
    virtual void visitLiteralExpr(LiteralExpr& expr) override;
    virtual void visitGroupingExpr(GroupingExpr& expr) override;

    ExprPrinter() {}
    ~ExprPrinter() {}

    void print(Expr* expr);
};
