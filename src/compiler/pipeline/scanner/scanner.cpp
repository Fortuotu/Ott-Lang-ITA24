#include "compiler/pipeline/scanner/scanner.hpp"

static bool is_space(char ch) {
    return std::isspace(static_cast<unsigned char>(ch));
}

static bool is_print(char ch) {
    return std::isprint(static_cast<unsigned char>(ch));
}

static bool is_digit(char ch) {
    return std::isdigit(static_cast<unsigned char>(ch));
}

static bool is_alpha(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch));
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

    if (get_next_ch()) {
        std::cout << "Syntax error.\n";
        std::exit(EXIT_FAILURE);
    }

    return std::move(tokens);
}

bool Scanner::scan_token() {
    while (get_next_ch()) {
        if (is_space(ch)) {
            continue;
        }

        if (scan_punctuation()) { return true; }
        else if (scan_number_literal()) { return true; }
        else if (scan_word()) { return true; }

        return false;
    }

    return false;
}

bool Scanner::scan_punctuation() {
    switch (ch) {
    case '+':
        tokens.push(Token(TokenType::OP_ADD, "+"));
        return true;
    case '-':
        tokens.push(Token(TokenType::OP_SUB, "-"));
        return true;
    case '*':
        tokens.push(Token(TokenType::OP_MUL, "*"));
        return true;
    case '/':
        tokens.push(Token(TokenType::OP_DIV, "/"));
        return true;
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
    case '(':
        tokens.push(Token(TokenType::OPEN_PARENTH, "("));
        return true;
    case ')':
        tokens.push(Token(TokenType::CLOSE_PARENTH, ")"));
        return true;
    case '{':
        tokens.push(Token(TokenType::OPEN_CURLY, "{"));
        return true;
    case '}':
        tokens.push(Token(TokenType::CLOSE_CURLY, "}"));
        return true;
    default:
        return false;
    }
}

bool Scanner::scan_number_literal() {
    if (!is_digit(ch)) { return false; }

    std::string literal(1, ch);

    while (get_next_ch()) {
        if (!is_digit(ch)) {
            rewind_ch();

            break;
        }

        literal.push_back(ch);
    }

    tokens.push(Token(TokenType::INT_LITERAL, literal));

    return true;
}

bool Scanner::scan_word() {
    static std::unordered_map<std::string, TokenType> reserved_words = {
        { "function", TokenType::KW_FUNCTION },
        { "return",   TokenType::KW_RETURN   },
        { "if",       TokenType::KW_IF       },
        { "while",    TokenType::KW_WHILE    },

        { "true",     TokenType::KW_TRUE     },
        { "false",    TokenType::KW_FALSE    },

        { "not",      TokenType::OP_NOT      },
        { "and",      TokenType::OP_AND      },
        { "or",       TokenType::OP_OR       }
    };

    if (!is_alpha(ch)) { return false; }

    std::string word(1, ch);

    while (get_next_ch()) {
        if (!is_alpha(ch) && !is_digit(ch) && ch != '_') {
            rewind_ch();

            break;
        }

        word.push_back(ch);
    }

    if (reserved_words.count(word) > 0) {
        tokens.push(Token(reserved_words[word], word));
    } else {
        tokens.push(Token(TokenType::IDENTIFIER, word));
    }

    return true;
}

bool Scanner::get_next_ch() {
    if (fc_idx >= fc.length()) return false;

    ch = fc.at(fc_idx++);

    return true;
}

void Scanner::rewind_ch() {
    --fc_idx;
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
