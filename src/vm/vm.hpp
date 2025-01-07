#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include <string>
#include <array>

#include "runtime/bytecode.hpp"
#include "file_utils.hpp"

class VM {
private:
    std::vector<Value> const_table;
    std::vector<std::uint16_t> func_table;
    std::vector<std::uint8_t> bytecode;

    constexpr static std::size_t MAX_STACK = 256;
    std::array<Value, MAX_STACK> stack;
    std::size_t sp = 0;
    std::size_t ip = 0;

    constexpr static std::size_t MAX_GLOBAL = 256;
    std::array<Value, MAX_GLOBAL> global_table;

    bool exited = false;

    Opcode get_opcode() { return static_cast<Opcode>(bytecode[ip++]); }
    std::uint8_t get_byte() { return bytecode[ip++]; }

    void push(Value val) { stack[sp++] = val; }
    Value pop() { return stack[--sp]; }

    void run_instruction();

    void parse_file(std::string& filename);
public:
    void init(std::string& filename) { parse_file(filename); }
    void run();
};
