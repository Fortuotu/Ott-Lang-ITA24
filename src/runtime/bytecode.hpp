#pragma once

#include <cstdint>

enum class Opcode {
    NO_OP,

    PRINT,
    RET,

    PUSH,
    POP,

    JUMP_IF_TRUE,
    JUMP_IF_FALSE,
    CALL,

    LOAD_CONST,

    STORE_GLOBAL,
    LOAD_GLOBAL,

    STORE_LOCAL,
    LOAD_LOCAL,

    ADD,
    SUB,
    MUL,
    DIV,
    NEG,

    GT,
    LT,
    EQ,
    NEQ,
    GTE,
    LTE,

    AND,
    OR,
    NOT
};

using Value = std::int64_t;
