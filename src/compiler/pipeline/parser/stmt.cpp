#include "parser.hpp"

Stmt* Parser::parse_stmt() {
    Stmt* stmt = nullptr;
    Token name;

    consumer.consume();

    switch (consumer.get_type()) {
    case TokenType::KW_FUNCTION:
        stmt = parse_func_decl();
        break;
    case TokenType::OPEN_CURLY:
        stmt = parse_block_stmt();
        break;
    case TokenType::KW_RETURN:
        stmt = parse_ret_stmt();
        break;
    case TokenType::KW_IF:
        stmt = parse_if_stmt();
        break;
    case TokenType::KW_WHILE:
        stmt = parse_while_stmt();
        break;
    case TokenType::IDENTIFIER:
        name = consumer.get();
        if (consumer.match({TokenType::OP_ASSIGN})) {
            stmt = parse_assign_stmt(name);
        }
        else if (consumer.match({TokenType::OPEN_PARENTH})) {
            stmt = parse_call_stmt(name);
        }
        break;
    case TokenType::KW_PRINT:
        stmt = parse_print_stmt();
        break;
    default:
        break;
    }

    return stmt;
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

    decl->body = parse_block_stmt();
    if (!decl->body) { return nullptr; }

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

WhileStmt* Parser::parse_while_stmt() {
    WhileStmt* stmt = new WhileStmt();

    if (!consumer.match({TokenType::OPEN_PARENTH})) { return nullptr; }

    stmt->cond = parse_expr();
    if (!stmt->cond) { return nullptr; }

    if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }
    if (!consumer.match({TokenType::OPEN_CURLY})) { return nullptr; }

    stmt->body = parse_block_stmt();
    if (!stmt->body) { return nullptr; }

    return stmt;
}

AssignStmt* Parser::parse_assign_stmt(Token& name) {
    AssignStmt* stmt = new AssignStmt();

    stmt->left_operand = name;

    stmt->right_operand = parse_expr();
    if (!stmt->right_operand) { return nullptr; }

    return stmt;
}

CallStmt* Parser::parse_call_stmt(Token& name) {
    CallStmt* call_stmt = new CallStmt();

    call_stmt->name = name;

    if (!consumer.match({TokenType::CLOSE_PARENTH})) {
        Expr* expr = parse_expr();
        if (!expr) { return nullptr; }

        call_stmt->args.push_back(expr);

        while (consumer.match({TokenType::COMMA})) {
            expr = parse_expr();
            if (!expr) { return nullptr; }

            call_stmt->args.push_back(expr);
        }

        if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }
    }

    return call_stmt;
}

PrintStmt* Parser::parse_print_stmt() {
    PrintStmt* stmt = new PrintStmt();

    stmt->expr = parse_expr();
    if (!stmt->expr) { return nullptr; }

    return stmt;
}
