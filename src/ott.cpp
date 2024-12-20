#include "lexer.hpp"
#include "parser.hpp"

int main(void) {
    Lexer lexer;
    Parser parser;
    
    TokenStream tokens;
    lexer.GenerateTokenStream("../test.ott", tokens);

    ASTNode *root = parser.GenerateAST(tokens);

    return 0;
}
