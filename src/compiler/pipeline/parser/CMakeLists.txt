set(SOURCES
    expr.cpp
    stmt.cpp
    parser.cpp
    parse_analyzer.cpp
)

add_library(parser STATIC ${SOURCES})