#include "compiler/pipeline/bytecode_gen/byte_buffer.hpp"

std::size_t ByteBuffer::write_opcode(Opcode opcode) {
    bytes.push_back(static_cast<std::uint8_t>(opcode));

    return get_last_idx();
}

std::size_t ByteBuffer::write_arg8(std::uint8_t arg) {
    bytes.push_back(arg);

    return get_last_idx();
}

void ByteBuffer::backpatch_arg8(std::size_t idx, std::uint8_t val) {
    bytes[idx] = val;
}
