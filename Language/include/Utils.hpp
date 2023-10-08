#pragma once

#include <charconv>
#include <cstring>
#include <fstream>
#include <utility>

#include "Generator.hpp"
#include "Parser.hpp"
#include "Scanner.hpp"

#ifndef WIN32
#include <cstdlib>
#else
#endif  // !WIN32

namespace Krokodil {

inline auto read_all(const std::string &path) -> std::string {
  std::ifstream stream(path);
  std::string line;
  std::stringstream lines;
  while (std::getline(stream, line)) {
    lines << line << std::endl;
  }
  return lines.str();
}

inline auto compile(std::string lines) -> std::string {
  Scanner scanner(std::move(lines));
  auto tokens = scanner.scan_tokens();
  std::stringstream stream;
  stream << scanner.status_log.str();
  for (const auto &token : tokens) {
    stream << token << std::endl;
  }
  Parser parser(std::move(tokens));
  auto ast = parser.program();
  stream << std::setw(2) << ast << std::endl;
  Generator generator(std::move(ast));
  generator.generate("out.s");

#ifndef WIN32
  if (system("gcc -no-pie out.s") != 0) {
    std::cerr << strerror(errno) << std::endl;
  }
  if (system("./a.out") != 0) {
    std::cerr << strerror(errno) << std::endl;
  }
#else
  // Call mingw gcc in windows
#endif  // !WIN32

  return stream.str();
}

inline auto to_int(std::string s) -> std::optional<int> {
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

inline auto to_float(std::string s) -> std::optional<float> {
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
