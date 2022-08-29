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
struct string<com::pair<A, B>> {
    static std::string str(com::pair<A, B> param) {
        std::ostringstream oss;
        oss << "{ " << com::to_string<A>(param.first) << ", " << com::to_string<B>(param.second) << " }";
        return oss.str();
    }
};

/* Partially specialized template for Vectors */
template <typename T>
struct string<com::vec<T>> {
    static std::string str(com::vec<T> param) {
        std::ostringstream oss;
        oss << "com::vec { ";
        if (!param.empty()) {
            std::transform(param.begin(), param.end() - 1, std::ostream_iterator<std::string>(oss, ", "), com::to_string<T>);
            oss << com::to_string<T>(param.back());
        }
        oss << " }";
        return oss.str();
    }
};

/* Partially specialized template for Vector2 of Pairs */
template <typename A, typename B>
struct string<com::vec<com::pair<A, B>>> {
    static std::string str(com::vec<com::pair<A, B>> param) {
        std::ostringstream oss;
        oss << "com::vec { ";
        if (!param.empty()) {
            std::transform(param.begin(), param.end() - 1, std::ostream_iterator<std::string>(oss, ", "), com::to_string<com::pair<A, B>>);
            oss << com::to_string<com::pair<A, B>>(param.back());
        }
        oss << " }";
        return oss.str();
    }
};

/* Partially specialized template for gmt::Vector2 */
template <typename T>
struct string<gmt::Vector2<T>> {
    static std::string str(gmt::Vector2<T> param) {
        std::ostringstream oss;
        oss << "gmt::Vector2 { " << param.x << " ; " << param.y << " }";
        return oss.str();
    }
};

/* Partially specialized template for com::sptr of gmt::Vector2 */
template <typename T>
struct string<com::sptr<gmt::Vector2<T>>> {
    static std::string str(com::sptr<gmt::Vector2<T>> param) {
        std::ostringstream oss;
        oss << "com::sptr ( " << com::to_string(*param) << " )";
        return oss.str();
    }
};

/* Partially specialized template for gmt::Matrix2 */
template <typename T>
struct string<gmt::Matrix2<T>> {
    static std::string str(gmt::Matrix2<T> param) {
        std::ostringstream oss;
        oss << "gmt::Matrix2 { " << param[0] << " ; " << param[1] << " ; " << param[2] << " ; " << param[3] << " }";
        return oss.str();
    }
};

/* Partially specialized template for gmt::Vertices2 */
template <typename T>
struct string<gmt::Vertices2<T>> {
    static std::string str(gmt::Vertices2<T> param) {
        std::ostringstream oss;
        oss << "gmt::Vertices2 { ";
        if (!param.vertices.empty()) {
            std::transform(param.vertices.begin(), param.vertices.end() - 1, std::ostream_iterator<std::string>(oss, ", "), com::to_string<gmt::Vector2<T>>);
            oss << com::to_string<gmt::Vector2<T>>(param.vertices.back());
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
        oss << "gmt::Bounds { " << com::to_string<gmt::Vector2<T>>(param.p1) << ", " << com::to_string<gmt::Vector2<T>>(param.p2) << " }";
        return oss.str();
    }
};

/* Usage example: com::to_string(com::type_name<QUALEUS_PRECISION>())*/
template <typename T>
constexpr auto type_name() noexcept {
    std::string_view name = "Error: unsupported compiler", prefix, suffix;
#ifdef __clang__
    name   = __PRETTY_FUNCTION__;
    prefix = "auto type_name() [T = ";
    suffix = "]";
#elif defined(__GNUC__)
    name   = __PRETTY_FUNCTION__;
    prefix = "constexpr auto type_name() [with T = ";
    suffix = "]";
#elif defined(_MSC_VER)
    name   = __FUNCSIG__;
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