cmake_minimum_required(VERSION 3.23)

project(krokodil VERSION 0.0.1 LANGUAGES CXX)

include(CPack)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

# Disable tests for json library
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(deps/json)

add_subdirectory(deps/magic_enum)
add_subdirectory(Language)
add_subdirectory(CLI)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(deps/glfw)
add_subdirectory(GUI)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
  add_subdirectory(Test)
endif()

