#include "parser.hpp"

#include "iostream"

Parser::Parser() {

}

Parser::~Parser() {
    
}

AST* Parser::GenerateAST(TokenStream& tokens) {
    Token tok;

    AST* ast = new AST();

    while (true) {
        tok = tokens.CheckToken();
        if (tok.type == TokenType::TOKENS_END) {
            return ast;
        }

        ast->stmts.push_back(ParseStmt(tokens));
    }
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

    Expr* root = nullptr;

    tok = tokens.CheckToken();
    if (tok.type == TokenType::NOT || tok.type == TokenType::SUBTRACT) {
        root = new UnaryExpr(tok.type, ParseUnary(tokens));

        return root;
    }

    root = ParseGrouping(tokens);

    return root;
}

Expr* Parser::ParseGrouping(TokenStream& tokens) {
    Token tok;

    Expr* root = nullptr;

    tok = tokens.ConsumeToken();

    if (tok.type == TokenType::OPEN_PARENTHESES) {
        root = new GroupingExpr(ParseExpr(tokens));

        tok = tokens.ConsumeToken();
        if (tok.type != TokenType::CLOSE_PARENTHESES) {
            // error
            std::cout << "Expected closing parentheses\n";
            exit(1);
        }
        return root;
    }

    if (tok.type == TokenType::INT_LITERAL) {
        root = new LiteralExpr(tok.type, std::atoi(tok.value.c_str()));
    }

    return root;
}

Stmt* Parser::ParseStmt(TokenStream& tokens) {
    Token tok;

    tok = tokens.CheckToken();

    switch (tok.type) {
    case TokenType::PRINT:
        return ParsePrint(tokens);
    default:
        break;
    }

    return nullptr;
}

Stmt* Parser::ParsePrint(TokenStream& tokens) {
    Token tok;

    tok = tokens.ConsumeToken(); // Consume 'PRINT' token
    tok = tokens.ConsumeToken(); // Consume '(' token

    Stmt* root = new PrintStmt(ParseExpr(tokens));

    tok = tokens.ConsumeToken(); // Consume ')' token

    return root;
}
