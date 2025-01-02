#include "compiler/token/token.hpp"

void TokenConsumer::consume(TokenType accepted_type) {
    if (tokens.front().type != accepted_type || out_of_tokens()) {
        std::cout << "Expected a different token after '" << active_token.val << "'.\n";
        std::exit(EXIT_FAILURE);
    }

    active_token = tokens.front();
}

void TokenConsumer::check() {
    if (out_of_tokens()) {
        active_token = Token();

        return;
    }

    active_token = tokens.front();
}

bool TokenConsumer::match(std::initializer_list<TokenType> accepted_types) {
    if (out_of_tokens()) {
        active_token = Token();

        return false;
    }

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

bool TokenConsumer::out_of_tokens() {
    return tokens.empty();
}

Token TokenConsumer::get() {
    return active_token;
}

TokenType TokenConsumer::get_type() {
    return active_token.type;
}
