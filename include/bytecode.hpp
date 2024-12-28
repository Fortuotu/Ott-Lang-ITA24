#pragma once

enum class Opcode {
    ADD,
    SUB,
    MUL,
    DIV,

    NEG,
    NOT,

    LOAD_CONST,

    STORE_GLOBAL,
    LOAD_GLOBAL,
    STORE_LOC,
    LOAD_LOC,

    PRINT,

    JUMP_IFT,
    JUMP_IFF,

    INC_STACK_PTR,
    DEC_STACK_PTR,

    EXIT,
};

using RtVal = int;

using byte = unsigned char;
