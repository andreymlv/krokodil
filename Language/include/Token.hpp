#pragma once

#include <magic_enum.hpp>
#include <sstream>
#include <string>
#include <variant>

#include "TokenType.hpp"

namespace Krokodil {
using Literal = std::optional<std::variant<float, std::string>>;

class Token {
 public:
  Token(TokenType type, std::string lexeme, Literal literal, int line)
      : type(type),
        lexeme(std::move(lexeme)),
        literal(std::move(literal)),
        line(line) {}

  friend std::ostream& operator<<(std::ostream& os, const Token& token);

 private:
  TokenType type;
  std::string lexeme;
  Literal literal;
  int line;
};

std::ostream& operator<<(std::ostream& os, const Token& t) {
  os << magic_enum::enum_name(t.type) << " " << t.lexeme << " ";
  std::visit([&os](auto&& arg) { os << arg; }, t.literal.value_or("null"));
  return os;
}

}  // namespace Krokodil
