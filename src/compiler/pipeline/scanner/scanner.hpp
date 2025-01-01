#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

#include "compiler/token/token.hpp"

class Scanner {
private:
    std::queue<Token> tokens;
public:
    std::queue<Token> tokenize(std::string& filename);
};
