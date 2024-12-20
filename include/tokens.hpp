#pragma once

#include <vector>
#include <string>

enum class TokenType {
    VARIABLE,
    FUNCTION,
    IF,
    WHILE,
    END,
    RETURN,

    IDENTIFIER,
    INT_LITERAL,
    STRING_LITERAL,

    NOT,
    NEGATE,

    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULUS,
    
    ASSIGN,

    EQUAL,
    NOT_EQUAL,
    GREATER,
    LESS,
    GREATER_OR_EQUAL,
    LESS_OR_EQUAL,

    PARENTHESES,
    COMMA,

    TOKENS_END
};

struct Token {
    TokenType type;
    std::string value;
};

class TokenStream {
private:
    std::vector<Token> tokens_;
    size_t selector_ = 0;

    Token end_token_;
public:
    TokenStream();

    std::vector<Token>& InternalVector();

    Token ConsumeToken();
    Token CheckToken();
    void SkipToken();
};
