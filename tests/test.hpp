// clang-format off
#include <stdexcept>
#include <string>
#include "../include/Common/Maths.hpp"
#include "../include/Common/String.hpp"
#include "../include/Geometry/Vector.hpp"
#include "../include/Geometry/Vertices.hpp"
#include "../include/Geometry/Bounds.hpp"


template <class T>
using Unit = T;

template <class T>
using Vect = std::vector<T>;

template <class T>
using Pair = std::vector<std::pair<T, T>>;

template <class T>
using SVect = std::vector<std::shared_ptr<T>>;

template <class T>
using SPair = std::vector<std::pair<std::shared_ptr<T>, std::shared_ptr<T>>>;

#define ASSERT_THROW(condition) { if (!(condition)) { throw std::runtime_error(std::string("\n") + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__) + std::string(" in ") + std::string(__PRETTY_FUNCTION__)); } }

#define ASSERT_EQUAL(x, y) { if ((com::to_string(x)) != (com::to_string(y))) { throw std::runtime_error(std::string("\n\n__________________________ /!\\ ENGINE TEST FAILED /!\\ __________________________\n") + std::string("\n[Assertion Failed]\nExpected ") + com::to_string(x) + std::string("\nResult ") + com::to_string(y) + "\nin " + std::string(__PRETTY_FUNCTION__) + "\nat " + std::string(__FILE__) + std::string(":") + std::to_string(__LINE__)); } }
// clang-format on