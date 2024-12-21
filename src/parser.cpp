#include "parser.hpp"

#include "iostream"

Parser::Parser() {

}

Parser::~Parser() {
    
}

ASTNode* Parser::GenerateAST(TokenStream& tokens) {
    return ParseExpr(tokens);
}

Expr* Parser::ParseExpr(TokenStream& tokens) {
    return ParseEquality(tokens);
}

Expr* Parser::ParseEquality(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseCondition(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::EQUAL || tok.type == TokenType::NOT_EQUAL) {
        Token operator_ = tokens.ConsumeToken();
        Expr* cond = ParseCondition(tokens);

        root = new BinaryExpr(operator_.type, root, cond);
    }

    return root;
}

Expr* Parser::ParseCondition(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseTerm(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::GREATER || tok.type == TokenType::LESS ||
        tok.type == TokenType::GREATER_OR_EQUAL || tok.type == TokenType::LESS_OR_EQUAL) {
        
        Token operator_ = tokens.ConsumeToken();
        Expr* cond = ParseCondition(tokens);

        root = new BinaryExpr(operator_.type, root, cond);
    }

    return root;
}

Expr* Parser::ParseTerm(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseFactor(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::ADD || tok.type == TokenType::SUBTRACT) {
        Token operator_ = tokens.ConsumeToken();
        Expr* term = ParseTerm(tokens);

        root = new BinaryExpr(operator_.type, root, term);
    }

    return root;
}

Expr* Parser::ParseFactor(TokenStream& tokens) {
    Token tok;

    Expr* root = ParseUnary(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::MULTIPLY || tok.type == TokenType::DIVIDE) {
        Token operator_ = tokens.ConsumeToken();
        Expr* factor = ParseFactor(tokens);

        root = new BinaryExpr(operator_.type, root, factor);
    }

    return root;
}

Expr* Parser::ParseUnary(TokenStream& tokens) {
    Token tok;

    tok = tokens.ConsumeToken();

    Expr* root = nullptr;

    if (tok.type == TokenType::NOT || tok.type == TokenType::NEGATE) {
        root = new UnaryExpr(tok.type, ParseUnary(tokens));

        return root;
    }

    if (tok.type == TokenType::INT_LITERAL) {
        root = new LiteralExpr(tok.type, std::atoi(tok.value.c_str()));
    }

    return root;
}
