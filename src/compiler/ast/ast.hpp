#pragma once

#include <vector>

#include "compiler/ast/expr.hpp"
#include "compiler/ast/stmt.hpp"

struct AST {
    std::vector<Stmt*> decls;
};
