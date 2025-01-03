#include "compiler/environment/environment.hpp"

void DefEnv::start_scope() {
    innermost = new ChildEnv(innermost);
}

void DefEnv::start_scope_with(std::vector<Token> names) {
    start_scope();

    for (Token& name : names) {
        define_name(name);
    }
}

void DefEnv::end_scope() {
    ChildEnv* parent = innermost->parent;

    delete innermost;

    innermost = parent;
}

void DefEnv::define_name(Token name) {
    if (innermost == nullptr) {
        if (future_globals.count(name.val) > 0) {
            future_globals.erase(name.val);
        }

        name_definitions.insert(name.val);

        return;
    }

    innermost->name_definitions.insert(name.val);
}

bool DefEnv::is_name_defined(Token name) {
    if (name_definitions.count(name.val) != 0) return true;

    ChildEnv* scope = innermost;

    while (scope != nullptr) {
        if (scope->name_definitions.count(name.val) != 0) return true;

        scope = scope->parent;
    }

    return false;
}

void DefEnv::assure_future_global_def(Token name) {
    future_globals.insert(name.val);
}

bool DefEnv::all_future_defs_assured() {
    return future_globals.empty();
}
