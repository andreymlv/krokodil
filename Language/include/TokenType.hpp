#pragma once

namespace Krokodil {
enum class TokenType {
  // Single-character tokens.
  COMMA,
  LEFT_BRACE,
  LEFT_PAREN,
  MINUS,
  PLUS,
  RIGHT_BRACE,
  RIGHT_PAREN,
  SEMICOLON,
  SHIFT_LEFT,
  SHIFT_RIGHT,
  AMPERSAND,
  VERTICAL_BAR,
  SLASH,
  STAR,

  // One or two character tokens.
  AND,
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  OR,

  // Literals.
  IDENTIFIER,
  NUMBER,
  STRING,

  // Keywords.
  BEGIN,
  ELSE,
  END,
  FALSE,
  FOR,
  FUN,
  IF,
  PRINT,
  RETURN,
  TRUE,
  TYPE,
  WHILE,

  EndOfFile,
};

}
