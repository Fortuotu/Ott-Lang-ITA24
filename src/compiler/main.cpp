#include "compiler/pipeline/scanner/scanner.hpp"
#include "compiler/pipeline/parser/parser.hpp"
#include "compiler/pipeline/bytecode_gen/compiler.hpp"

int main(void) {
    Scanner scanner;

    std::string filename = "/Users/ott/development/Ott-Lang-ITA24/test.ott";
    std::queue<Token> tokens = scanner.tokenize(filename);

    Parser parser(tokens);
    AST* ast = parser.parse();

    std::string output_filename = "/Users/ott/development/Ott-Lang-ITA24/test.cott";

    Compiler compiler;
    compiler.compile(ast);
    compiler.write_to_file(output_filename);

    return EXIT_SUCCESS;
}
