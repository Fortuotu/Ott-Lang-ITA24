#pragma once

#include <string>

enum TokenType {
    // Keywords
    VARIABLE,
    FUNCTION,
    LABEL,
    IF,
    JUMP,
    END,

    IDENTIFIER,

    INT_LITERAL,
    STRING_LITERAL,

    // Operators
    ASSIGN,
    EQUALS,
    NEGATION,
    NOT_EQUALS,
    BIGGER,
    SMALLER,

    PARENTHESES
};

struct Token {
    TokenType type;
    std::string value;
};
