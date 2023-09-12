#include <Token.hpp>
#include <cstdio>

int main(int argc, char **argv) {
  printf("%d\n", Token(12, 32).get_line());
  return 0;
}
