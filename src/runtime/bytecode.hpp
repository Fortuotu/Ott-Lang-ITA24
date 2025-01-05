#pragma once

#include <cstdint>

enum class Opcode {
    NO_OP,

    PRINT,
    RET,

    PUSH,
    POP,

    JMP_IFT,
    JMP_IFF,
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