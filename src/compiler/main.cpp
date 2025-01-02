#include "compiler/pipeline/scanner/scanner.hpp"
#include "compiler/pipeline/parser/parser.hpp"

int main(void) {
    Scanner scanner;

    std::string filename = "/Users/ott/Downloads/Ott-Lang-ITA24/test.ott";
    std::queue<Token> tokens = scanner.tokenize(filename);

    
    Token token;
    while (tokens.size() > 0) {
        token = tokens.front();
        tokens.pop();

        std::cout << token.val << " -> " << (int)token.type << '\n';
    }
    

    Parser parser(tokens);

    return EXIT_SUCCESS;
}
