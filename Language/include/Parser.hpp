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

  explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
    if (tokens.empty()) {
      lookahead = std::nullopt;
    } else {
      lookahead = tokens.at(0);
    }
  }

  nlohmann::json program() {
    return {
        {"type", "Program"},
        {"body", numeric_literal()},
    };
  }

  nlohmann::json numeric_literal() {
    auto token = eat(TokenType::NUMBER);
    if (!token.has_value()) {
      status_log << "Error: Expected number." << std::endl;
      had_error = true;
    }
    return {
        {"type", "numeric_literal"},
        {"value", std::get<int>(token.value().literal.value())},
    };
  }

 private:
  std::optional<Token> eat(TokenType type) {
    if (!lookahead.has_value()) {
      return std::nullopt;
    }
    if (isAtEnd()) {
      return std::nullopt;
    }
    lookahead = tokens.at(current);
    if (lookahead.value().type != type) {
      return std::nullopt;
    }
    current += 1;
    return token;
  }

  bool isAtEnd() const { return current == tokens.size(); }

  int current = 0;
  std::vector<Token> tokens;
  std::optional<Token> lookahead;
};

}  // namespace Krokodil
