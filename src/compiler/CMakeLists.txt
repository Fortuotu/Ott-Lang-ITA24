add_subdirectory(pipeline)
add_subdirectory(token)
add_subdirectory(environment)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(otc main.cpp)
target_link_libraries(otc PRIVATE parser scanner token environment)