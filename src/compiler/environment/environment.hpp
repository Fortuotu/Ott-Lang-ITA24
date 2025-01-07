#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cstdint>

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
    std::uint8_t selected_scope;

    std::uint8_t current_scope() { return scopes.size() == 1 ? GLOBAL_SCOPE : LOCAL_SCOPE; }
public:
    constexpr static std::uint8_t GLOBAL_SCOPE = 0;
    constexpr static std::uint8_t LOCAL_SCOPE = 1;
    constexpr static std::uint8_t NO_SCOPE = 0xff;

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
