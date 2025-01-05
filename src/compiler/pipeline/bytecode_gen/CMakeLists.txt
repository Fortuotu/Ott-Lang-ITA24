set(SOURCES
    compiler.cpp
    byte_buffer.cpp
)

add_library(bytecode_gen STATIC ${SOURCES})