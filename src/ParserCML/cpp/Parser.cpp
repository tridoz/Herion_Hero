#include "../hpp/Parser.hpp"

#include <stdexcept>

Parser::Parser(std::vector<Token> tokens) : tokens(std::move(tokens)) {
}

const Token& Parser::Peek() const {
    return tokens[current];
}

const Token& Parser::Previous() const {
    return tokens[current - 1];
}

bool Parser::IsAtEnd() const {
    return Peek().type == TokenType::EndOfFile;
}

const Token& Parser::Advance() {
    if (!IsAtEnd())
        ++current;

    return Previous();
}

bool Parser::Check(const TokenType type) const {
    if (IsAtEnd())
        return type == TokenType::EndOfFile;

    return Peek().type == type;
}

bool Parser::Match(const TokenType type) {
    if (!Check(type))
        return false;

    Advance();
    return true;
}

const Token& Parser::Consume(const TokenType type, const std::string& message) {
    if (Check(type))
        return Advance();

    Error(Peek(), message);
}

void Parser::ConsumeSeparator() {
    // Both are allowed:
    //
    // param x {10};
    //
    // param x {10},
    //
    // This makes the syntax a little more forgiving.

    if (Match(TokenType::Semicolon))
        return;

    if (Match(TokenType::Comma))
        return;

    // No separator is also useful before a closing parenthesis.
}

CMLDocument Parser::Parse() {
    CMLDocument document;

    while (!IsAtEnd()) {
        if (!Check(TokenType::Component)) {
            Error(Peek(), "Expected 'component'");
        }

        document.components.push_back(ParseComponent());

        // Optional ; after component
        Match(TokenType::Semicolon);
    }

    return document;
}

CMLComponent Parser::ParseComponent() {
    Consume(TokenType::Component, "Expected 'component'");

    const Token& name = Consume(TokenType::Identifier, "Expected component name");

    CMLComponent component;
    component.name = name.value;

    Consume(TokenType::OpenParenthesis, "Expected '(' after component name");

    while (!Check(TokenType::CloseParenthesis)) {
        if (IsAtEnd()) {
            Error(Peek(), "Expected ')' before end of file");
        }

        if (Check(TokenType::Param)) {
            component.parameters.push_back(ParseParameter());

            ConsumeSeparator();
            continue;
        }

        if (Check(TokenType::Component)) {
            component.children.push_back(ParseComponent());

            ConsumeSeparator();
            continue;
        }

        Error(Peek(), "Expected 'param' or 'component'");
    }

    Consume(TokenType::CloseParenthesis, "Expected ')' after component");

    return component;
}

CMLParameter Parser::ParseParameter() {
    Consume(TokenType::Param, "Expected 'param'");

    const Token& name = Consume(TokenType::Identifier, "Expected parameter name");

    Consume(TokenType::OpenBrace, "Expected '{' after parameter name");

    CMLValue value = ParseValue();

    Consume(TokenType::CloseBrace, "Expected '}' after parameter value");

    return CMLParameter{name.value, std::move(value)};
}

CMLValue Parser::ParseValue() {
    if (Check(TokenType::String)) {
        return CMLString{Advance().value};
    }

    if (Check(TokenType::Number)) {
        return CMLNumber{std::stod(Advance().value)};
    }

    if (Check(TokenType::Identifier)) {
        return CMLIdentifier{Advance().value};
    }

    Error(Peek(), "Expected value");
}

void Parser::Error(const Token& token, const std::string& message) const {
}