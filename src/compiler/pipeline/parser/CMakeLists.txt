set(SOURCES
    expr.cpp
    stmt.cpp
    parser.cpp
)

add_library(parser STATIC ${SOURCES})