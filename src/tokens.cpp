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

Token TokenStream::CheckToken() {
    if (selector_ >= tokens_.size()) {
        return end_token_;
    }

    return tokens_[selector_];
}

void TokenStream::SkipToken() {
    selector_++;
}
