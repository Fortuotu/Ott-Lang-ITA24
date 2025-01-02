#include "compiler/pipeline/parser/parser.hpp"

Expr* Parser::parse_expr() {
    return expr_equality();
}

Expr* Parser::expr_equality() {
    Expr* root = expr_term();
    if (root == nullptr) { return nullptr; }

    if (consumer.match({TokenType::OP_EQUALS, TokenType::OP_NOT_EQUALS, TokenType::OP_GREATER_EQUALS, TokenType::OP_LESS_EQUALS})) {
        Expr* equality = expr_equality();
        if (equality == nullptr) { return nullptr; }

        root = new BinaryExpr(consumer.get_type(), root, equality);
    }

    return root;
}

Expr* Parser::expr_term() {
    Expr* root = expr_factor();
    if (root == nullptr) { return nullptr; }

    if (consumer.match({TokenType::OP_ADD, TokenType::OP_SUB})) {
        Expr* term = expr_term();
        if (term == nullptr) { return nullptr; }

        root = new BinaryExpr(consumer.get_type(), root, term);
    }

    return root;
}

Expr* Parser::expr_factor() {
    Expr* root = expr_unary();
    if (root == nullptr) { return nullptr; }

    if (consumer.match({TokenType::OP_MUL, TokenType::OP_DIV})) {
        Expr* factor = expr_factor();
        if (factor == nullptr) { return nullptr; }

        root = new BinaryExpr(consumer.get_type(), root, factor);
    }

    return root;
}

Expr* Parser::expr_unary() {
    Expr* root = nullptr;

    if (consumer.match({TokenType::OP_NOT, TokenType::OP_SUB})) {
        Expr* unary = expr_unary();
        if (unary == nullptr) { return nullptr; }

        root = new UnaryExpr(consumer.get_type(), unary);
    } else {
        root = expr_primary();
    }

    return root;
}

Expr* Parser::expr_primary() {
    Expr* root = nullptr;

    if (consumer.match({TokenType::OPEN_PARENTH})) {
        root = new GroupingExpr(parse_expr());

        if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }
    } else if (consumer.match({TokenType::IDENTIFIER})) {
        root = new IdfExpr(consumer.get());
    } else if (consumer.match({TokenType::INT_LITERAL})) {
        root = new LiteralExpr(consumer.get());
    }

    return root;
}
