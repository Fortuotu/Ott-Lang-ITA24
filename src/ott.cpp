#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"

int main(void) {
    Lexer lexer;
    Parser parser;
    ExprPrinter ep;
    
    TokenStream tokens;
    lexer.GenerateTokenStream("../test.ott", tokens);

    AST* root = parser.GenerateAST(tokens);
    
    

    return 0;
}
