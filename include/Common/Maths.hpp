#ifndef Maths_HPP
#define Maths_HPP

#define PI 3.141592653589793  /* Archimede Constant */
#define EU 2.718281828459045  /* Euler Number */
#define TAU 6.283185307179586 /* Tau as 2PI */
#define GR 1.618033988749894  /* Golder Ratio */
#define PC 1.414213562373095  /* Pythagoras Constant */

#define RO 360 /* Complete rotation */

#include <array>
#include <chrono>
#include <cmath>
#include <deque>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <sstream>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace phy {

class Shape;
class Circle;
class Polygon;
class Edge;
class Corpse;

}  // namespace phy

namespace gmt {

template <typename T>
class Vector2;

template <typename T>
class Matrix2;

template <typename T>
class Vertices2;

template <typename T>
class Bounds;

}  // namespace gmt

namespace com {

template <typename T>
using sptr = std::shared_ptr<T>;

template <typename T>
using uptr = std::unique_ptr<T>;

template <typename T>
using vec = std::vector<T>;

template <typename T, int S>
using arr = std::array<T, S>;

template <typename I, typename T>
using map = std::unordered_map<I, T>;

template <typename T>
using spair = std::pair<T, T>;

template <typename A, typename B>
using pair = std::pair<A, B>;

template <typename P, typename T>
sptr<T> make_sptr(T o) {
    return std::make_shared<P>(o);
}

bool float_equals(float a, float b, float sigma = 0.1f);

float degree_to_radian(float degree);

float radian_to_degree(float radian);

float digits_comma(float number, int digits);

vec<int> cyclic_indexes(int min, int max, int size);

unsigned modulo(int value, unsigned m);

int rand_interval(int value);

int rand_interval_centered(int value);

vec<int> interpolate_array(const vec<int> &array_a, const vec<int> &array_b, const float &rate);

template <class C>
void remove(int i, vec<C> &vect) {
    vect.erase(vect.begin() + i);
}

template <class C>
C remove_return(int i, vec<C> &vect) {
    C ptr = vect.at(i);
    remove(i, vect);
    return ptr;
}

template <class C>
void remove_unordered(int i, vec<C> &vect) {
    if (i != vect.size() - 1) { vect.at(i) = std::move(vect.back()); }
    vect.pop_back();
}

template <class C>
C remove_unordered_return(int i, vec<C> &vect) {
    C ptr = vect.at(i);
    remove_unordered(i, vect);
    return ptr;
}

template <class C>
void remove_pairs(int i, vec<pair<C, C>> &pairs) {
    int first_pair = ((i - 1) * i) / 2;
    pairs.erase(pairs.begin() + first_pair, pairs.begin() + first_pair + i);  // Remove the first interval from pairs

    int next_pair = first_pair + i;
    int step      = i;
    while (next_pair < pairs.size()) {
        pairs.erase(pairs.begin() + next_pair);  // Remove the rest from pairs
        next_pair = next_pair + step;
        step++;
    }
}

/* Avoid linear complexity of the erase but do not keep the order */
template <class C>
void remove_pairs_unordered(const C &ptr, vec<pair<C, C>> &pairs) {
    int j    = 0;
    int size = pairs.size();
    while (j < size) {
        if (pairs.at(j).first == ptr || pairs.at(j).second == ptr) {
            if (j != pairs.size() - 1) { pairs.at(j) = std::move(pairs.back()); }
            pairs.pop_back();
            size = pairs.size();
        } else {
            j++;
        }
    }
}

template <class C, typename Func>
void remove_lambda(vec<C> &vect, Func lambda) {
    int i    = 0;
    int size = vect.size();
    while (i < size) {
        if (lambda(vect.at(i))) {
            if (i != vect.size() - 1) { vect.at(i) = std::move(vect.back()); }
            vect.pop_back();
            size = vect.size();
        } else {
            i++;
        }
    }
}

template <typename T>
bool decimal_equals(const T &a, const T &b, T epsilon = std::numeric_limits<T>::epsilon()) {
    return fabs(a - b) < epsilon;
}

template <typename T>
T minmax_filter(const T &value, const T &min, const T &max) {
    return std::max(std::min(value, max), min);
}

template <typename T>
vec<T> concatenate(vec<T> vect_a, vec<T> vect_b) {
    vec<T> vect_ab;
    vect_ab.reserve(vect_a.size() + vect_b.size());  // preallocate memory
    vect_ab.insert(vect_ab.end(), vect_a.begin(), vect_a.end());
    vect_ab.insert(vect_ab.end(), vect_b.begin(), vect_b.end());
    return vect_ab;
}

template <class C>
vec<pair<C, C>> non_touching_pairs(vec<C> vector) {
    vec<pair<C, C>> pairs = {};
    int n                 = vector.size();
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 2; j < n - (i == 0); j++) { pairs.push_back({i, j}); }
    }
    return pairs;
}

template <class C, typename Func>
vec<C> create_vector(C init, int number, Func next) {
    vec<C> vector = {};
    C pred        = init;
    for (int i = 0; i < number; i++) {
        vector.push_back(pred);
        pred = next(pred);
    }
    return vector;
}

template <typename T>
void obj_swap(T &a, T &b) {
    T temp = a;
    a      = b;
    b      = temp;
}

}  // namespace com
#endif
