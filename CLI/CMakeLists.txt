project(KrokodilCLI VERSION 0.0.1 LANGUAGES CXX)

set(SOURCES src/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC KrokodilLanguage)
