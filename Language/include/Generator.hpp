#pragma once

#include <nlohmann/json.hpp>

namespace Krokodil {

class Generator {
 public:
  explicit Generator(nlohmann::json ast) : ast(std::move(ast)) {}

  void generate(const std::string& path) {
  }

 private:
  nlohmann::json ast;
};

}  // namespace Krokodil
