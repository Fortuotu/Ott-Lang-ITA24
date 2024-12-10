#include "lexer.hpp"

char GetNextCharacter(std::ifstream& input_stream) {
    char ch = 0;
    
    input_stream.get(ch);
    if (input_stream.eof())
        return -1;

    return ch;
}

char CheckNextCharacter(std::ifstream& input_stream) {
    char ch = 0;

    input_stream.get(ch);
    if (input_stream.eof())
        return -1;

    input_stream.seekg(-1, std::ios::cur);

    return ch;
}

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

        int e = GetNextToken(input_stream, token);
        if (e < 0) {
            return;
        }

        token_stream.push_back(token);
    }
}

inline void Lexer::ParseNextKeyword(std::ifstream& input_stream, Token& token) {
    static std::unordered_map<std::string, TokenType> keywords = {
        {"FUNCTION", TokenType::FUNCTION},
        {"VARIABLE", TokenType::VARIABLE},
        {"END",      TokenType::END     },
        {"IF",       TokenType::IF      },
        {"JUMP",     TokenType::JUMP    },
        {"LABEL",    TokenType::LABEL   }
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

    token.type = TokenType::IDENTIFIER;

    input_stream.seekg(-1, std::ios::cur);
}

inline void Lexer::ParseNextIntLiteral(std::ifstream& input_stream, Token& token) {
    char ch = 0;
    char last_ch = 0;

    while (input_stream.get(ch)) {
        if (input_stream.eof())
            return;
        
        if (!std::isdigit(ch)) {
            if (std::isdigit(last_ch))
                break;

            last_ch = ch;

            continue;
        }

        token.value.push_back(ch);

        last_ch = ch;
    }

    token.type = TokenType::INT_LITERAL;

    input_stream.seekg(-1, std::ios::cur);
}

inline void Lexer::ParseNextStringLiteral(std::ifstream& input_stream, Token& token) {
    char ch = 0;

    while (input_stream.get(ch)) {
        if (input_stream.eof())
            return;
        
        if (ch == 0x22)
            break;

        token.value.push_back(ch);
    }

    token.type = TokenType::STRING_LITERAL;

    input_stream.seekg(-1, std::ios::cur);
}

int Lexer::GetNextToken(std::ifstream& input_stream, Token& token) {
    char ch = 0;

    while (ch = GetNextCharacter(input_stream)) {
        if (ch < 0)
            break;

        if (std::isspace(ch))
            continue;

        // Fixed length tokens
        switch (ch) {
        case '(':
        case ')':
            token.type = TokenType::PARENTHESES;
            token.value = ch;
            return 1;
        case '=':
            ch = CheckNextCharacter(input_stream);
            if (ch < 0)
                return -1;
            if (ch == '=') {
                token.type = TokenType::EQUALS;
                token.value = "==";

                (void) GetNextCharacter(input_stream);

                return 1;
            }
            token.type = TokenType::ASSIGN;
            token.value = "=";
            return 1;
        case '!':
            ch = CheckNextCharacter(input_stream);
            if (ch < 0)
                return -1;
            if (ch == '=') {
                token.type = TokenType::NOT_EQUALS;
                token.value = "!=";

                (void) GetNextCharacter(input_stream);

                return 1;
            }
            token.type = TokenType::NEGATION;
            token.value = "!";
            return 1;
        case '>':
            token.type = TokenType::BIGGER;
            token.value = ">";
            return 1;
        case '<':
            token.type = TokenType::SMALLER;
            token.value = "<";
            return 1;
        case 0x22:
            // String literal
            ParseNextStringLiteral(input_stream, token);
            return 1;
        default:
            break;
        }

        // Int literal
        if (std::isdigit(ch)) {
            input_stream.seekg(-1, std::ios::cur);

            ParseNextIntLiteral(input_stream, token);
            return 1;
        }

        // Keyword
        else if (std::isalpha(ch) && std::isupper(ch)) {
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
