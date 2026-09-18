#include "../hpp/CMLValue.hpp"

#include <format>

std::string CMLString::ToString() const {
    return '"' + value + '"';
}

std::string CMLIdentifier::ToString() const {
    return value;
}

std::string CMLNumber::ToString() const {
    return std::format("{}", value);
}

std::string CMLValueToString(const CMLValue& value) {
    return std::visit([](const auto& value) { return value.ToString(); }, value);
}