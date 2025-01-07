set(SOURCES
    file_utils.cpp
)

add_library(file_utils STATIC ${SOURCES})

add_subdirectory(compiler)
add_subdirectory(disass)
add_subdirectory(vm)