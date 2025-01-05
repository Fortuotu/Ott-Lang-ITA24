#pragma once

#include <cstdint>
#include <vector>

#include "runtime/bytecode.hpp"

struct ByteBuffer {
    std::vector<std::uint8_t> bytes;

    std::size_t get_offset() { return bytes.size(); }

    std::size_t write_opcode(Opcode opcode);
    std::size_t write_arg8(std::uint8_t arg);
};
