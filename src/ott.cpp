#include "lexer.hpp"

int main(void) {
    Lexer lexer;

    std::vector<Token> tokens;
    lexer.GenerateTokenStream("test.ott", tokens);

    return 0;
}
