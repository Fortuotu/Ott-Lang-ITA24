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
    for (auto& scope : scopes) {
        if (scope.find(name.val) != scope.end()) {
            return true;
        }
    }

    return false;
}

void EnvironmentEx::start_scope() {
    scopes.push_back(std::unordered_map<std::string, std::size_t>());
}

void EnvironmentEx::start_scope_with(std::vector<Token>& names) {
    start_scope();

    for (Token name : names) {
       define(name);
    }
}

void EnvironmentEx::end_scope() {
    if (scopes.size() == 1) { return; }

    scopes.pop_back();
}

void EnvironmentEx::define(Token name) {
    scopes.back().insert(std::make_pair(name.val, scopes.back().size()));

    selected = scopes.back().at(name.val);
}

bool EnvironmentEx::find_defined(Token name) {
    for (auto rit = scopes.rbegin(); rit != scopes.rend() - 1; ++rit) {
        if (rit->find(name.val) != rit->end()) {
            selected = rit->at(name.val);
            selected_scope = LOCAL_SCOPE;

            return true;
        }
    }

    if (scopes.front().find(name.val) != scopes.front().end()) {
        selected = scopes.front().at(name.val);
        selected_scope = GLOBAL_SCOPE;

        return true;
    }

    return false;
}
