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

    CALL,

    EXIT,
};

using RtVal = int;

using byte = unsigned char;
