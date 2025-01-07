cmake_minimum_required(VERSION 3.30)

project(Ott-Lang)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

include_directories(src)

add_subdirectory(src)
