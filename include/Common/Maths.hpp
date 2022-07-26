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
class Circle;
class Corpse;
class Polygon;
}  // namespace phy

namespace gmt {

template <typename T>
class Vector;

template <typename T>
class Vertices;

template <typename T>
class Bounds;

template <typename T>
class Collision;

template <typename T>
class Text;

class QuadTree;
class QuadNode;

}  // namespace gmt

namespace com {

bool float_equals(float a, float b, float sigma = 0.1f);
float degree_to_radian(float degree);
float radian_to_degree(float radian);
float digits_comma(float number, int digits);
std::vector<int> cyclic_indexes(int min, int max, int size);
unsigned modulo(int value, unsigned m);
int rand_interval(int value);
int rand_interval_centered(int value);

std::vector<int> interpolate_array(const std::vector<int> &array_a, const std::vector<int> &array_b, const float &rate);

template <class C>
void remove(int i, std::vector<C> &vect) {
    vect.erase(vect.begin() + i);
}

template <class C>
C remove_return(int i, std::vector<C> &vect) {
    C ptr = vect.at(i);
    com::remove(i, vect);
    return ptr;
}

template <class C>
void remove_unordered(int i, std::vector<C> &vect) {
    if (i != vect.size() - 1) { vect.at(i) = std::move(vect.back()); }
    vect.pop_back();
}

template <class C>
C remove_unordered_return(int i, std::vector<C> &vect) {
    C ptr = vect.at(i);
    com::remove_unordered(i, vect);
    return ptr;
}

template <class C>
void remove_pairs(int i, std::vector<std::pair<C, C>> &pairs) {
    int first_pair = ((i - 1) * i) / 2;
    pairs.erase(pairs.begin() + first_pair, pairs.begin() + first_pair + i);  // Remove the first interval from pairs

    int next_pair = first_pair + i;
    int step = i;
    while (next_pair < pairs.size()) {
        pairs.erase(pairs.begin() + next_pair);  // Remove the rest from pairs
        next_pair = next_pair + step;
        step++;
    }
}

/* Avoid linear complexity of the erase but do not keep the order */
template <class C>
void remove_pairs_unordered(const C &ptr, std::vector<std::pair<C, C>> &pairs) {
    int j = 0;
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
void remove_lambda(std::vector<C> &vect, Func lambda) {
    int i = 0;
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
std::vector<T> concatenate(std::vector<T> vect_a, std::vector<T> vect_b) {
    std::vector<T> vect_ab;
    vect_ab.reserve(vect_a.size() + vect_b.size());  // preallocate memory
    vect_ab.insert(vect_ab.end(), vect_a.begin(), vect_a.end());
    vect_ab.insert(vect_ab.end(), vect_b.begin(), vect_b.end());
    return vect_ab;
}

template <class C>
std::vector<std::pair<C, C>> non_touching_pairs(std::vector<C> vector) {
    std::vector<std::pair<C, C>> pairs = {};
    int n = vector.size();
    for (int i = 0; i < n - 2; i++) {
        for (int j = i + 2; j < n - (i == 0); j++) { pairs.push_back({i, j}); }
    }
    return pairs;
}

template <class C, typename Func>
std::vector<C> create_vector(C init, int number, Func next) {
    std::vector<C> vector = {};
    C pred = init;
    for (int i = 0; i < number; i++) {
        vector.push_back(pred);
        pred = next(pred);
    }
    return vector;
}

template <typename T>
void obj_swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

}  // namespace com
#endif
