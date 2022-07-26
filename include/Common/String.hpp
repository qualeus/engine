#ifndef String_HPP
#define String_HPP

#include <stdexcept>
#include <string>

// clang-format off
#define LOG_ERROR(message) { \
    throw std::runtime_error(std::string("\n") + std::string(message) + std::string("\nat file:     ") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string("\nat function: ") + std::string(__PRETTY_FUNCTION__)); \
}
// clang-format on

#include "Maths.hpp"

namespace com {

/* Base structure definititon */
template <typename T>
struct string {
    static std::string str(T param) {
        std::ostringstream oss;
        oss << param;
        return oss.str();
    }
};

/* Structure call alias */
template <typename T>
std::string to_string(T param) {
    return com::string<T>::str(param);
}

/* Partially specialized template for Pairs */
template <typename A, typename B>
struct string<std::pair<A, B>> {
    static std::string str(std::pair<A, B> param) {
        std::ostringstream oss;
        oss << "{ " << com::to_string<A>(param.first) << ", " << com::to_string<B>(param.second) << " }";
        return oss.str();
    }
};

/* Partially specialized template for Vectors */
template <typename T>
struct string<std::vector<T>> {
    static std::string str(std::vector<T> param) {
        std::ostringstream oss;
        oss << "std::vector { ";
        if (!param.empty()) {
            std::transform(param.begin(), param.end() - 1, std::ostream_iterator<std::string>(oss, ", "), com::to_string<T>);
            oss << com::to_string<T>(param.back());
        }
        oss << " }";
        return oss.str();
    }
};

/* Partially specialized template for Vector of Pairs */
template <typename A, typename B>
struct string<std::vector<std::pair<A, B>>> {
    static std::string str(std::vector<std::pair<A, B>> param) {
        std::ostringstream oss;
        oss << "std::vector { ";
        if (!param.empty()) {
            std::transform(param.begin(), param.end() - 1, std::ostream_iterator<std::string>(oss, ", "), com::to_string<std::pair<A, B>>);
            oss << com::to_string<std::pair<A, B>>(param.back());
        }
        oss << " }";
        return oss.str();
    }
};

/* Partially specialized template for gmt::Vector */
template <typename T>
struct string<gmt::Vector<T>> {
    static std::string str(gmt::Vector<T> param) {
        std::ostringstream oss;
        oss << "gmt::Vector { " << param.x << " ; " << param.y << " }";
        return oss.str();
    }
};

/* Partially specialized template for shared_ptr of gmt::Vector */
template <typename T>
struct string<std::shared_ptr<gmt::Vector<T>>> {
    static std::string str(std::shared_ptr<gmt::Vector<T>> param) {
        std::ostringstream oss;
        oss << "std::shared_ptr ( " << com::to_string(*param) << " )";
        return oss.str();
    }
};

/* Partially specialized template for gmt::Vertices */
template <typename T>
struct string<gmt::Vertices<T>> {
    static std::string str(gmt::Vertices<T> param) {
        std::ostringstream oss;
        oss << "gmt::Vertices { ";
        if (!param.vertices.empty()) {
            std::transform(param.vertices.begin(), param.vertices.end() - 1, std::ostream_iterator<std::string>(oss, ", "), com::to_string<std::shared_ptr<gmt::Vector<T>>>);
            oss << com::to_string<std::shared_ptr<gmt::Vector<T>>>(param.vertices.back());
        }
        oss << " }";
        return oss.str();
    }
};

/* Partially specialized template for gmt::Bounds */
template <typename T>
struct string<gmt::Bounds<T>> {
    static std::string str(gmt::Bounds<T> param) {
        std::ostringstream oss;
        oss << "gmt::Bounds { " << param.x1 << ", " << param.y1 << " ; " << param.x2 << ", " << param.y2 << " }";
        return oss.str();
    }
};

/* Usage example: com::to_string(com::type_name<QUALEUS_PRECISION>())*/
template <typename T>
constexpr auto type_name() noexcept {
    std::string_view name = "Error: unsupported compiler", prefix, suffix;
#ifdef __clang__
    name = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name = __FUNCSIG__;
    prefix = "auto __cdecl type_name<";
    suffix = ">(void) noexcept";
#endif
    name.remove_prefix(prefix.size());
    name.remove_suffix(suffix.size());

    return name;
}

/*
template <typename T, typename std::enable_if_t<std::is_pointer<T>::value> * = 0>
std::string to_string(T value) {
    return to_string(*value);
}
*/

}  // namespace com

#endif