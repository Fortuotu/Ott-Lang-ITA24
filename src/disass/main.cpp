#include "disass/disass.hpp"

int main(void) {
    Disassembler disass;

    std::string filename = "../test.cott";
    disass.disassemble(filename);

    return EXIT_SUCCESS;
}
