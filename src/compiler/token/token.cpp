#include "compiler/token/token.hpp"

void TokenConsumer::consume(TokenType accepted_type) {
    if (tokens.front().type != accepted_type) {
        throw "Temporary placeholder.";
    }

    active_token = std::move(tokens.front());

    tokens.pop();
}

void TokenConsumer::check() {
    active_token = tokens.front();
}

bool TokenConsumer::validate(std::initializer_list<TokenType> accepted_types) {
    TokenType next_type = tokens.front().type;

    for (TokenType type : accepted_types) {
        if (next_type == type) {
            active_token = std::move(tokens.front());

            tokens.pop();

            return true;
        }
    }

    return false;
}

Token TokenConsumer::get() {
    return std::move(active_token);
}

TokenType TokenConsumer::get_type() {
    return active_token.type;
}
