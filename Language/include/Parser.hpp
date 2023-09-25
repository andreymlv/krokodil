#pragma once

#include <nlohmann/json.hpp>
#include <vector>

#include "Token.hpp"

namespace Krokodil {

/**
 * @brief Parser (syntactic analysis).
 *
 * Implemented with recursive descent.
 */
class Parser {
 public:
  explicit Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {}

  nlohmann::json program() const { return numeric_literal(); }

  nlohmann::json numeric_literal() const {
    return {
        {"type", "numeric_literal"},
        {"value", std::get<float>(tokens.front().literal.value())},
    };
  }

 private:
  std::vector<Token> tokens;
};

}  // namespace Krokodil
