#include "compiler/pipeline/parser/parser.hpp"

Expr* Parser::parse_expr() {
    return parse_equality();
}

Expr* Parser::parse_equality() {
    Expr* root = parse_term();
    if (root == nullptr) { return nullptr; }

    if (consumer.match({TokenType::OP_EQUALS, TokenType::OP_NOT_EQUALS, TokenType::OP_GREATER_EQUALS, TokenType::OP_LESS_EQUALS})) {
        Expr* equality = parse_equality();
        if (equality == nullptr) { return nullptr; }

        root = new BinaryExpr(consumer.get_type(), root, equality);
    }

    return root;
}

Expr* Parser::parse_term() {
    Expr* root = parse_factor();
    if (root == nullptr) { return nullptr; }

    if (consumer.match({TokenType::OP_ADD, TokenType::OP_SUB})) {
        Expr* term = parse_term();
        if (term == nullptr) { return nullptr; }

        root = new BinaryExpr(consumer.get_type(), root, term);
    }

    return root;
}

Expr* Parser::parse_factor() {
    Expr* root = parse_unary();
    if (root == nullptr) { return nullptr; }

    if (consumer.match({TokenType::OP_MUL, TokenType::OP_DIV})) {
        Expr* factor = parse_factor();
        if (factor == nullptr) { return nullptr; }

        root = new BinaryExpr(consumer.get_type(), root, factor);
    }

    return root;
}

Expr* Parser::parse_unary() {
    Expr* root = nullptr;

    if (consumer.match({TokenType::OP_NOT, TokenType::OP_SUB})) {
        Expr* unary = parse_unary();
        if (unary == nullptr) { return nullptr; }

        root = new UnaryExpr(consumer.get_type(), unary);
    }
    else {
        root = parse_primary();
    }

    return root;
}

Expr* Parser::parse_primary() {
    Expr* root = nullptr;

    if (consumer.match({TokenType::OPEN_PARENTH})) {
        root = parse_grouping_expr();
        if (!root) { return nullptr; }
    }
    else if (consumer.match({TokenType::IDENTIFIER})) {
        Token idf = consumer.get();

        if (consumer.match({TokenType::OPEN_PARENTH})) {
            root = parse_call_expr();
            if (!root) { return nullptr; }
        }
        else {
            root = new IdfExpr(idf);
        }

        if (!env.is_name_defined(idf)) { env.assure_future_global_def(idf); }
    }
    else if (consumer.match({TokenType::INT_LITERAL})) {
        root = new LiteralExpr(consumer.get());
    }

    return root;
}

CallExpr* Parser::parse_call_expr() {
    CallExpr* call_expr = new CallExpr();

    call_expr->name = consumer.get();

    if (!consumer.match({TokenType::CLOSE_PARENTH})) {
        Expr* expr = parse_expr();
        if (!expr) { return nullptr; }

        call_expr->args.push_back(expr);

        while (consumer.match({TokenType::COMMA})) {
            expr = parse_expr();
            if (!expr) { return nullptr; }

            call_expr->args.push_back(expr);
        }

        if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }
    }

    return call_expr;
}

GroupingExpr* Parser::parse_grouping_expr() {
    Expr* expr = parse_expr();
    if (!expr) { return nullptr; }

    if (!consumer.match({TokenType::CLOSE_PARENTH})) { return nullptr; }

    GroupingExpr* grouping_expr = new GroupingExpr(expr);

    return grouping_expr;
}
