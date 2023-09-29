#pragma once

#include <iostream>
#include <optional>
#include <string>
#include <variant>

#include "TokenType.hpp"

namespace Krokodil {

using Literal = std::optional<std::variant<float, int, std::string>>;

auto compare(const Literal& lhs, const Literal& rhs) -> bool;

struct Token {
  Token(TokenType type, std::string lexeme, Literal literal, int line);

  auto operator==(const Token& rhs) const -> bool;

  auto operator!=(const Token& rhs) const -> bool;

  friend auto operator<<(std::ostream& os, const Token& token) -> std::ostream&;

  Literal literal;
  TokenType type;
  int line;
  std::string lexeme;
};

auto operator<<(std::ostream& os, const Token& t) -> std::ostream&;

}  // namespace Krokodil
