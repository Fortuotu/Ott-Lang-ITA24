#pragma once

#include <string>

enum TokenType {
    // Keywords
    FUNCTION,
    VARIABLE,
    END,

    ASSIGN,
    EQUALS,

    IDENTIFIER,
    LITERAL,
    PARENTHESES
};

struct Token {
    TokenType type;
    std::string value;
};
