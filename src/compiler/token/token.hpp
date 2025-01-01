#pragma once

#include <string>
#include <queue>
#include <stdexcept>

enum class TokenType {
    KW_FUNCTION,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_EQUALS,
    OP_NOT_EQUALS,
    OP_GREATER,
    OP_LESS,
    OP_GREATER_EQUALS,
    OP_LESS_EQUALS,
    OP_ASSIGN,

    OP_NOT,
    OP_AND,
    OP_OR,

    IDENTIFIER,
    INT_LITERAL,

    OPEN_PARENTH,
    CLOSE_PARENTH,

    NO_TYPE
};

struct Token {
    TokenType type;

    std::string val;

    Token() : type(TokenType::NO_TYPE) {}
    Token(TokenType type, std::string val) : type(type), val(val) {}
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

    void consume(TokenType accepted_type);
    void check();
    bool validate(std::initializer_list<TokenType> accepted_types);

    Token get();
    TokenType get_type();
};
