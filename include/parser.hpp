#pragma once

#include <vector>
#include <string>
#include <memory>
#include <variant>

#include "tokens.hpp"
#include "ast.hpp"

class Parser {
private:
    ASTNode* ParseFactor(TokenStream& tokens);
    ASTNode* ParseTerm(TokenStream& tokens);

    ASTNode* ParseExpr(TokenStream& tokens);

    ASTNode* ParseStmt(TokenStream& tokens);
public:
    Parser();
    ~Parser();

    ASTNode* GenerateAST(TokenStream& tokens);
};
