#pragma once

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <sstream>

// ================= COLORS =================
inline std::string red(const std::string& s) {
    return "\033[31m" + s + "\033[0m";
}

// ================= INDENT (tree style) =================
inline std::string indent(int n) {
    return std::string(n * 2, ' ');
}

inline std::string branch(bool last) {
    return last ? "└── " : "├── ";
}

// ================= FIELD =================
template<typename C, typename M>
struct Field {
    const char* name;
    M C::* ptr;
};

// ================= TYPE NAME (SAFE, NO typeid) =================
//
// IMPORTANT:
// avoids crashes with incomplete types (SDL_Renderer etc.)
//
template<typename T>
std::string type_name() {
#if defined(__clang__) || defined(__GNUC__)
    std::string s = __PRETTY_FUNCTION__;
    auto start = s.find("T = ");
    if (start == std::string::npos) return "unknown";
    start += 4;
    auto end = s.find(']', start);
    return s.substr(start, end - start);
#else
    return "unknown";
#endif
}

// ================= STL DETECTORS =================
template<typename T> struct is_vector : std::false_type {};
template<typename T, typename A>
struct is_vector<std::vector<T, A>> : std::true_type {};

template<typename T> struct is_list : std::false_type {};
template<typename T, typename A>
struct is_list<std::list<T, A>> : std::true_type {};

template<typename T> struct is_map : std::false_type {};

template<typename K, typename V, typename C, typename A>
struct is_map<std::map<K, V, C, A>> : std::true_type {};

template<typename K, typename V, typename H, typename E, typename A>
struct is_map<std::unordered_map<K, V, H, E, A>> : std::true_type {};

// ================= REFLECTION DETECTION =================
template<typename T, typename = void>
struct has_reflect_members : std::false_type {};

template<typename T>
struct has_reflect_members<T, std::void_t<decltype(T::reflect_members())>>
    : std::true_type {};

// ================= FORWARD DECL =================
template<typename T>
std::string struct_to_string(const T& obj, int indent_level);

template<typename T>
std::string value_to_string(const T& v, int indent_level);

// ================= VALUE TO STRING =================
template<typename T>
std::string value_to_string(const T& v, int indent_level) {

    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(v);
    }

    else if constexpr (std::is_same_v<T, std::string>) {
        return v;
    }

    else if constexpr (std::is_pointer_v<T>) {
        if (!v) return "nullptr";
        return "&" + value_to_string(*v, indent_level);
    }

    else if constexpr (is_vector<T>::value || is_list<T>::value) {

        std::string out = "[\n";
        int i = 0;
        int n = (int)v.size();

        for (const auto& e : v) {
            bool last = (++i == n);

            out += indent(indent_level + 1)
                + branch(last)
                + value_to_string(e, indent_level + 1)
                + "\n";
        }

        out += indent(indent_level) + "]";
        return out;
    }

    else if constexpr (is_map<T>::value) {

        std::string out = "{\n";
        int i = 0;
        int n = (int)v.size();

        for (const auto& [k, val] : v) {
            bool last = (++i == n);

            out += indent(indent_level + 1)
                + branch(last)
                + value_to_string(k, indent_level + 1)
                + " : "
                + value_to_string(val, indent_level + 1)
                + "\n";
        }

        out += indent(indent_level) + "}";
        return out;
    }

    else {
        return struct_to_string(v, indent_level);
    }
}

// ================= STRUCT TO STRING =================
template<typename T>
std::string struct_to_string(const T& obj, int indent_level) {

    std::string out;

    out += indent(indent_level)
        + type_name<T>()
        + " {\n";

    if constexpr (has_reflect_members<T>::value) {

        auto fields = T::reflect_members();

        std::apply([&](auto... f) {

            size_t i = 0;
            constexpr size_t N = sizeof...(f);

            ((out += indent(indent_level + 1)
                   + branch(++i == N)
                   + std::string(f.name)
                   + " : "
                   + type_name<std::decay_t<decltype(obj.*f.ptr)>>()
                   + " = "
                   + value_to_string(obj.*f.ptr, indent_level + 2)
                   + "\n"), ...);

        }, fields);

    } else {
        out += indent(indent_level + 1)
            + red("reflect_members_not_implemented!!!\n");
    }

    out += indent(indent_level) + "}";
    return out;
}
