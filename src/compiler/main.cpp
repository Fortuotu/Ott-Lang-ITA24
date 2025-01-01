#include "compiler/pipeline/scanner/scanner.hpp"
#include "compiler/pipeline/parser/parser.hpp"

int main(void) {
    Scanner scanner;

    std::string filename = "/Users/ott/Downloads/Ott-Lang-ITA24/test.oer";
    std::queue<Token> tokens = scanner.tokenize(filename);

    Parser parser(tokens);

    return EXIT_SUCCESS;
}
