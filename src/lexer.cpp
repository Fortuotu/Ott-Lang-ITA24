#include "lexer.hpp"

Lexer::Lexer() {

}

Lexer::~Lexer() {

}

void Lexer::ParseToken(std::string& token_str, std::vector<Token>& token_stream) {
    std::cout << token_str << '\n';
}

void Lexer::GenerateTokenStream(std::string filename, std::vector<Token>& token_stream) {
    std::ifstream input_stream(filename);
    Token token;

    while (true) {
        token.value.clear();

        int out_of_tokens = GetNextToken(input_stream, token);
        if (out_of_tokens < 0) {
            return;
        }

        token_stream.push_back(token);
    }
}

inline void Lexer::ParseNextKeyword(std::ifstream& input_stream, Token& token) {
    static std::unordered_map<std::string, TokenType> keywords {
        {"FUNCTION", FUNCTION},
        {"VARIABLE", VARIABLE},
        {"END",      END     },
    };

    char ch = 0;
    char last_ch = 0;

    while (input_stream.get(ch)) {
        if (input_stream.eof())
            return;
        
        if (!std::isalpha(ch) || std::islower(ch)) {
            if (std::isalpha(last_ch) && std::isupper(last_ch))
                break;

            last_ch = ch;

            continue;
        }

        token.value.push_back(ch);

        last_ch = ch;
    }

    token.type = keywords[token.value];

    input_stream.seekg(-1, std::ios::cur);
}

inline void Lexer::ParseNextIdentifier(std::ifstream& input_stream, Token& token) {
    char ch = 0;
    char last_ch = 0;

    while (input_stream.get(ch)) {
        if (input_stream.eof())
            return;
        
        if (!std::isalpha(ch) && ch != '_') {
            if (std::isalpha(last_ch) || last_ch == '_')
                break;

            last_ch = ch;

            continue;
        }

        token.value.push_back(ch);

        last_ch = ch;
    }

    token.type = IDENTIFIER;

    input_stream.seekg(-1, std::ios::cur);
}

int Lexer::GetNextToken(std::ifstream& input_stream, Token& token) {
    static TokenType next_expected_token;

    char ch = 0;

    while (input_stream.get(ch)) {
        if (input_stream.eof())
            return -1;
        
        if (std::isspace(ch)) {
            continue;
        }

        // Parentheses
        if (ch == '(' || ch == ')') {
            token.type = PARENTHESES;
            token.value = ch;
            return 1;
        }

        // Equals combinations
        if (ch == '=') {
            input_stream.get(ch);

            if (ch == '=') {
                token.type = EQUALS;
                token.value = "==";
                return 1;
            }

            token.type = ASSIGN;
            token.value = '=';

            return 1;
        }

        // Keyword
        if (std::isalpha(ch) && std::isupper(ch)) {
            input_stream.seekg(-1, std::ios::cur);

            ParseNextKeyword(input_stream, token);
            return 1;
        }

        // Identifier
        else if (std::isalpha(ch)) {
            input_stream.seekg(-1, std::ios::cur);

            ParseNextIdentifier(input_stream, token);
            return 1;
        }
    }

    return -1;
}
