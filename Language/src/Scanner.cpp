#include "Scanner.hpp"

#include <charconv>

namespace Krokodil {

Scanner::Scanner(std::string source) : source(std::move(source)) {}

std::vector<Token> Scanner::scan_tokens() {
  while (!isAtEnd()) {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  tokens.emplace_back(TokenType::EndOfFile, "EOF", std::nullopt, line);
  return tokens;
}

bool Scanner::isAtEnd() { return current >= source.length(); }

char Scanner::advance() { return source.at(current++); }

void Scanner::addToken(TokenType type, Literal literal) {
  auto text = source.substr(start, current - start);
  tokens.emplace_back(type, text, literal, line);
}

void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }

bool Scanner::match(char expected) {
  if (isAtEnd()) return false;
  if (source.at(current) != expected) return false;

  current++;
  return true;
}

char Scanner::peek() {
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

char Scanner::peekNext() {
  if (current + 1 >= source.length()) return '\0';
  return source.at(current + 1);
}

void Scanner::number() {
  while (isdigit(peek())) advance();

  // Look for a fractional part.
  if (peek() == '.' && isdigit(peekNext())) {
    // Consume the "."
    advance();

    while (isdigit(peek())) advance();
  }
  float result{};
  auto str = source.substr(start, current - start);
  auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);
  if (ec == std::errc::invalid_argument) {
    status_log << "[line " << line << "] Error"
               << ": "
                  "This is not a number."
               << std::endl;
    had_error = true;
  } else if (ec == std::errc::result_out_of_range) {
    status_log << "[line " << line << "] Error"
               << ": "
                  "This number is larger than an int."
               << std::endl;
    had_error = true;
  }
  addToken(TokenType::NUMBER, result);
}

void Scanner::identifier() {
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
      if (isdigit(c)) {
        number();
      } else if (isalpha(c)) {
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
