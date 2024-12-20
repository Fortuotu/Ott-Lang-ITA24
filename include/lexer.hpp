#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "tokens.hpp"

class Lexer {
private:
    inline void ParseNextKeyword(std::ifstream& input_stream, Token& token);
    inline void ParseNextIdentifier(std::ifstream& input_stream, Token& token);
    inline void ParseNextIntLiteral(std::ifstream& input_stream, Token& token);
    inline void ParseNextStringLiteral(std::ifstream& input_stream, Token& token);

    int GetNextToken(std::ifstream& input_stream, Token& token);
public:
    Lexer();
    ~Lexer();

    void GenerateTokenStream(std::string filename, TokenStream &token_stream);
};
