#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"

int main(void) {
    Lexer lexer;
    Parser parser;
    
    TokenStream tokens;
    lexer.GenerateTokenStream("../test.ott", tokens);

    ASTNode* root = parser.GenerateAST(tokens);
    ExprPrinter printer;
    printer.print((Expr*)root);
    
    return 0;
}
