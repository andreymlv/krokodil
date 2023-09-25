#include <gtest/gtest.h>

#include "Scanner.hpp"

namespace Krokodil {

TEST(Scanner, EmptyProgram) {
  std::string empty = "";
  std::vector<Token> empty_tokens{
      {TokenType::EndOfFile, "EOF", std::nullopt, 1},
  };
  Scanner scanner{empty};

  EXPECT_EQ(scanner.scan_tokens(), empty_tokens);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Scanner, HelloWorld) {
  std::string hello_world =
      "Begin\n"
      "\tprint \"Hello, World!\\n\"\n"
      "End\n";
  std::vector<Token> hello_world_tokens{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::STRING, "\"Hello, World!\\n\"", "Hello, World!\\n", 2},
      {TokenType::END, "End", std::nullopt, 3},
      {TokenType::EndOfFile, "EOF", std::nullopt, 4},
  };
  Scanner scanner{hello_world};

  EXPECT_EQ(scanner.scan_tokens(), hello_world_tokens);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Scanner, ArithmeticOperation) {
  std::string arithmetic =
      "Begin\n"
      "\tprint 5 + 3\n"
      "End\n";
  std::vector<Token> arithmetic_tokens{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::NUMBER, "5", 5.0F, 2},
      {TokenType::PLUS, "+", std::nullopt, 2},
      {TokenType::NUMBER, "3", 3.0F, 2},
      {TokenType::END, "End", std::nullopt, 3},
      {TokenType::EndOfFile, "EOF", std::nullopt, 4},
  };
  Scanner scanner{arithmetic};

  EXPECT_EQ(scanner.scan_tokens(), arithmetic_tokens);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Scanner, InvalidToken) {
  std::string invalid =
      "Begin\n"
      "\tprint @\n"
      "End\n";
  std::vector<Token> invalid_tokens{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::END, "End", std::nullopt, 3},
      {TokenType::EndOfFile, "EOF", std::nullopt, 4},
  };
  Scanner scanner{invalid};

  EXPECT_EQ(scanner.scan_tokens(), invalid_tokens);
  EXPECT_TRUE(scanner.had_error);
}

TEST(Scanner, MultiLineProgram) {
  std::string multi_line =
      "Begin\n"
      "\tprint \"Hello, World!\\n\"\n"
      "\tprint 5 + 3\n"
      "End\n";
  std::vector<Token> multi_line_tokens{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::STRING, "\"Hello, World!\\n\"", "Hello, World!\\n", 2},
      {TokenType::PRINT, "print", std::nullopt, 3},
      {TokenType::NUMBER, "5", 5.0F, 3},
      {TokenType::PLUS, "+", std::nullopt, 3},
      {TokenType::NUMBER, "3", 3.0F, 3},
      {TokenType::END, "End", std::nullopt, 4},
      {TokenType::EndOfFile, "EOF", std::nullopt, 5},
  };
  Scanner scanner{multi_line};


  EXPECT_EQ(scanner.scan_tokens(), multi_line_tokens);
  EXPECT_FALSE(scanner.had_error);
}

}  // namespace Krokodil
