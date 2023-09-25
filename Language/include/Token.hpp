#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include "TokenType.hpp"

namespace Krokodil {

using Literal = std::optional<std::variant<float, std::string>>;

bool compare(const Literal& lhs, const Literal& rhs);

struct Token {
  Token(TokenType type, std::string lexeme, Literal literal, int line);

  bool operator==(const Token& rhs) const;

  bool operator!=(const Token& rhs) const;

  friend std::ostream& operator<<(std::ostream& os, const Token& token);

  Literal literal;
  TokenType type;
  int line;
  std::string lexeme;
};

std::ostream& operator<<(std::ostream& os, const Token& t);

}  // namespace Krokodil
