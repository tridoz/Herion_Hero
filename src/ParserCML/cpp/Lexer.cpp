#include "../hpp/Lexer.hpp"

#include <cctype>
#include <stdexcept>

Lexer::Lexer(std::string source) : source(std::move(source)) {
}

bool Lexer::IsAtEnd() const {
    return current >= source.size();
}

char Lexer::Peek() const {
    if (IsAtEnd())
        return '\0';

    return source[current];
}

char Lexer::PeekNext() const {
    if (current + 1 >= source.size())
        return '\0';

    return source[current + 1];
}

char Lexer::Advance() {
    if (IsAtEnd())
        return '\0';

    const char character = source[current++];

    if (character == '\n') {
        ++line;
        column = 1;
    } else {
        ++column;
    }

    return character;
}

void Lexer::SkipWhitespace() {
    while (!IsAtEnd()) {
        const char character = Peek();

        if (std::isspace(static_cast<unsigned char>(character))) {
            Advance();
            continue;
        }

        // Optional comments:
        // // this is a comment
        if (character == '/' && PeekNext() == '/') {
            while (!IsAtEnd() && Peek() != '\n')
                Advance();

            continue;
        }

        break;
    }
}

Token Lexer::MakeToken(
    TokenType type, const std::string& value, const std::size_t token_line, const std::size_t token_column
) {
    return Token{type, value, token_line, token_column};
}

Token Lexer::ReadIdentifier() {
    const std::size_t token_line = line;
    const std::size_t token_column = column;

    std::string value;

    while (!IsAtEnd()) {
        const char character = Peek();

        if (std::isalnum(static_cast<unsigned char>(character)) || character == '_' || character == ':') {
            value += Advance();
        } else {
            break;
        }
    }

    if (value == "component") {
        return MakeToken(TokenType::Component, value, token_line, token_column);
    }

    if (value == "param") {
        return MakeToken(TokenType::Param, value, token_line, token_column);
    }

    return MakeToken(TokenType::Identifier, value, token_line, token_column);
}

Token Lexer::ReadNumber() {
    const std::size_t token_line = line;
    const std::size_t token_column = column;

    std::string value;

    // Sign
    if (Peek() == '-' || Peek() == '+')
        value += Advance();

    bool decimal_point_found = false;

    while (!IsAtEnd()) {
        const char character = Peek();

        if (std::isdigit(static_cast<unsigned char>(character))) {
            value += Advance();
        } else if (character == '.' && !decimal_point_found) {
            decimal_point_found = true;
            value += Advance();
        } else {
            break;
        }
    }

    return MakeToken(TokenType::Number, value, token_line, token_column);
}

Token Lexer::ReadString() {
    const std::size_t token_line = line;
    const std::size_t token_column = column;

    // Skip opening "
    Advance();

    std::string value;

    while (!IsAtEnd() && Peek() != '"') {
        const char character = Advance();

        if (character == '\\') {
            if (IsAtEnd())
                break;

            const char escaped = Advance();

            switch (escaped) {
            case 'n':
                value += '\n';
                break;

            case 't':
                value += '\t';
                break;

            case '"':
                value += '"';
                break;

            case '\\':
                value += '\\';
                break;

            default:
                value += escaped;
                break;
            }
        } else {
            value += character;
        }
    }

    if (IsAtEnd()) {
        Error("Unterminated string");
    }

    // Skip closing "
    Advance();

    return MakeToken(TokenType::String, value, token_line, token_column);
}

std::vector<Token> Lexer::Tokenize() {
    std::vector<Token> tokens;

    while (!IsAtEnd()) {
        SkipWhitespace();

        if (IsAtEnd())
            break;

        const std::size_t token_line = line;
        const std::size_t token_column = column;

        const char character = Peek();

        // Identifier
        if (std::isalpha(static_cast<unsigned char>(character)) || character == '_') {
            tokens.push_back(ReadIdentifier());
            continue;
        }

        // Number
        if (std::isdigit(static_cast<unsigned char>(character)) ||
            ((character == '-' || character == '+') && std::isdigit(static_cast<unsigned char>(PeekNext())))) {
            tokens.push_back(ReadNumber());
            continue;
        }

        // String
        if (character == '"') {
            tokens.push_back(ReadString());
            continue;
        }

        Advance();

        switch (character) {
        case '(':
            tokens.push_back(MakeToken(TokenType::OpenParenthesis, "(", token_line, token_column));
            break;

        case ')':
            tokens.push_back(MakeToken(TokenType::CloseParenthesis, ")", token_line, token_column));
            break;

        case '{':
            tokens.push_back(MakeToken(TokenType::OpenBrace, "{", token_line, token_column));
            break;

        case '}':
            tokens.push_back(MakeToken(TokenType::CloseBrace, "}", token_line, token_column));
            break;

        case ';':
            tokens.push_back(MakeToken(TokenType::Semicolon, ";", token_line, token_column));
            break;

        case ',':
            tokens.push_back(MakeToken(TokenType::Comma, ",", token_line, token_column));
            break;

        default:
            Error("Unexpected character '" + std::string(1, character) + "'");
        }
    }

    tokens.push_back(MakeToken(TokenType::EndOfFile, "", line, column));

    return tokens;
}

[[noreturn]]
void Lexer::Error(const std::string& message) const {
    throw std::runtime_error(
        "CML Lexer Error at " + std::to_string(line) + ":" + std::to_string(column) + " - " + message
    );
}