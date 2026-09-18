#pragma once

#include "CMLValue.hpp"

#include <string>
#include <vector>

struct CMLParameter {
    std::string name;
    CMLValue value;

    [[nodiscard]]
    std::string ToString(std::size_t indent = 0) const;
};

struct CMLComponent {
    std::string name;

    std::vector<CMLParameter> parameters;
    std::vector<CMLComponent> children;

    [[nodiscard]]
    std::string ToString(std::size_t indent = 0) const;
};

struct CMLDocument {
    std::vector<CMLComponent> components;

    [[nodiscard]]
    std::string ToString() const;
};