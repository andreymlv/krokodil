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
  tokenizer
  tokenizer.cpp
)
target_link_libraries(
  tokenizer
  GTest::gtest_main
  KrokodilLanguage
)

include(GoogleTest)
gtest_discover_tests(tokenizer)
