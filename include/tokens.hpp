#pragma once

#include <vector>
#include <string>

enum class TokenType {
    VAR,
    FUNCTION,
    IF,
    WHILE,
    THEN,
    END,
    RETURN,
    PRINT,

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

    OPEN_PARENTHESES,
    CLOSE_PARENTHESES,
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
    Token ValidateToken(TokenType tt);
    Token CheckToken();
};
