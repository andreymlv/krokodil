cmake_minimum_required(VERSION 3.23)

project(krokodil VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(Language)
add_subdirectory(CLI)
add_subdirectory(GUI)
