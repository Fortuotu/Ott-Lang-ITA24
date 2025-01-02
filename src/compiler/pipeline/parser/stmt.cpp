#include "parser.hpp"

Stmt* Parser::parse_stmt() {
    Stmt* stmt = nullptr;

    consumer.check();

    switch (consumer.get_type()) {
    case TokenType::OPEN_CURLY:
        stmt = parse_block_stmt();
        break;
    case TokenType::KW_IF:
        stmt = parse_if_stmt();
        break;
    default:
        break;
    }

    return stmt;
}

Stmt* Parser::parse_decl() {
    Stmt* decl = nullptr;

    consumer.check();

    switch (consumer.get_type()) {
    case TokenType::KW_FUNCTION:
        decl = parse_func_decl();
        break;
    default:
        break;
    }

    return decl;
}

FuncDecl* Parser::parse_func_decl() {
    FuncDecl* decl = new FuncDecl();

    if (!consumer.match({TokenType::KW_FUNCTION})) { return nullptr; }
    if (!consumer.match({TokenType::IDENTIFIER})) { return nullptr; }

    decl->name = consumer.get();

    if (!consumer.match({TokenType::OPEN_PARENTH})) { return nullptr; }

    while (consumer.match({TokenType::IDENTIFIER})) {
        decl->params.push_back(consumer.get());

        if (!consumer.match({TokenType::COMMA})) { break; }

        consumer.check();
        if (consumer.get_type() != TokenType::COMMA) { return nullptr; }
    }

    if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }

    decl->body = parse_block_stmt();
    if (!decl->body) { return nullptr; }

    return decl;
}

BlockStmt* Parser::parse_block_stmt() {
    BlockStmt* block_stmt = new BlockStmt();

    if (!consumer.match({TokenType::OPEN_CURLY})) { return nullptr; }

    while (!consumer.match({TokenType::CLOSE_CURLY})) {
        if (consumer.out_of_tokens()) { return nullptr; }

        Stmt* stmt = parse_stmt();
        if (!stmt) { return nullptr; }
    
        block_stmt->stmts.push_back(stmt);
    }

    return block_stmt;
}

IfStmt* Parser::parse_if_stmt() {
    IfStmt* stmt = new IfStmt();

    if (!consumer.match({TokenType::KW_IF})) { return nullptr; }
    if (!consumer.match({TokenType::OPEN_PARENTH})) { return nullptr; }

    stmt->cond = parse_expr();
    if (!stmt->cond) { return nullptr; }

    if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }

    stmt->body = parse_block_stmt();
    if (!stmt->body) { return nullptr; }

    return stmt;
}
