#include "compiler/environment/environment.hpp"

void Environment::start_scope() {
    scopes.push_back(std::unordered_set<std::string>());
}

void Environment::start_scope_with(std::vector<Token>& names) {
    start_scope();

    for (Token name : names) {
       define_name(name);
    }
}

void Environment::end_scope() {
    if (scopes.size() == 1) { return; }

    scopes.pop_back();
}

void Environment::define_name(Token name) {
    scopes.back().insert(name.val);
}

bool Environment::is_name_defined(Token name) {
    return scopes.back().find(name.val) != scopes.back().end();
}
