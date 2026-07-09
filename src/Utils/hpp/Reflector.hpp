#pragma once

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <sstream>
#include <utility>

// ================= INDENT =================
inline std::string indent(int n) {
    return std::string(n * 2, ' ');
}

// ================= COLORS =================
inline std::string red(const std::string& s) {
    return "\033[31m" + s + "\033[0m";
}

inline std::string yellow(const std::string& s) {
    return "\033[33m" + s + "\033[0m";
}

inline std::string green(const std::string& s) {
    return "\033[32m" + s + "\033[0m";
}

inline std::string cyan(const std::string& s) {
    return "\033[36m" + s + "\033[0m";
}

inline std::string magenta(const std::string& s) {
    return "\033[35m" + s + "\033[0m";
}





// ================= FIELD =================
template<typename C, typename M>
struct Field {
    const char* name;
    M C::* ptr;
};

// ================= TYPE NAME =================
template<typename T>
std::string type_name() {
#if defined(__clang__) || defined(__GNUC__)
    std::string s = __PRETTY_FUNCTION__;
    auto start = s.find("T = ");
    if (start == std::string::npos) return "unknown";
    start += 4;
    // fine naturale del template info
    auto end = s.find(']', start);
    std::string type = s.substr(start, end - start);
    // 🔥 TAGLIO TUTTO DOPO ';'
    auto semi = type.find(';');
    if (semi != std::string::npos)
        type = type.substr(0, semi);

    return type;
#else
    return "unknown";
#endif
}

// ================= STL TRAITS =================
template<typename T> struct is_vector : std::false_type {};
template<typename T, typename A>
struct is_vector<std::vector<T, A>> : std::true_type {};

template<typename T> struct is_list : std::false_type {};
template<typename T, typename A>
struct is_list<std::list<T, A>> : std::true_type {};

template<typename T> struct is_map : std::false_type {};
template<typename K, typename V, typename... R>
struct is_map<std::map<K, V, R...>> : std::true_type {};
template<typename K, typename V, typename... R>
struct is_map<std::unordered_map<K, V, R...>> : std::true_type {};

// ================= REFLECTION CHECK =================
template<typename T, typename = void>
struct has_reflect_members : std::false_type {};

template<typename T>
struct has_reflect_members<T, std::void_t<decltype(T::reflect_members())>>
    : std::true_type {};

// ================= FORWARD DECL =================
template<typename T>
std::string value_to_string(const T& v, int indent_level);

template<typename T>
std::string struct_to_string(const T& obj, int indent_level);

// ================= VALUE TO STRING =================
template<typename T>
std::string value_to_string(const T& v, int indent_level) {

    // ---------- ARITHMETIC ----------
    if constexpr (std::is_arithmetic_v<T>) {
        return std::to_string(v);
    }

    // ---------- STRING ----------
    else if constexpr (std::is_same_v<T, std::string>) {
        return "\"" + v + "\"";
    }

    // ---------- POINTER ----------
    else if constexpr (std::is_pointer_v<T>) {

        if (!v)
            return red("nullptr");

        using P = std::remove_pointer_t<T>;

        if constexpr (has_reflect_members<P>::value) {
            return struct_to_string(*v, indent_level);
        } else {
            return std::string("[ptr ") + type_name<P>() + "]";
        }
    }

    // ---------- VECTOR ----------
    else if constexpr (is_vector<T>::value) {

        std::string out = "[\n";

        for (const auto& e : v) {
            out +=
                value_to_string(e, indent_level + 1)
                + "\n";
        }

        out += indent(indent_level - 1) + "]";
        return out;
    }

    // ---------- LIST ----------
    else if constexpr (is_list<T>::value) {

        std::string out = "[\n";


        for (const auto& e : v) {
            out +=
                value_to_string(e, indent_level + 1)
                + "\n";
        }

        out += indent(indent_level - 1) + "]";
        return out;
    }

    // ---------- MAP ----------
    else if constexpr (is_map<T>::value) {

        std::string out = "{\n";

        for (const auto& [k, val] : v) {
            auto value = value_to_string(val, indent_level);

            if (value.find('\n') != std::string::npos) {
                out += indent(indent_level)
                    + magenta(value_to_string(k, indent_level + 1))
                    + " : ";

                // rimuove l'indent iniziale della prima riga
                auto pos = value.find_first_not_of(' ');
                out += value.substr(pos);

                out += "\n";
            }
            else {
                out += indent(indent_level)
                    + magenta(value_to_string(k, indent_level + 1))
                    + " : "
                    + value
                    + "\n";
            }
        }

        out += indent(indent_level - 1) + "}";
        return out;
    }

    // ---------- ENUM ----------
    else if constexpr (std::is_enum_v<T>) {
        return std::to_string(static_cast<std::underlying_type_t<T>>(v));
    }

    // ---------- FALLBACK SAFE ----------
    else {
        if constexpr (has_reflect_members<T>::value) {
            return struct_to_string(v, indent_level  );
        } else {
            return std::string(indent(indent_level) + "[opaque type: ") + type_name<T>() + "]";
        }
    }
}

// ================= STRUCT TO STRING =================
template<typename T>
std::string struct_to_string(const T& obj, int indent_level) {

    using RawT = std::remove_cvref_t<T>;

    const RawT* ptr = nullptr;

    // ---------- POINTER HANDLING ----------
    if constexpr (std::is_pointer_v<RawT>) {

        if (!obj) {
            return indent(indent_level)
                + type_name<std::remove_pointer_t<RawT>>() + "* {\n"
                + indent(indent_level + 1)
                + red("nullptr")
                + "\n"
                + indent(indent_level)
                + "}";
        }

        ptr = obj;
    } else {
        ptr = &obj;
    }

    if (!ptr) {
        return red("INVALID POINTER");
    }

    using BaseT = std::remove_pointer_t<RawT>;

    std::string out;

    // 🔥 STRUCT HEADER (pulito, niente caos)
    int header_indent = std::max(0, indent_level - 1);

    out += indent(header_indent)
        + type_name<BaseT>()
        + (std::is_pointer_v<RawT> ? "*" : "")
        + " {\n";
    // ---------- SAFE REFLECTION ----------
    if constexpr (!has_reflect_members<BaseT>::value) {

        out += indent(indent_level + 1)
            + red("no reflection available")
            + "\n";

    } else {

        auto fields = BaseT::reflect_members();

        std::apply([&](auto const&... f) {

            ((out +=
                indent(indent_level + 1)

                // 🔥 ADDRESS DEL CAMPO
                + [&]() {
                    const void* addr = &(ptr->*(f.ptr));
                    std::ostringstream oss;
                    oss << addr;
                    return yellow(oss.str());
                }()

                + " -> "

                // FIELD NAME
                + cyan(std::string(f.name))

                + " -> "

                // FIELD TYPE
                + green(type_name<std::remove_cvref_t<
                    decltype(ptr->*(f.ptr))
                >>())

                + " = "

                // VALUE
                + value_to_string(ptr->*(f.ptr), indent_level + 2)

                + "\n"
            ), ...);

        }, fields);
    }

    out += indent(indent_level) + "}";
    return out;
}
// ================= UTILITY =================
template<typename... Ts>
auto concat_tuple(Ts&&... ts) {
    return std::tuple_cat(std::forward<Ts>(ts)...);
}
