cmake_minimum_required(VERSION 3.14)

project(serial-port LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

add_compile_options(-Wall -Werror)

include_directories("${PROJECT_SOURCE_DIR}/inc")

add_executable(serial-port tests.cpp)
