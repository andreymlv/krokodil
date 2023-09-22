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

inline std::string compile(std::string lines) {
  Scanner scanner(lines);
  auto tokens = scanner.scan_tokens();
  std::stringstream stream;
  stream << scanner.status_log.str();
  for (const auto &token : tokens) {
    stream << token << std::endl;
  }
  return stream.str();
}

}  // namespace Krokodil
