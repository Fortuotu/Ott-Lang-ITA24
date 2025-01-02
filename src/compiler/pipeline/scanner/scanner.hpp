#pragma once

// Temporary
#include <iostream>

#include <fstream>
#include <sstream>
#include <regex>
#include <cctype>
#include <queue>
#include <unordered_map>

#include "compiler/token/token.hpp"

class Scanner {
private:
    std::string fc;
    size_t fc_idx = 0;

    char ch = 0;

    std::queue<Token> tokens;

    bool scan_token();
    bool scan_punctuation();
    bool scan_number_literal();
    bool scan_word();

    bool get_next_ch();
    void rewind_ch();
    bool match_next_ch(char matching_ch);
public:
    std::queue<Token> tokenize(std::string& filename);
};
