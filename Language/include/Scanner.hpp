#pragma once

#include <sstream>
#include <unordered_map>
#include <vector>

#include "Token.hpp"

namespace Krokodil {

/**
 * @brief Tokenizer (lexical analysis).
 *
 * Can be implemented with regular expressions or with manual string scanning.
 */
class Scanner {
 public:
  std::stringstream status_log;
  bool had_error = false;

  /**
   * @brief Ctor.
   *
   * @param[in] source Source code.
   */
  explicit Scanner(std::string source);

  /**
   * @brief Scans the input source code and tokenizes it.
   *
   * @return A vector of tokens representing the scanned input source code.
   */
  auto scan_tokens() -> std::vector<Token>;

 protected:
  /**
   * @brief Checks if the current position is at or beyond the end of the
   * source.
   *
   * @return Returns true if the current position is at or beyond the end of the
   * source, otherwise returns false.
   */
  auto isAtEnd() -> bool;

  /**
   * @brief Advances to the next character in the source.
   *
   * @return Returns the character at the current position before it is
   * incremented.
   * @throws `std::out_of_range` if the current position is out of bounds of the
   * source.
   */
  auto advance() -> char;

  /**
   * @brief Adds a token to the list of tokens.
   *
   * @param[in] type The type of the token to be added.
   * @param[in] literal The literal value of the token to be added.
   */
  void addToken(TokenType type, const Literal& literal);

  /**
   * @brief Adds a token to the list of tokens without a literal value.
   *
   * @param[in] type The type of the token to be added.
   */
  void addToken(TokenType type);

  /**
   * @brief Checks if the current character in the source matches the expected
   * character.
   *
   * @param[in] expected The character we expect to find at the current position
   * in the source.
   * @return Returns true if the current character matches the expected
   * character, otherwise returns false.
   */
  auto match(char expected) -> bool;

  /**
   * @brief Peeks at the current character in the source without advancing.
   *
   * @return Returns the character at the current position in the source, or a
   * null character if we are at the end of the source.
   */
  auto peek() -> char;

  /**
   * @brief Processes a string in the source.
   *
   */
  void string();

  /**
   * @brief Peeks at the next character in the source without advancing.
   *
   * @return Returns the character at the next position in the source, or a null
   * character if we are at or near the end of the source.
   */
  auto peekNext() -> char;

  /**
   * @brief Processes a number in the source.
   *
   */
  void number();

  /**
   * @brief Processes an identifier in the source code.
   *
   */
  void identifier();

  /**
   * @brief Scans a token in the source code and adds it to the token list.
   *
   */
  void scanToken();

 private:
  std::string source;
  std::vector<Token> tokens;
  std::unordered_map<std::string, TokenType> keywords{
      {"else", TokenType::ELSE},     {"False", TokenType::FALSE},
      {"for", TokenType::FOR},       {"fun", TokenType::FUN},
      {"if", TokenType::IF},         {"print", TokenType::PRINT},
      {"return", TokenType::RETURN}, {"True", TokenType::TRUE},
      {"while", TokenType::WHILE},   {"Begin", TokenType::BEGIN},
      {"End", TokenType::END},
  };
  int start = 0;
  int current = 0;
  int line = 1;
};
}  // namespace Krokodil
