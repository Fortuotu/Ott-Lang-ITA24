#pragma once

#include <vector>
#include <fstream>
#include <cstdint>
#include <stdexcept>

std::vector<std::uint8_t> read_binary_file(const std::string& filename);

std::uint64_t read_uint64(std::vector<std::uint8_t>& data, std::size_t& offset);
std::uint32_t read_uint32(std::vector<std::uint8_t>& data, std::size_t& offset);
std::uint16_t read_uint16(std::vector<std::uint8_t>& data, std::size_t& offset);
std::uint8_t read_uint8(std::vector<std::uint8_t>& data, std::size_t& offset);