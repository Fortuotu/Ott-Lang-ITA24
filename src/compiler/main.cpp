#include "compiler/pipeline/scanner/scanner.hpp"
#include "compiler/pipeline/parser/parser.hpp"

static void debug_print_tokens(std::queue<Token> tokens) {
    Token token;

    std::cout << '\n';

    while (tokens.size() > 0) {
        token = tokens.front();
        tokens.pop();

        std::cout << token.val << " -> " << (int)token.type << '\n';
    }

    std::cout << '\n';
}

int main(void) {
    Scanner scanner;

    std::string filename = "/Users/ott/development/Ott-Lang-ITA24/test.ott";
    std::queue<Token> tokens = scanner.tokenize(filename);

    debug_print_tokens(tokens);

    Parser parser(tokens);
    AST* ast = parser.parse();

    return EXIT_SUCCESS;
}
