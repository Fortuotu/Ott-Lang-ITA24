#include "compiler/pipeline/scanner/scanner.hpp"

static std::string file_to_string(std::string& filename) {
    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::stringstream buf;
    buf << ifs.rdbuf();

    return buf.str();
}

std::queue<Token> Scanner::tokenize(std::string& filename) {
    std::string file_contents = file_to_string(filename);

    std::cout << file_contents;

    return std::move(tokens);
}
