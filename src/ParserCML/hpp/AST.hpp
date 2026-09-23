#pragma once

#include "CMLValue.hpp"

#include <stdexcept>
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

template <typename T> auto GetParameter(const std::string& name, const std::vector<CMLParameter>& params) -> T {
    for (const CMLParameter& par : params) {
        if (par.name == name)
            return std::get<T>(par.value);
    }

    throw std::runtime_error("CML parameter not found: " + name);
}