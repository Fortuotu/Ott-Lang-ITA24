#pragma once

#include <iostream>
#include <string>

#include "compiler/ast/ast.hpp"
#include "compiler/token/token.hpp"

class Parser {
private:
    TokenConsumer consumer;

    Expr* parse_expr();
    Expr* expr_equality();
    Expr* expr_term();
    Expr* expr_factor();
    Expr* expr_unary();
    Expr* expr_primary();

    Stmt* parse_stmt();
    Stmt* parse_decl();
    FuncDecl* parse_func_decl();
    BlockStmt* parse_block_stmt();
    IfStmt* parse_if_stmt();
public:
    Parser(std::queue<Token>& tokens) : consumer(tokens) {}

    AST* parse();
};
