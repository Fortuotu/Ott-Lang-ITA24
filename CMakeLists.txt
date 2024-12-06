# Set the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the project name
project(Ott-Lang)

# Add the include directory to the search path for header files
include_directories(include)

# Add the src directory as a subdirectory
add_subdirectory(src)

# Define the executable in the root directory
add_executable(ott src/ott.cpp)

# Link the compiled libraries (lexer, tokens) to the executable
target_link_libraries(ott lexer tokens)
