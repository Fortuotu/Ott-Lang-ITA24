#include "lexer.hpp"
#include "parser.hpp"
#include "ast.hpp"
#include "runtime.hpp"

int main(void) {
    Lexer lexer;
    Parser parser;

    ExprPrinter ep;
    
    TokenStream tokens;
    lexer.GenerateTokenStream("../test.ott", tokens);

    AST* root = parser.GenerateAST(tokens);
    
    Interpreter inter(root);
    inter.exec();

    return 0;
}
