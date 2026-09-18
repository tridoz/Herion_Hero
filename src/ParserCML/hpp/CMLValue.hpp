#pragma once

#include <string>
#include <variant>

struct CMLString {
    std::string value;

    [[nodiscard]]
    std::string ToString() const;
};

struct CMLIdentifier {
    std::string value;

    [[nodiscard]]
    std::string ToString() const;
};

struct CMLNumber {
    double value;

    [[nodiscard]]
    std::string ToString() const;
};

using CMLValue = std::variant<CMLString, CMLIdentifier, CMLNumber>;

[[nodiscard]]
std::string CMLValueToString(const CMLValue& value);