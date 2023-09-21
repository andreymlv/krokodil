project(KrokodilLanguage VERSION 0.0.1 LANGUAGES CXX)

set(SOURCES src/Token.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PUBLIC ../deps/magic_enum/include/)
