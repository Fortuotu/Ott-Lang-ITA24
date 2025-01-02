#include "compiler/pipeline/scanner/scanner.hpp"
#include "compiler/pipeline/parser/parser.hpp"

static void debug_print_tokens_exit(std::queue<Token> tokens) {
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

    std::string filename = "/Users/ott/Downloads/Ott-Lang-ITA24/test.ott";
    std::queue<Token> tokens = scanner.tokenize(filename);

    Parser parser(tokens);
    Expr* ast = parser.parse();

    if (ast == nullptr) {
        std::cout << "Invalid expression.\n";
        std::exit(EXIT_SUCCESS);
    }

    std::cout << ast << '\n';

    return EXIT_SUCCESS;
}
