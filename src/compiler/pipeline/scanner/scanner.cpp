#include "compiler/pipeline/scanner/scanner.hpp"

static bool is_space(char ch) {
    return std::isspace(static_cast<unsigned char>(ch));
}

static bool is_print(char ch) {
    return std::isprint(static_cast<unsigned char>(ch));
}

static std::string file_to_string(std::string& filename) {
    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::stringstream buf;
    buf << ifs.rdbuf();

    return buf.str();
}

std::queue<Token> Scanner::tokenize(std::string& filename) {
    fc = file_to_string(filename);

    while (scan_token());

    return std::move(tokens);
}

bool Scanner::get_next_ch() {
    if (fc_idx >= fc.length()) return false;

    ch = fc.at(fc_idx++);

    return true;
}

bool Scanner::match_next_ch(char matching_ch) {
    if (fc_idx >= fc.length()) return false;

    char next_ch = fc.at(fc_idx);

    if (next_ch == matching_ch) {
        ch = next_ch;
        ++fc_idx;

        return true;
    }

    return false;
}

bool Scanner::scan_punctuation() {
    switch (ch) {
    case '=':
        if (match_next_ch('=')) {
            tokens.push(Token(TokenType::OP_EQUALS, "=="));
        } else if (match_next_ch('!')) {
            tokens.push(Token(TokenType::OP_EQUALS, "!="));
        } else {
            tokens.push(Token(TokenType::OP_ASSIGN, "="));
        }
        return true;
    case '>':
        if (match_next_ch('=')) {
            tokens.push(Token(TokenType::OP_GREATER_EQUALS, ">="));
        } else {
            tokens.push(Token(TokenType::OP_GREATER, ">"));
        }
        return true;
    case '<':
        if (match_next_ch('=')) {
            tokens.push(Token(TokenType::OP_LESS_EQUALS, "<="));
        } else {
            tokens.push(Token(TokenType::OP_LESS, "<"));
        }
        return true;
    case '!':
        if (match_next_ch('=')) {
            tokens.push(Token(TokenType::OP_NOT_EQUALS, "!="));
        } else {
            tokens.push(Token(TokenType::OP_NOT, "!"));
        }
        return true;
    default:
        return false;
    }
}

bool Scanner::scan_token() {
    while (get_next_ch()) {
        if (is_space(ch)) {
            continue;
        }

        if (scan_punctuation()) {
            return true;
        }

        return true;
    }

    return false;
}
