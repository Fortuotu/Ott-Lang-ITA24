#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

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

class EnvironmentEx {
private:
    std::vector<std::unordered_map<std::string, std::size_t>> scopes;

    std::size_t selected;
    bool selected_scope;
public:
    constexpr static bool GLOBAL_SCOPE = 0;
    constexpr static bool LOCAL_SCOPE = 1;

    EnvironmentEx() : scopes(1) {}

    void start_scope();
    void start_scope_with(std::vector<Token>& names);
    void end_scope();

    void define(Token name);
    bool find_defined(Token name);

    std::size_t get() const { return selected; }
    bool is_global() { return selected_scope == GLOBAL_SCOPE; }
    bool is_local() { return selected_scope == LOCAL_SCOPE; }
};
