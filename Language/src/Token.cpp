#include "Token.hpp"

#include <magic_enum.hpp>
#include <sstream>

namespace Krokodil {

Token::Token(TokenType type, std::string lexeme, Literal literal, int line)
    : type(type),
      lexeme(std::move(lexeme)),
      literal(std::move(literal)),
      line(line) {}

std::ostream& operator<<(std::ostream& os, const Token& t) {
  os << magic_enum::enum_name(t.type) << " " << t.lexeme << " ";
  std::visit([&os](auto&& arg) { os << arg; }, t.literal.value_or("null"));
  return os;
}

bool compare(const Literal& lhs, const Literal& rhs) {
  // Case 1: Neither has a value
  if (!lhs && !rhs) {
    return true;
  }

  // Case 2: Only one has a value
  if (!lhs || !rhs) {
    return false;
  }

  // Case 3: Both have a value
  return std::visit(
      [](auto&& arg1, auto&& arg2) {
        using T = std::decay_t<decltype(arg1)>;
        using G = std::decay_t<decltype(arg2)>;
        if constexpr (std::is_same_v<T, G>) {
          return arg1 == arg2;
        }
        return false;
      },
      *lhs, *rhs);
}

bool Token::operator!=(const Token& rhs) const { return !(*this == rhs); }

bool Token::operator==(const Token& rhs) const {
  return type == rhs.type && lexeme == rhs.lexeme &&
         compare(literal, rhs.literal) && line == rhs.line;
}
}  // namespace Krokodil
