#include "file_utils.hpp"

std::vector<std::uint8_t> read_binary_file(const std::string& filename) {
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

std::uint64_t read_uint64(std::vector<std::uint8_t>& data, std::size_t& offset) {
    std::uint64_t value = 0;

    for (std::size_t i = 0; i < sizeof(std::uint64_t); i++) {
        value |= static_cast<std::uint64_t>(data[offset++]) << (i * 8);
    }

    return value;
}

std::uint32_t read_uint32(std::vector<std::uint8_t>& data, std::size_t& offset) {
    std::uint32_t value = 0;

    for (std::size_t i = 0; i < sizeof(std::uint32_t); i++) {
        value |= static_cast<std::uint32_t>(data[offset++]) << (i * 8);
    }

    return value;
}

std::uint16_t read_uint16(std::vector<std::uint8_t>& data, std::size_t& offset) {
    std::uint16_t value = 0;

    for (std::size_t i = 0; i < sizeof(std::uint16_t); i++) {
        value |= static_cast<std::uint16_t>(data[offset++]) << (i * 8);
    }

    return value;
}

std::uint8_t read_uint8(std::vector<std::uint8_t>& data, std::size_t& offset) {
    std::uint8_t value = 0;

    for (std::size_t i = 0; i < sizeof(std::uint8_t); i++) {
        value |= static_cast<std::uint8_t>(data[offset++]) << (i * 8);
    }

    return value;
}
