#include "compiler/pipeline/parser/parser.hpp"

Expr* Parser::expr() {
    return expr_equality();
}

Expr* Parser::expr_equality() {
    Expr* root = expr_term();

    if (consumer.validate({TokenType::OP_EQUALS, TokenType::OP_NOT_EQUALS})) {
        root = new BinaryExpr(consumer.get_type(), root, expr_equality());
    }

    return root;
}

Expr* Parser::expr_term() {
    Expr* root = expr_factor();

    if (consumer.validate({TokenType::OP_ADD, TokenType::OP_SUB})) {
        root = new BinaryExpr(consumer.get_type(), root, expr_term());
    }

    return root;
}

Expr* Parser::expr_factor() {
    Expr* root = expr_unary();

    if (consumer.validate({TokenType::OP_MUL, TokenType::OP_DIV})) {
        root = new BinaryExpr(consumer.get_type(), root, expr_factor());
    }

    return root;
}

Expr* Parser::expr_unary() {
    Expr* root = nullptr;

    if (consumer.validate({TokenType::OP_NOT, TokenType::OP_SUB})) {
        root = new UnaryExpr(consumer.get_type(), expr_unary());
    }

    root = expr_primary();

    return root;
}

Expr* Parser::expr_primary() {
    Expr* root = nullptr;

    if (consumer.validate({TokenType::OPEN_PARENTH})) {
        root = expr();

        consumer.consume(TokenType::CLOSE_PARENTH);
    } else if (consumer.validate({TokenType::IDENTIFIER})) {
        root = new IdfExpr(consumer.get());
    } else if (consumer.validate({TokenType::INT_LITERAL})) {
        root = new LiteralExpr(consumer.get());
    }

    return root;
}
