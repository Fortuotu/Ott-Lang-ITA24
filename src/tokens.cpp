#include "tokens.hpp"

TokenStream::TokenStream() {
    end_token_.type = TokenType::TOKENS_END;
}

std::vector<Token>& TokenStream::InternalVector() {
    return tokens_;
}

Token TokenStream::ConsumeToken() {
    if (selector_ >= tokens_.size()) {
        return end_token_;
    }

    return tokens_[selector_++];
}

Token TokenStream::ValidateToken(TokenType tt) {
    Token t = ConsumeToken();

    if (t.type != tt) {
        return end_token_;
    }

    return t;
}

Token TokenStream::CheckToken() {
    if (selector_ >= tokens_.size()) {
        return end_token_;
    }

    return tokens_[selector_];
}
