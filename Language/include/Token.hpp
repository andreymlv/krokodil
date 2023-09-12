#pragma once

struct Token {
  Token(int line, int some) : line(line), some(some) {}
  int line;
  int some;

  int get_line() const;
};
