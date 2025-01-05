#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "runtime/bytecode.hpp"

class Disassembler {
private:
    std::vector<std::uint8_t> bytecode;
    std::size_t offset = 0;

    void disassemble_instruction();

    Opcode get_opcode() { return static_cast<Opcode>(bytecode[offset++]); }
    std::uint8_t get_byte() { return bytecode[offset++]; }
public:
    void diassemble(std::string& filename);
};
