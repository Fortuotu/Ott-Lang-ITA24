#include "parser.hpp"

Stmt* Parser::parse_stmt() {
    Stmt* stmt = nullptr;

    consumer.consume();

    switch (consumer.get_type()) {
    case TokenType::OPEN_CURLY:
        env.start_scope();
        stmt = parse_block_stmt();
        env.end_scope();
        break;
    case TokenType::KW_RETURN:
        stmt = parse_ret_stmt();
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

    consumer.consume();

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

    if (!consumer.match({TokenType::IDENTIFIER})) { return nullptr; }

    decl->name = consumer.get();

    if (!consumer.match({TokenType::OPEN_PARENTH})) { return nullptr; }

    if (consumer.match({TokenType::IDENTIFIER})) {
        decl->params.push_back(consumer.get());

        while (consumer.match({TokenType::COMMA})) {
            if (!consumer.match({TokenType::IDENTIFIER})) { return nullptr; }
 
            decl->params.push_back(consumer.get());
        }
    }

    if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }
    if (!consumer.match({TokenType::OPEN_CURLY})) { return nullptr; }

    env.start_scope_with(decl->params);
    decl->body = parse_block_stmt();
    env.end_scope();

    if (!decl->body) { return nullptr; }

    env.define_name(decl->name);

    return decl;
}

BlockStmt* Parser::parse_block_stmt() {
    BlockStmt* block_stmt = new BlockStmt();

    while (!consumer.match({TokenType::CLOSE_CURLY})) {
        if (consumer.out_of_tokens()) { return nullptr; }

        Stmt* stmt = parse_stmt();
        if (!stmt) { return nullptr; }
    
        block_stmt->stmts.push_back(stmt);
    }

    return block_stmt;
}

RetStmt* Parser::parse_ret_stmt() {
    RetStmt* stmt = new RetStmt();

    stmt->val = parse_expr();
    if (!stmt->val) { return nullptr; }

    return stmt;
}

IfStmt* Parser::parse_if_stmt() {
    IfStmt* stmt = new IfStmt();

    if (!consumer.match({TokenType::OPEN_PARENTH})) { return nullptr; }

    stmt->cond = parse_expr();
    if (!stmt->cond) { return nullptr; }

    if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }
    if (!consumer.match({TokenType::OPEN_CURLY})) { return nullptr; }

    stmt->body = parse_block_stmt();
    if (!stmt->body) { return nullptr; }

    return stmt;
}
