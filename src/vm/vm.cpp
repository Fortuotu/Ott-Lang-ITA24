#include "vm/vm.hpp"

void VM::parse_file(std::string& filename) {
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

void VM::run() {
    while (!exited) {
        run_instruction();
    }
}

void VM::run_instruction() {
    switch (get_opcode()) {
    case Opcode::LOAD_CONST: {
        std::uint8_t idx = get_byte();
        push(const_table[idx]);
        break;
    }
    case Opcode::STORE_GLOBAL: {
        std::uint8_t idx = get_byte();
        global_table[idx] = pop();
        break;
    }
    case Opcode::LOAD_GLOBAL: {
        std::uint8_t idx = get_byte();
        push(global_table[idx]);
        break;
    }
    case Opcode::PRINT: {
        std::cout << pop() << std::endl;
        break;
    }
    case Opcode::EXIT: {
        exited = true;
        break;
    }
    default: {
        std::cout << "Unknown instruction, aborting...";
        exited = true;
        break;
    }
    };
}
