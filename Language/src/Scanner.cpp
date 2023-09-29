#include "Scanner.hpp"

#include <charconv>
#include <cstring>
#include <optional>

#include "Utils.hpp"

namespace Krokodil {

Scanner::Scanner(std::string source) : source(std::move(source)) {}

auto Scanner::scan_tokens() -> std::vector<Token> {
  while (!isAtEnd()) {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  tokens.emplace_back(TokenType::EndOfFile, "EOF", std::nullopt, line);
  return tokens;
}

auto Scanner::isAtEnd() -> bool { return current >= source.length(); }

auto Scanner::advance() -> char { return source.at(current++); }

void Scanner::addToken(TokenType type, const Literal& literal) {
  auto text = source.substr(start, current - start);
  tokens.emplace_back(type, text, literal, line);
}

void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }

auto Scanner::match(char expected) -> bool {
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

auto Scanner::peek() -> char {
  if (isAtEnd()) return '\0';
  return source.at(current);
}

void Scanner::string() {
  auto start_line = line;
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (isAtEnd()) {
    status_log << "[line " << start_line << ":" << line << "] Error"
               << ": "
               << "Unterminated string." << std::endl;
    had_error = true;
    return;
  }

  advance();

  auto value = source.substr(start + 1, current - start - 2);
  addToken(TokenType::STRING, value);
}

auto Scanner::peekNext() -> char {
  if (current + 1 >= source.length()) return '\0';
  return source.at(current + 1);
}

void Scanner::number() {
  while (isdigit(peek()) != 0) advance();

  // Look for a fractional part.
  if (peek() == '.' && (isdigit(peekNext()) != 0)) {
    // Consume the "."
    advance();

    while (isdigit(peek()) != 0) advance();
  }
  auto str = source.substr(start, current - start);
  bool error = false;

  {
    auto result = to_int(str);
    if (!result.has_value()) {
      error = true;
    } else {
      addToken(TokenType::NUMBER, result);
      return;
    }
  }

  {
    auto result = to_float(str);
    if (!result.has_value() && error) {
      status_log << "[line " << line << "] Error"
                 << ": "
                 << "Unexpected number." << std::endl;
      had_error = true;
    } else {
      addToken(TokenType::NUMBER, result);
      return;
    }
  }
}

void Scanner::identifier() {
  while (isalnum(peek()) != 0) advance();

  std::string text = source.substr(start, current - start);

  TokenType type;
  try {
    type = keywords.at(text);
  } catch (const std::out_of_range& e) {
    type = TokenType::IDENTIFIER;
  }
  addToken(type);
}

void Scanner::scanToken() {
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
      if (match('=')) {
        addToken(TokenType::EQUAL_EQUAL);
      } else {
        status_log << "[line " << line << "] Error"
                   << ": "
                   << "Unexpected character." << std::endl;
        had_error = true;
      }
      break;
    case '&':
      addToken(match('&') ? TokenType::AND : TokenType::AMPERSAND);
      break;
    case '|':
      addToken(match('|') ? TokenType::OR : TokenType::VERTICAL_BAR);
      break;
    case ':':
      if (match('=')) {
        addToken(TokenType::EQUAL);
      } else {
        status_log << "[line " << line << "] Error"
                   << ": "
                   << "Unexpected character." << std::endl;
        had_error = true;
      }
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
      if (isdigit(c) != 0) {
        number();
      } else if (isalpha(c) != 0) {
        identifier();
      } else {
        status_log << "[line " << line << "] Error"
                   << ": "
                   << "Unexpected character." << std::endl;
        had_error = true;
      }
      break;
  }
}
}  // namespace Krokodil
