#pragma once

#include <vector>
#include <string>
#include <memory>
#include <variant>

#include "tokens.hpp"
#include "ast.hpp"

class Parser {
private:
    Expr* ParseGrouping(TokenStream& tokens);
    Expr* ParseUnary(TokenStream& tokens);
    Expr* ParseFactor(TokenStream& tokens);
    Expr* ParseTerm(TokenStream& tokens);
    Expr* ParseCondition(TokenStream& tokens);
    Expr* ParseEquality(TokenStream& tokens);

    Expr* ParseExpr(TokenStream& tokens);
public:
    Parser();
    ~Parser();

    ASTNode* GenerateAST(TokenStream& tokens);
};
