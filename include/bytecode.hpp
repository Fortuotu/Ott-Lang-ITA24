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
    PRINT,
};

using RtVal = int;

using byte = unsigned char;
