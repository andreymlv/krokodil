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

  std::string to_string() const {
    std::stringstream stream;
    stream << magic_enum::enum_name(type) << " " << lexeme << " ";
    std::visit([&stream](auto&& arg) { stream << arg; },
               literal.value_or("null"));
    return stream.str();
  }

 private:
  TokenType type;
  std::string lexeme;
  Literal literal;
  int line;
};
}  // namespace Krokodil
