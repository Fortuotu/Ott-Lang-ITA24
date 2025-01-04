#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "compiler/token/token.hpp"

class Environment {
private:
    std::vector<std::unordered_set<std::string>> scopes;
public:
    Environment() : scopes(1) {}

    void start_scope();
    void start_scope_with(std::vector<Token>& names);
    void end_scope();

    void define_name(Token name);
    bool is_name_defined(Token name);
};
