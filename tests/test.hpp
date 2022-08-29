// clang-format off
#include <stdexcept>
#include <string>
#include "../include/Common/String.hpp"


template <class T>
using Unit = T;

template <class T>
using Vect = com::vec<T>;

template <class T>
using Pair = com::vec<com::pair<T, T>>;

template <class T>
using SVect = com::vec<com::sptr<T>>;

template <class T>
using SPair = com::vec<com::pair<com::sptr<T>, com::sptr<T>>>;

#define ASSERT_THROW(condition) { if (!(condition)) { throw std::runtime_error(std::string("\n") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string(" in ") + std::string(__PRETTY_FUNCTION__)); } }

#define ASSERT_EQUAL(x, y) { if ((com::to_string(x)) != (com::to_string(y))) { throw std::runtime_error(std::string("\n\n__________________________ /!\\ ENGINE TEST FAILED /!\\ __________________________\n") + std::string("\n[Assertion Failed]\nExpected ") + com::to_string(x) + std::string("\nResult ") + com::to_string(y) + "\nin " + std::string(__PRETTY_FUNCTION__) + "\nat " + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__)); } }
// clang-format on