#pragma once

#include <vector>
#include <string>
#include <memory>
#include <variant>

#include "tokens.hpp"
#include "ast.hpp"

// Creates the AST from tokens.
class Parser {
private:
    Expr* ParseGrouping(TokenStream& tokens);
    Expr* ParseUnary(TokenStream& tokens);
    Expr* ParseFactor(TokenStream& tokens);
    Expr* ParseTerm(TokenStream& tokens);
    Expr* ParseCondition(TokenStream& tokens);
    Expr* ParseEquality(TokenStream& tokens);
    Expr* ParseIdf(TokenStream& tokens);

    Expr* ParseExpr(TokenStream& tokens);

    Stmt* ParsePrint(TokenStream& tokens);
    Stmt* ParseVarDecl(TokenStream& tokens);
    Stmt* ParseAssign(TokenStream& tokens);
    Stmt* ParseIf(TokenStream& tokens);
    Stmt* ParseBlock(TokenStream& tokens);
    Stmt* ParseFuncDecl(TokenStream& tokens);
    Stmt* ParseIdfStmt(TokenStream& tokens);

    Stmt* ParseStmt(TokenStream& tokens);

    void ParseFuncCallArgs(TokenStream& tokens, CallExprStmt* call);
public:
    Parser() {}
    ~Parser() {}

    // parse function
    AST* GenerateAST(TokenStream& tokens);
};
