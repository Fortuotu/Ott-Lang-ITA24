#pragma once

#include <vector>

#include "compiler/token/token.hpp"

struct Expr;

struct FuncDecl;

struct StmtVisitor {
    virtual ~StmtVisitor() = default;
};

struct Stmt {
    virtual ~Stmt() = default;
    virtual void accept(StmtVisitor& visitor) = 0;
};

struct FuncDecl : Stmt {
    Token name;

    std::vector<Expr*> params;
};
