#include "vm/vm.hpp"

int main(void) {
    VM vm;

    std::string filename = "../test.cott";
    vm.init(filename);

    vm.run();

    return EXIT_SUCCESS;
}
