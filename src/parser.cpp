#include "parser.hpp"

#include "iostream"

Parser::Parser() {

}

Parser::~Parser() {
    
}

ASTNode* Parser::GenerateAST(TokenStream& tokens) {
    return ParseExpr(tokens);
}

ASTNode* Parser::ParseExpr(TokenStream& tokens) {
    return ParseTerm(tokens);
}

ASTNode* Parser::ParseTerm(TokenStream& tokens) {
    Token tok;

    ASTNode* root = ParseFactor(tokens);

    tok = tokens.CheckToken();
    if (tok.type == TokenType::ADD || tok.type == TokenType::SUBTRACT) {
        Token operator_ = tokens.ConsumeToken();
        ASTNode *term = ParseTerm(tokens);

        root = new BinaryExpr(operator_.type, root, term);
    }

    return root;
}

ASTNode* Parser::ParseFactor(TokenStream& tokens) {
    Token tok;

    tok = tokens.ConsumeToken();

    ASTNode* root = new LiteralExpr(TokenType::INT_LITERAL, std::atoi(tok.value.c_str()));

    tok = tokens.CheckToken();
    if (tok.type == TokenType::MULTIPLY || tok.type == TokenType::DIVIDE) {
        Token operator_ = tokens.ConsumeToken();
        ASTNode* factor = ParseFactor(tokens);

        root = new BinaryExpr(operator_.type, root, factor);
    }

    return root;
}
