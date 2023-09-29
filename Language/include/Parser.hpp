#pragma once

#include <nlohmann/json.hpp>
#include <optional>
#include <vector>

#include "Token.hpp"
#include "TokenType.hpp"

namespace Krokodil {

/**
 * @brief Parser (syntactic analysis).
 *
 * Implemented with recursive descent.
 */
class Parser {
 public:
  std::stringstream status_log;
  bool had_error = false;

  explicit Parser(std::vector<Token> tokens)
      : tokens(std::move(tokens)), token(nextToken()) {}

  auto program() -> nlohmann::json {
    return {
        declaration(), block(),
        // print(),
    };
  }

  auto accept(TokenType type) -> bool {
    if (token.value().type == type) {
      token = nextToken();
      return true;
    }
    return false;
  }

  auto expect(TokenType type) -> bool {
    if (accept(type)) {
      return true;
    }
    return false;
  }

  auto declaration() -> nlohmann::json {
    nlohmann::json result;
    if (accept(TokenType::IDENTIFIER)) {
      result.emplace_back("");
      do {
        expect(TokenType::IDENTIFIER);
        expect(TokenType::EQUAL);
        expect(TokenType::NUMBER);
      } while (accept(TokenType::COMMA));
    }
    return {};
  }

  auto block() -> nlohmann::json {
    if (accept(TokenType::BEGIN)) {
      do {
      } while (accept(TokenType::COMMA));
      expect(TokenType::SEMICOLON);
      expect(TokenType::END);
    }
    return {};
  }

 private:
  auto nextToken() -> std::optional<Token> {
    std::optional<Token> current;
    try {
      current = tokens.at(index);
    } catch (const std::out_of_range& e) {
      return std::nullopt;
    }
    index++;
    return current;
  }

  std::vector<Token> tokens;
  std::optional<Token> token;
  int index = 0;
};

}  // namespace Krokodil
