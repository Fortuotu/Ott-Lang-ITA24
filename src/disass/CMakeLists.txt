set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(otd main.cpp disass.cpp)
target_link_libraries(otd file_utils)