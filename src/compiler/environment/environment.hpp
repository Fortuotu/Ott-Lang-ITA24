#pragma once

#include <string>
#include <unordered_set>

#include "compiler/token/token.hpp"

class DefEnv {
private:
    struct ChildEnv {
        ChildEnv* parent;

        std::unordered_set<std::string> name_definitions;

        ChildEnv(ChildEnv* parent) : parent(parent) {}
    };

    ChildEnv* innermost = nullptr;

    std::unordered_set<std::string> future_globals;

    std::unordered_set<std::string> name_definitions;
public:
    void start_scope();
    void start_scope_with(std::vector<Token> names);
    void end_scope();

    void define_name(Token name);
    bool is_name_defined(Token name);

    void assure_future_global_def(Token name);
    bool all_future_defs_assured();
};
