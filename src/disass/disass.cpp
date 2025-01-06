#include "disass/disass.hpp"

static std::vector<std::uint8_t> read_binary_file(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file");
    }

    file.seekg(0, std::ios::end);
    std::streamsize file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<std::uint8_t> data(file_size);
    if (!file.read(reinterpret_cast<char*>(data.data()), file_size)) {
        throw std::runtime_error("Error reading file data");
    }

    return data;
}

static uint64_t read_uint64(std::vector<std::uint8_t>& data, std::size_t& offset) {
    uint64_t value = 0;

    for (std::size_t i = 0; i < sizeof(uint64_t); i++) {
        value |= static_cast<uint64_t>(data[offset++]) << (i * 8);
    }

    offset += sizeof(uint64_t);

    return value;
}

static uint32_t read_uint32(std::vector<std::uint8_t>& data, std::size_t& offset) {
    uint32_t value = 0;

    for (std::size_t i = 0; i < sizeof(uint32_t); i++) {
        value |= static_cast<uint32_t>(data[offset++]) << (i * 8);
    }

    offset += sizeof(uint32_t);

    return value;
}

static uint16_t read_uint16(std::vector<std::uint8_t>& data, std::size_t& offset) {
    uint16_t value = 0;

    for (std::size_t i = 0; i < sizeof(uint16_t); i++) {
        value |= static_cast<uint16_t>(data[offset++]) << (i * 8);
    }

    offset += sizeof(uint16_t);

    return value;
}

static uint8_t read_uint8(std::vector<std::uint8_t>& data, std::size_t& offset) {
    uint8_t value = 0;

    for (std::size_t i = 0; i < sizeof(uint8_t); i++) {
        value |= static_cast<uint8_t>(data[offset++]) << (i * 8);
    }

    offset += sizeof(uint8_t);

    return value;
}

void Disassembler::parse_file(std::string& filename) {
    std::vector<std::uint8_t> fc = read_binary_file(filename);

    std::size_t offset = 0;

    std::size_t const_tab_size = 0;
    std::size_t func_tab_size = 0;

    const_tab_size = read_uint32(fc, offset);
    const_table.reserve(const_tab_size);

    func_tab_size = read_uint32(fc, offset);
    func_table.reserve(func_tab_size);

    for (std::size_t i = 0; i < const_tab_size; ++i) {
        const_table.push_back(read_uint64(fc, offset));
    }

    for (std::size_t i = 0; i < func_tab_size; ++i) {
        func_table.push_back(read_uint16(fc, offset));
    }

    while (offset < fc.size()) {
        bytecode.push_back(read_uint8(fc, offset));
    }
}

void Disassembler::disassemble(std::string& filename) {
    parse_file(filename);

    while (offset < bytecode.size()) {
        disassemble_instruction();
    }
}

void Disassembler::disassemble_instruction() {
    std::size_t instruction_offset = offset;
    std::string instruction_str;

    switch (get_opcode()) {
    case Opcode::ADD:
        instruction_str = "ADD";
        break;
    case Opcode::SUB:
        instruction_str = "SUB";
        break;
    case Opcode::MUL:
        instruction_str = "MUL";
        break;
    case Opcode::DIV:
        instruction_str = "DIV";
        break;
    case Opcode::LOAD_CONST:
        instruction_str = "LOAD_CONST " + std::to_string(get_byte());
        break;
    case Opcode::STORE_GLOBAL:
        instruction_str = "STORE_GLOBAL " + std::to_string(get_byte());
        break;
    case Opcode::LOAD_GLOBAL:
        instruction_str = "LOAD_GLOBAL " + std::to_string(get_byte());
        break;
    case Opcode::STORE_LOCAL:
        instruction_str = "STORE_LOCAL " + std::to_string(get_byte());
        break;
    case Opcode::LOAD_LOCAL:
        instruction_str = "LOAD_LOCAL " + std::to_string(get_byte());
        break;
    case Opcode::JUMP_IF_TRUE:
        instruction_str = "JUMP_IF_TRUE " + std::to_string(get_byte());
        break;
    case Opcode::JUMP_IF_FALSE:
        instruction_str = "JMP_IF_FALSE " + std::to_string(get_byte());
        break;
    case Opcode::CALL:
        instruction_str = "CALL " + std::to_string(get_byte()) + ", " + std::to_string(get_byte());
        break;
    case Opcode::RET:
        instruction_str = "RET";
        break;
    default:
        break;
    };

    std::cout << instruction_str << "\n";
}
