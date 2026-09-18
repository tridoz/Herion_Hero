#pragma once

#include "Token.hpp"

#include <string>
#include <vector>

class Lexer {
  public:
    explicit Lexer(std::string source);

    std::vector<Token> Tokenize();

  private:
    std::string source;

    std::size_t current = 0;
    std::size_t line = 1;
    std::size_t column = 1;

  private:
    [[nodiscard]] auto IsAtEnd() const -> bool;

    [[nodiscard]] auto Peek() const -> char;
    [[nodiscard]] auto PeekNext() const -> char;

    [[nodiscard]] auto Advance() -> char;

    auto SkipWhitespace() -> void;

    auto MakeToken(TokenType, const std::string&, std::size_t, std::size_t) -> Token;

    auto ReadIdentifier() -> Token;
    auto ReadNumber() -> Token;
    auto ReadString() -> Token;

    [[noreturn]] auto Error(const std::string&) const -> void;
};