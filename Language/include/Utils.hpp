#pragma once

#include <charconv>
#include <cstring>
#include <fstream>

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

inline std::optional<int> to_int(std::string s) {
  int value{};
  auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);

  if (strlen(ptr) != 0) {
    return std::nullopt;
  }

  if (ec == std::errc::invalid_argument) {
    return std::nullopt;
  } else if (ec == std::errc::result_out_of_range) {
    return std::nullopt;
  }

  return value;
}

inline std::optional<float> to_float(std::string s) {
  float value{};
  auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);

  if (ec == std::errc::invalid_argument) {
    return std::nullopt;
  } else if (ec == std::errc::result_out_of_range) {
    return std::nullopt;
  }

  return value;
}

}  // namespace Krokodil
