#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Scanner.hpp"

namespace Krokodil {

inline std::string read_all(const std::string &path) {
  std::ifstream stream(path);
  std::string line;
  std::stringstream lines;
  while (std::getline(stream, line)) {
    lines << line << std::endl;
  }
  return lines.str();
}

inline void compile(std::string lines) {
  Scanner scanner(lines);
  auto tokens = scanner.scan_tokens();
  for (const auto &token : tokens) {
    std::cout << token.to_string() << std::endl;
  }
}

}  // namespace Krokodil
