project(KrokodilLanguage VERSION 0.0.1 LANGUAGES CXX)

set(SOURCES src/Token.cpp src/Scanner.cpp)

add_library(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json)
target_include_directories(${PROJECT_NAME} PUBLIC include/)
target_include_directories(${PROJECT_NAME} PUBLIC ../deps/magic_enum/include/)
