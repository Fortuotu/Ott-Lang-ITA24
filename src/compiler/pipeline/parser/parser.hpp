#pragma once

#include <iostream>
#include <string>

#include "compiler/ast/ast.hpp"
#include "compiler/token/token.hpp"

class Parser {
private:
    TokenConsumer consumer;

    Expr* parse_expr();
    Expr* parse_equality();
    Expr* parse_term();
    Expr* parse_factor();
    Expr* parse_unary();
    Expr* parse_primary();
    CallExpr* parse_call_expr();
    GroupingExpr* parse_grouping_expr();

    Stmt* parse_stmt();
    Stmt* parse_decl();
    FuncDecl* parse_func_decl();
    BlockStmt* parse_block_stmt();
    IfStmt* parse_if_stmt();
public:
    Parser(std::queue<Token>& tokens) : consumer(tokens) {}

    AST* parse();
};
