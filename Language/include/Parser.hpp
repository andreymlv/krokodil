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

  explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

  auto program() -> nlohmann::json {
    nlohmann::json json;
    json["type"] = "Program";
    json["block"] = block();
    return json;
  }

  auto statements() -> nlohmann::json {
    // TODO(andreymlv): add several statements parsing
    // For now print expects only string
    Literal literal;
    if (!match(TokenType::PRINT)) {
      if ((literal = match(TokenType::STRING)).has_value()) {
        if (!match(TokenType::SEMICOLON)) {
          return {
              {"type", "Statement"},
              {"print", std::get<std::string>(literal.value())},
          };
        }
        had_error = true;
        return {};
      }
      had_error = true;
      return {};
    }
    return {};
  }

  auto block() -> nlohmann::json {
    nlohmann::json json;
    if (!match(TokenType::BEGIN)) {
      if (!match(TokenType::END)) {
        json["type"] = "Block";
        json["statements"] = statements();
        return json;
      } else {
        had_error = true;
        return json;
      }
    }
    had_error = true;
    return json;
  }

 private:
  auto match(TokenType type) -> Literal {
    if (index < tokens.size() && tokens[index].type == type) {
      index += 1;
      return tokens[index - 1].literal;
    }
    return {};
  }

  std::vector<Token> tokens;
  int index = 0;
};

}  // namespace Krokodil
