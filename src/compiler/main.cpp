#include "compiler/pipeline/scanner/scanner.hpp"
#include "compiler/pipeline/parser/parser.hpp"
#include "compiler/pipeline/bytecode_gen/compiler.hpp"

int main(void) {
    Scanner scanner;

    std::string filename = "/Users/ott/development/Ott-Lang-ITA24/test.ott";
    std::queue<Token> tokens = scanner.tokenize(filename);

    Parser parser(tokens);
    AST* ast = parser.parse();

    Compiler compiler;
    compiler.compile(ast);

    return EXIT_SUCCESS;
}
