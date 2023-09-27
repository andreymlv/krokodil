project(KrokodilTest VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  ${PROJECT_NAME}
  tests.cpp
)
target_link_libraries(
  ${PROJECT_NAME}
  GTest::gtest_main
  nlohmann_json::nlohmann_json
  KrokodilLanguage
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
