#include "bytecode.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <utility>

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
            printf("PRINT\n");
            break;
        case Opcode::LOAD_CONST:
            printf("LOAD_CONST %d\n", (int)bytes[++offset]);
            break;
        case Opcode::ADD:
            printf("ADD\n");
            break;
        case Opcode::SUB:
            printf("SUB\n");
            break;
        case Opcode::MUL:
            printf("MUL\n");
            break;
        case Opcode::DIV:
            printf("DIV\n");
            break;
        case Opcode::STORE_GLOBAL:
            printf("STORE_GLOBAL %d\n", (int)bytes[++offset]);
            break;
        case Opcode::LOAD_GLOBAL:
            printf("LOAD_GLOBAL %d\n", (int)bytes[++offset]);
            break;
        default:
            break;
        }

        ++offset;
    }
}

/*
file_format:
    constant_table_size: 4 bytes,
    code_size: 4 bytes,
    constant_table: 'constant_table_size' bytes,
    code: 'code_size' bytes
*/
int main(int argc, char* argv[]) {
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
