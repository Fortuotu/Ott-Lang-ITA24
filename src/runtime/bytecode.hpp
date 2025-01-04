#pragma once

enum class Opcode {
    NO_OP,

    PRINT,
    RET,

    PUSH,
    POP,

    LOAD_CONST,

    ADD,
    SUB,
    MUL,
    DIV,

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

struct RuntimeValue {
    int val;
};
