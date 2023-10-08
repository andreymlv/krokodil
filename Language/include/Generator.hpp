#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

namespace Krokodil {

class Generator {
 public:
  explicit Generator(nlohmann::json ast) : ast(std::move(ast)) {}

  void generate(const std::string& path) {
    std::ofstream file(path);
    file << ".global main" << std::endl;
    file << ".text" << std::endl;
    file << "main:" << std::endl;
    file << "mov $message, %rdi" << std::endl;
    file << "call puts" << std::endl;
    file << "ret" << std::endl;
    file << "message:" << std::endl;
    file << ".asciz \"Hello, World!\"" << std::endl;
  }

 private:
  nlohmann::json ast;
};

}  // namespace Krokodil
