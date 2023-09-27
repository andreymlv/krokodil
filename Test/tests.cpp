#include <gtest/gtest.h>

#include "Parser.hpp"
#include "Scanner.hpp"

namespace Krokodil {

TEST(Scanner, EmptyProgram) {
  std::string source = "";
  std::vector<Token> expected{
      {TokenType::EndOfFile, "EOF", std::nullopt, 1},
  };
  Scanner scanner{source};

  EXPECT_EQ(scanner.scan_tokens(), expected);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Scanner, HelloWorld) {
  std::string source =
      "Begin\n"
      "\tprint \"Hello, World!\\n\"\n"
      "End\n";
  std::vector<Token> expected{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::STRING, "\"Hello, World!\\n\"", "Hello, World!\\n", 2},
      {TokenType::END, "End", std::nullopt, 3},
      {TokenType::EndOfFile, "EOF", std::nullopt, 4},
  };
  Scanner scanner{source};

  EXPECT_EQ(scanner.scan_tokens(), expected);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Scanner, ArithmeticOperation) {
  std::string source =
      "Begin\n"
      "\tprint 5 + 3\n"
      "End\n";
  std::vector<Token> expected{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::NUMBER, "5", 5, 2},
      {TokenType::PLUS, "+", std::nullopt, 2},
      {TokenType::NUMBER, "3", 3, 2},
      {TokenType::END, "End", std::nullopt, 3},
      {TokenType::EndOfFile, "EOF", std::nullopt, 4},
  };
  Scanner scanner{source};

  EXPECT_EQ(scanner.scan_tokens(), expected);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Scanner, InvalidToken) {
  std::string source =
      "Begin\n"
      "\tprint @\n"
      "End\n";
  std::vector<Token> expected{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::END, "End", std::nullopt, 3},
      {TokenType::EndOfFile, "EOF", std::nullopt, 4},
  };
  Scanner scanner{source};

  EXPECT_EQ(scanner.scan_tokens(), expected);
  EXPECT_TRUE(scanner.had_error);
}

TEST(Scanner, MultiLineProgram) {
  std::string source =
      "Begin\n"
      "\tprint \"Hello, World!\\n\"\n"
      "\tprint 5 + 3.2\n"
      "End\n";
  std::vector<Token> expected{
      {TokenType::BEGIN, "Begin", std::nullopt, 1},
      {TokenType::PRINT, "print", std::nullopt, 2},
      {TokenType::STRING, "\"Hello, World!\\n\"", "Hello, World!\\n", 2},
      {TokenType::PRINT, "print", std::nullopt, 3},
      {TokenType::NUMBER, "5", 5, 3},
      {TokenType::PLUS, "+", std::nullopt, 3},
      {TokenType::NUMBER, "3.2", 3.2F, 3},
      {TokenType::END, "End", std::nullopt, 4},
      {TokenType::EndOfFile, "EOF", std::nullopt, 5},
  };
  Scanner scanner{source};

  EXPECT_EQ(scanner.scan_tokens(), expected);
  EXPECT_FALSE(scanner.had_error);
}

TEST(Parser, Number) {
  std::string source = "5\n";
  Scanner scanner{source};
  Parser parser{scanner.scan_tokens()};
  nlohmann::json expected{
      {"type", "Program"},
      {
          "body",
          {{"type", "numeric_literal"}, {"value", 5}},
      },
  };
  EXPECT_EQ(parser.program(), expected);
  EXPECT_FALSE(parser.had_error);
}

}  // namespace Krokodil
