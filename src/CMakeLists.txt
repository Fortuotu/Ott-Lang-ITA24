set(SOURCES
    lexer.cpp
    ott.cpp
    tokens.cpp
    parser.cpp
    ast.cpp
)

add_library(lexer lexer.cpp)
add_library(tokens tokens.cpp)
add_library(parser parser.cpp)
add_library(ast ast.cpp)
