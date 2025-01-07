#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "runtime/bytecode.hpp"
#include "file_utils.hpp"

class Disassembler {
private:
    std::vector<std::uint8_t> bytecode;
    std::size_t offset = 0;

    std::vector<Value> const_table;
    std::vector<std::uint16_t> func_table;

    void parse_file(std::string& filename);

    void disassemble_instruction();

    Opcode get_opcode() { return static_cast<Opcode>(bytecode[offset++]); }
    std::uint8_t get_byte() { return bytecode[offset++]; }
public:
    void disassemble(std::string& filename);
};
