#include "../hpp/AST.hpp"

#include <format>

namespace {

    std::string Indent(const std::size_t level) {
        return std::string(level * 4, ' ');
    }

} // namespace

std::string CMLParameter::ToString(const std::size_t indent) const {
    return std::format("{}param {} {{{}}};", Indent(indent), name, CMLValueToString(value));
}

std::string CMLComponent::ToString(const std::size_t indent) const {
    std::string result;

    result += std::format("{}component {}(\n", Indent(indent), name);

    for (const auto& parameter : parameters) {
        result += parameter.ToString(indent + 1);
        result += '\n';
    }

    for (const auto& child : children) {
        result += child.ToString(indent + 1);
        result += '\n';
    }

    result += std::format("{})", Indent(indent));

    return result;
}

std::string CMLDocument::ToString() const {
    std::string result;

    for (const auto& component : components) {
        result += component.ToString();
        result += ";\n";
    }

    return result;
}