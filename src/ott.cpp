#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include "compiler.hpp"

int main(void) {
    Lexer lexer;
    Parser parser;
    
    TokenStream tokens;
    lexer.GenerateTokenStream("../test.ott", tokens);

    /*
    while (true) {
        Token t = tokens.ConsumeToken();
        if (t.type == TokenType::TOKENS_END) break;;
        printf("%s      Type: %d\n", t.value.c_str(), (int)t.type);
    }
    printf("\n\n");
    */
   
    AST* root = parser.GenerateAST(tokens);

    Compiler comp(root);
    comp.compile("../test.cott");

    return 0;
}
