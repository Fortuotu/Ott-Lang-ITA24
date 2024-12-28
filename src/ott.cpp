#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include "compiler.hpp"

int main(void) {
    Lexer lexer;
    Parser parser;
    
    TokenStream tokens;
    lexer.GenerateTokenStream("../test.ott", tokens);

    AST* root = parser.GenerateAST(tokens);
    
    Compiler comp(root);
    comp.compile("../test.cott");

    return 0;
}
