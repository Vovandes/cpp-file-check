cmake_minimum_required(VERSION 3.16)
project(cpp-file-check LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp-file-check src/main.cpp)

if(MSVC)
    target_compile_options(cpp-file-check PRIVATE /W4 /permissive-)
else()
    target_compile_options(cpp-file-check PRIVATE -Wall -Wextra -Wpedantic)
endif()
