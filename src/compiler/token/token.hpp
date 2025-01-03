#pragma once

#include <iostream>
#include <string>
#include <queue>

enum class TokenType {
    KW_FUNCTION,
    KW_RETURN,
    KW_IF,
    KW_WHILE,
    
    KW_TRUE,
    KW_FALSE,

    OP_NOT,
    OP_AND,
    OP_OR,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,

    OP_GREATER,
    OP_LESS,
    OP_EQUALS,
    OP_NOT_EQUALS,
    OP_GREATER_EQUALS,
    OP_LESS_EQUALS,

    OP_ASSIGN,

    IDENTIFIER,
    INT_LITERAL,

    OPEN_PARENTH,
    CLOSE_PARENTH,
    OPEN_CURLY,
    CLOSE_CURLY,
    COMMA,

    NO_TYPE
};

struct Token {
    TokenType type;

    std::string val;

    Token() : type(TokenType::NO_TYPE) {}
    Token(TokenType type, std::string val) : type(type), val(val) {}

    Token(const Token& other) : type(other.type), val(other.val) {}
    Token(Token&& other) noexcept : type(std::exchange(other.type, TokenType::NO_TYPE)), val(std::move(other.val)) {}

    Token& operator=(Token& other) noexcept {
        if (this != &other) {
            type = other.type;
            val = other.val;
        }

        return *this;
    }

    Token& operator=(Token&& other) noexcept {
        if (this != &other) {
            type = std::exchange(other.type, TokenType::NO_TYPE);
            val = std::move(other.val);
        }

        return *this;
    }
};

class TokenConsumer {
private:
    std::queue<Token> tokens;

    Token active_token;
public:
    TokenConsumer(std::queue<Token>& tokens) : tokens(std::move(tokens)) {}

    void consume();
    void check();
    bool match(std::initializer_list<TokenType> accepted_types);

    bool out_of_tokens();

    Token get();
    TokenType get_type();
};
