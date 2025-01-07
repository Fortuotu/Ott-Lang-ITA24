#pragma once

#include <iostream>
#include <string>

#include "compiler/ast/ast.hpp"
#include "compiler/token/token.hpp"
#include "compiler/pipeline/parser/parse_analyzer.hpp"

class Parser {
private:
    TokenConsumer consumer;

    Expr* parse_expr();
    Expr* parse_equality();
    Expr* parse_term();
    Expr* parse_factor();
    Expr* parse_unary();
    Expr* parse_primary();
    CallExpr* parse_call_expr(Token& name);
    GroupingExpr* parse_grouping_expr();

    Stmt* parse_stmt();
    FuncDecl* parse_func_decl();
    BlockStmt* parse_block_stmt();
    RetStmt* parse_ret_stmt();
    IfStmt* parse_if_stmt();
    WhileStmt* parse_while_stmt();
    AssignStmt* parse_assign_stmt(Token& name);
    CallStmt* parse_call_stmt(Token& name);
    PrintStmt* parse_print_stmt();
public:
    Parser(std::queue<Token>& tokens) : consumer(tokens) {}

    AST* parse();
};
