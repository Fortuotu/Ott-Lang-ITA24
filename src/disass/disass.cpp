#include "disass/disass.hpp"

void Disassembler::parse_file(std::string& filename) {
    std::vector<std::uint8_t> fc = read_binary_file(filename);

    std::size_t offset = 0;

    std::uint32_t const_tab_size = 0;
    std::uint32_t func_tab_size = 0;

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
    case Opcode::MOD:
        instruction_str = "MOD";
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
    case Opcode::PRINT:
        instruction_str = "PRINT";
        break;
    case Opcode::EXIT:
        instruction_str = "EXIT";
        break;
    default:
        break;
    };

    std::cout << instruction_str << "\n";
}
