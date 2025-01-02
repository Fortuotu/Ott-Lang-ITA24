#pragma once

#include <iostream>
#include <string>

#include "compiler/ast/ast.hpp"
#include "compiler/token/token.hpp"

class Parser {
private:
    AST* ast = nullptr;

    TokenConsumer consumer;

    Expr* expr();
    Expr* expr_equality();
    Expr* expr_term();
    Expr* expr_factor();
    Expr* expr_unary();
    Expr* expr_primary();

    Stmt* stmt();

    Decl* parse_decl();
    FuncDecl* parse_func_decl();
public:
    Parser(std::queue<Token>& tokens) : ast(new AST()), consumer(tokens) {}

    AST* parse();
};
