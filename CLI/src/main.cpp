#include <Utils.hpp>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  if (argc == 1) {
    std::cerr << "Usage: " << argv[0] << " <scripts>";
    return 1;
  }
  std::vector<std::string> paths(argv + 1, argv + argc);
  for (const auto& path : paths) {
    auto lines = Krokodil::read_all(path);
    std::cout << Krokodil::compile(std::move(lines));
  }
  return 0;
}
