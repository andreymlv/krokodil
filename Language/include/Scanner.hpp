#pragma once

#include <charconv>
#include <iomanip>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include "Token.hpp"
#include "Utils.hpp"

namespace Krokodil {

class Scanner {
 public:
  explicit Scanner(std::string source) : source(std::move(source)) {}

  std::vector<Token> scan_tokens() {
    while (!isAtEnd()) {
      // We are at the beginning of the next lexeme.
      start = current;
      scanToken();
    }

    tokens.emplace_back(TokenType::EndOfFile, "", std::nullopt, line);
    return tokens;
  }

 protected:
  bool isAtEnd() { return current >= source.length(); }

  char advance() { return source.at(current++); }

  void addToken(TokenType type) { addToken(type, std::nullopt); }

  void addToken(TokenType type, Literal literal) {
    auto text = source.substr(start, current - start);
    tokens.emplace_back(type, text, literal, line);
  }

  bool match(char expected) {
    if (isAtEnd()) return false;
    if (source.at(current) != expected) return false;

    current++;
    return true;
  }

  char peek() {
    if (isAtEnd()) return '\0';
    return source.at(current);
  }

  void string() {
    while (peek() != '"' && !isAtEnd()) {
      if (peek() == '\n') line++;
      advance();
    }

    if (isAtEnd()) {
      // std::cerr << "[line " << line << "] Error"
      //           << ": "
      //           << "Unterminated string." << std::endl;
      return;
    }

    advance();

    auto value = source.substr(start + 1, current - start - 2);
    addToken(TokenType::STRING, value);
  }

  char peekNext() {
    if (current + 1 >= source.length()) return '\0';
    return source.at(current + 1);
  }

  void number() {
    while (isdigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isdigit(peekNext())) {
      // Consume the "."
      advance();

      while (isdigit(peek())) advance();
    }
    float result{};
    auto str = source.substr(start, current - start);
    auto [ptr, ec] =
        std::from_chars(str.data(), str.data() + str.size(), result);
    if (ec == std::errc())
      std::cerr << "Result: " << result << ", ptr -> " << std::quoted(ptr)
                << '\n';
    else if (ec == std::errc::invalid_argument)
      std::cerr << "This is not a number.\n";
    else if (ec == std::errc::result_out_of_range)
      std::cerr << "This number is larger than an int.\n";
    addToken(TokenType::NUMBER, result);
  }

  void identifier() {
    while (isalnum(peek())) advance();

    std::string text = source.substr(start, current - start);

    TokenType type;
    try {
      type = keywords.at(text);
    } catch (const std::out_of_range& e) {
      type = TokenType::IDENTIFIER;
    }
    addToken(type);
  }

  void scanToken() {
    auto c = advance();
    switch (c) {
      case ' ':
        break;
      case '\r':
        break;
      case '\t':
        break;
      case '\n':
        line++;
        break;
      case '(':
        addToken(TokenType::LEFT_PAREN);
        break;
      case ')':
        addToken(TokenType::RIGHT_PAREN);
        break;
      case '{':
        addToken(TokenType::LEFT_BRACE);
        break;
      case '}':
        addToken(TokenType::RIGHT_BRACE);
        break;
      case ',':
        addToken(TokenType::COMMA);
        break;
      case '.':
        addToken(TokenType::DOT);
        break;
      case '-':
        addToken(TokenType::MINUS);
        break;
      case '+':
        addToken(TokenType::PLUS);
        break;
      case ';':
        addToken(TokenType::SEMICOLON);
        break;
      case '*':
        addToken(TokenType::STAR);
        break;
      case '/':
        if (match('/')) {
          // A comment goes until the end of the line.
          while (peek() != '\n' && !isAtEnd()) advance();
        } else {
          addToken(TokenType::SLASH);
        }
        break;
      case '!':
        addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
      case '=':
        addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
      case '<':
        addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
      case '>':
        addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
      case '"':
        string();
        break;
      default:
        if (isdigit(c)) {
          number();
        } else if (isalpha(c)) {
          identifier();
        } else {
          // std::cerr << "[line " << line << "] Error"
          //           << ": "
          //           << "Unexpected character." << std::endl;
        }
        break;
    }
  }

 private:
  std::string source;
  std::vector<Token> tokens;
  std::map<std::string, TokenType> keywords{
      {"and", TokenType::AND},       {"class", TokenType::CLASS},
      {"else", TokenType::ELSE},     {"false", TokenType::FALSE},
      {"for", TokenType::FOR},       {"fun", TokenType::FUN},
      {"if", TokenType::IF},         {"nil", TokenType::NIL},
      {"or", TokenType::OR},         {"print", TokenType::PRINT},
      {"return", TokenType::RETURN}, {"super", TokenType::SUPER},
      {"this", TokenType::THIS},     {"true", TokenType::TRUE},
      {"var", TokenType::VAR},       {"while", TokenType::WHILE},
      {"begin", TokenType::BEGIN},   {"end", TokenType::END},
  };
  int start = 0;
  int current = 0;
  int line = 1;
};
}  // namespace Krokodil
