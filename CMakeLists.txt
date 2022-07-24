# CMake dependencies
cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# File dependency
file(GLOB HEADERS "./includes/*.hpp")
file(GLOB SOURCES "./sources/*.cpp")

# Project binary type
add_library(library_loader STATIC ${HEADERS} ${SOURCES})

# Project compilation flags
target_compile_options(library_loader PRIVATE -Wall -Wextra -Werror -Wpedantic -g)

# Project dependencies
target_include_directories(library_loader PRIVATE includes)
