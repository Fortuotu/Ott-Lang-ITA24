#include "disass/disass.hpp"

int main(void) {
    Disassembler disass;

    std::string filename = "../test.cott";
    disass.diassemble(filename);

    return EXIT_SUCCESS;
}
