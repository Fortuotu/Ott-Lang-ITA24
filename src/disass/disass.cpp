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

void Disassembler::diassemble(std::string& filename) {
    bytecode = read_binary_file(filename);

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
