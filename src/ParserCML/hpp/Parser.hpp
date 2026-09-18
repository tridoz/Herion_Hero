#pragma once

#include "AST.hpp"
#include "Token.hpp"

#include <string>
#include <vector>

class Parser {
  public:
    explicit Parser(std::vector<Token> tokens);

    CMLDocument Parse();

  private:
    std::vector<Token> tokens;
    std::size_t current = 0;

  private:
    [[nodiscard]]
    auto Peek() const -> const Token&;

    [[nodiscard]]
    auto Previous() const -> const Token&;

    [[nodiscard]]
    auto IsAtEnd() const -> bool;

    auto Advance() -> const Token&;

    [[nodiscard]] auto Check(TokenType type) const -> bool;

    auto Match(TokenType type) -> bool;

    auto Consume(TokenType type, const std::string& message) -> const Token&;

    auto ParseComponent() -> CMLComponent;

    CMLParameter ParseParameter();

    CMLValue ParseValue();

    void ConsumeSeparator();

    [[noreturn]]
    void Error(const Token& token, const std::string& message) const;
};