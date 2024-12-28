#include "bytecode.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

void print_bytes(std::vector<byte>& bytes, int off, int count) {
    static char buf[255];

    if (count == 1) {
        snprintf(buf, 255, "%02x      ", bytes[off]);
    } else if (count == 2) {
        snprintf(buf, 255, "%02x %02x   ", bytes[off], bytes[off + 1]);
    } else {
        snprintf(buf, 255, "%02x %02x %02x", bytes[off], bytes[off + 1], bytes[off + 2]);
    }

    printf("%s", buf);
}

// Function to read a binary file into a vector of bytes
std::vector<unsigned char> readFileToVector(const char* filename) {
    // Open the binary file for reading
    std::ifstream inFile(filename, std::ios::binary);

    // Check if the file is open
    if (!inFile) {
        std::cerr << "Error opening file: " << filename << " for reading!" << std::endl;
        return {}; // Return an empty vector in case of error
    }

    // Move to the end of the file to get its size
    inFile.seekg(0, std::ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg); // Go back to the beginning of the file

    // Resize the vector to hold all the bytes from the file
    std::vector<unsigned char> byteVector(fileSize);

    // Read the bytes into the vector
    inFile.read(reinterpret_cast<char*>(byteVector.data()), fileSize);

    // Check if the read was successful
    if (!inFile) {
        std::cerr << "Error reading from file!" << std::endl;
        return {}; // Return an empty vector in case of error
    }

    // Close the file
    inFile.close();

    // Return the vector containing the file data
    return std::move(byteVector);
}

void disass(std::vector<byte>& bytes, int off) {
    int offset = off;

    while (offset < bytes.size()) {
        printf("    ");
        switch ((Opcode)bytes[offset]) {
        case Opcode::PRINT:
            print_bytes(bytes, offset, 1);
            printf("PRINT\n");
            break;
        case Opcode::LOAD_CONST:
            print_bytes(bytes, offset, 2);
            printf("LOAD_CONST %d\n", (int)bytes[++offset]);
            break;
        case Opcode::ADD:
            print_bytes(bytes, offset, 1);
            printf("ADD\n");
            break;
        case Opcode::SUB:
            print_bytes(bytes, offset, 1);
            printf("SUB\n");
            break;
        case Opcode::MUL:
            print_bytes(bytes, offset, 1);
            printf("MUL\n");
            break;
        case Opcode::DIV:
            print_bytes(bytes, offset, 1);
            printf("DIV\n");
            break;
        case Opcode::STORE_GLOBAL:
            print_bytes(bytes, offset, 2);
            printf("STORE_GLOBAL %d\n", (int)bytes[++offset]);
            break;
        case Opcode::LOAD_GLOBAL:
            print_bytes(bytes, offset, 2);
            printf("LOAD_GLOBAL %d\n", (int)bytes[++offset]);
            break;
        case Opcode::JUMP_IFF:
            print_bytes(bytes, offset, 2);
            printf("JUMP_IFF %d\n", (int)bytes[++offset]);
            break;
        case Opcode::JUMP_IFT:
            print_bytes(bytes, offset, 2);
            printf("JUMP_IFT %d\n", (int)bytes[++offset]);
            break;
        case Opcode::EXIT:
            print_bytes(bytes, offset, 1);
            printf("EXIT\n");
            break;
        case Opcode::STORE_LOC:
            print_bytes(bytes, offset, 2);
            printf("STORE_LOC %d\n", (int)bytes[++offset]);
            break;
        case Opcode::LOAD_LOC:
            print_bytes(bytes, offset, 2);
            printf("LOAD_LOC %d\n", (int)bytes[++offset]);
            break;
        default:
            break;
        }

        ++offset;
    }
}

int main(int argc, char* argv[]) {
    /*
    file_format:
        constant_table_size: 4 bytes,
        code_size: 4 bytes,
        constant_table: 'constant_table_size' bytes,
        code: 'code_size' bytes
    */

    auto bytes = readFileToVector("../test.cott");

    unsigned int header_size = 0x8;
    unsigned int const_table_size = (unsigned int)bytes[0];
    unsigned int code_size = (unsigned int)bytes[4];

    printf("HEADER:\n");
    printf("    CONST_TABLE_SIZE: %d entries\n", const_table_size);
    printf("    CODE_SIZE: %d bytes\n", code_size);

    printf("\n");

    printf("CONST_TABLE:\n");
    for (int i = 0; i < const_table_size; ++i) {
        printf("    %d -> %d\n", i, bytes[header_size + i * sizeof(RtVal)]);
    }

    printf("\n");
    printf("CODE:\n");
    int off = header_size + const_table_size * sizeof(RtVal);
    disass(bytes, off);

    return 0;
}
