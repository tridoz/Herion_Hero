#pragma once

#include <cstddef>
#include <cstdint>
#include <string>

enum class TokenType : std::uint8_t {
    Identifier,

    String,
    Number,

    Component,
    Param,

    OpenParenthesis,  // (
    CloseParenthesis, // )

    OpenBrace,  // {
    CloseBrace, // }

    Semicolon, // ;
    Comma,     // ,

    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;

    std::size_t line;
    std::size_t column;
};