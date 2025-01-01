#pragma once

#include <string>

#include "compiler/ast/ast.hpp"
#include "compiler/token/token.hpp"

class Parser {
private:
    TokenConsumer consumer;

    Expr* expr();
    Expr* expr_equality();
    Expr* expr_term();
    Expr* expr_factor();
    Expr* expr_unary();
    Expr* expr_primary();

    Stmt* stmt();
public:
    Parser(std::queue<Token>& tokens) : consumer(tokens) {}

    
};
