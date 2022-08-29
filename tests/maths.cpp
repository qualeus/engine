#include "../include/Common/Maths.hpp"

#include "test.hpp"

template <class T>
com::pair<SVect<T>, SPair<T>> create_pairs(com::vec<T> values) {
    SVect<T> vect = SVect<T>();
    SPair<T> pair = SPair<T>();

    for (int i = 0; i < values.size(); i++) {
        vect.push_back(com::make_sptr<T>(values[i]));
        for (int j = 0; j < i; j++) { pair.push_back({com::make_sptr<T>(values[j]), com::make_sptr<T>(values[i])}); }
    }
    return com::pair<SVect<T>, SPair<T>>({vect, pair});
}

template <class T>
Pair<T> extract_pair(SPair<T> spair) {
    Pair<T> pair = Pair<T>();
    for (int i = 0; i < spair.size(); i++) { pair.push_back({*spair[i].first, *spair[i].second}); }
    return pair;
}

template <class T>
Vect<T> extract_vect(SVect<T> svect) {
    Vect<T> vect = Vect<T>();
    for (int i = 0; i < svect.size(); i++) { vect.push_back(*svect[i]); }
    return vect;
}

template <class T>
void remove_pairs(int index_delete, com::vec<T> values) {
    /*
    Ex: We remove the 3:

    Step0 [3]: {0,1},{0,2},{1,2},{0,3},{1,3},{2,3},{0,4},{1,4},{2,4},{3,4},{0,5},{1,5},{2,5},{3,5} ...
    Step1 (.): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{3,4},{0,5},{1,5},{2,5},{3,5},{4,5},{0,6},{1,6}  ...
    Step2 (6): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{0,5},{1,5},{2,5},{3,5},{4,5},{0,6},{1,6},{2,6}  ...
    Step3 (9): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{0,5},{1,5},{2,5},{4,5},{0,6},{1,6},{2,6},{3,6}  ...
    Step4 (13): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{0,5},{1,5},{2,5},{4,5},{0,6},{1,6},{2,6},{4,6}  ...
    Step5 (18):  [5] ... {0,5},{1,5},{2,5},{4,5},{0,6},{1,6},{2,6},{4,6},{5,6},{0,7},{1,7},{2,7}  ...
    Step6 (24):  [11] ... {2,6},{4,6},{5,6},{0,7},{1,7},{2,7},{4,7},{5,7},{6,7},{0,8},{1,8},{2,8}  ...
    */
    std::cout << "\nInput Vector2: " << com::to_string(values) << std::endl;

    com::pair<SVect<int>, SPair<int>> test_result = create_pairs(values);

    com::remove(index_delete, test_result.first);
    com::remove_pairs(index_delete, test_result.second);
    std::cout << "\nRemoving Pair [" << com::to_string(index_delete) << "]... => test_result" << std::endl;

    values.erase(values.begin() + index_delete);
    std::cout << "Manual Remove [" << com::to_string(index_delete) << "]... => true_result" << std::endl;

    Vect<int> test_result_vect = extract_vect(test_result.first);
    Pair<int> test_result_pair = extract_pair(test_result.second);

    std::cout << "\ntest_result_vect: " << com::to_string(test_result_vect) << std::endl;
    std::cout << "test_result_pair: " << com::to_string(test_result_pair) << std::endl;

    com::pair<SVect<int>, SPair<int>> true_result = create_pairs(values);

    Vect<int> true_result_vect = extract_vect(true_result.first);
    Pair<int> true_result_pair = extract_pair(true_result.second);

    std::cout << "\ntrue_result_vect: " << com::to_string(true_result_vect) << std::endl;
    std::cout << "true_result_pair: " << com::to_string(true_result_pair) << std::endl;

    ASSERT_EQUAL(true_result_vect.size(), test_result_vect.size());
    for (int i = 0; i < test_result_vect.size(); i++) { ASSERT_EQUAL(true_result_vect[i], test_result_vect[i]); }

    ASSERT_EQUAL(true_result_pair.size(), test_result_pair.size());
    for (int i = 0; i < test_result_pair.size(); i++) { ASSERT_EQUAL(true_result_pair[i], test_result_pair[i]); }
}

template <class T>
void remove_pairs_unordered(int index_delete, com::vec<T> values) {
    /*
    Ex: We remove the 3:

    Step0 [3]: {0,1},{0,2},{1,2},{0,3},{1,3},{2,3},{0,4},{1,4},{2,4},{3,4},{0,5},{1,5},{2,5},{3,5} ...
    Step1 (.): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{3,4},{0,5},{1,5},{2,5},{3,5},{4,5},{0,6},{1,6}  ...
    Step2 (6): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{0,5},{1,5},{2,5},{3,5},{4,5},{0,6},{1,6},{2,6}  ...
    Step3 (9): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{0,5},{1,5},{2,5},{4,5},{0,6},{1,6},{2,6},{3,6}  ...
    Step4 (13): {0,1},{0,2},{1,2},{0,4},{1,4},{2,4},{0,5},{1,5},{2,5},{4,5},{0,6},{1,6},{2,6},{4,6}  ...
    Step5 (18):  [5] ... {0,5},{1,5},{2,5},{4,5},{0,6},{1,6},{2,6},{4,6},{5,6},{0,7},{1,7},{2,7}  ...
    Step6 (24):  [11] ... {2,6},{4,6},{5,6},{0,7},{1,7},{2,7},{4,7},{5,7},{6,7},{0,8},{1,8},{2,8}  ...
    */
    std::cout << "\nInput Vector2: " << com::to_string(values) << std::endl;

    com::pair<SVect<int>, SPair<int>> test_result = create_pairs(values);

    auto ptr = com::remove_unordered_return(index_delete, test_result.first);
    com::remove_pairs_unordered(ptr, test_result.second);
    std::cout << "\nRemoving Pair [" << com::to_string(index_delete) << "]... => test_result" << std::endl;

    values.erase(values.begin() + index_delete);
    std::cout << "Manual Remove [" << com::to_string(index_delete) << "]... => true_result" << std::endl;

    Vect<int> test_result_vect = extract_vect(test_result.first);
    Pair<int> test_result_pair = extract_pair(test_result.second);

    std::cout << "\ntest_result_vect: " << com::to_string(test_result_vect) << std::endl;
    std::cout << "test_result_pair: " << com::to_string(test_result_pair) << std::endl;

    com::pair<SVect<int>, SPair<int>> true_result = create_pairs(values);

    Vect<int> true_result_vect = extract_vect(true_result.first);
    Pair<int> true_result_pair = extract_pair(true_result.second);

    std::cout << "\ntrue_result_vect: " << com::to_string(true_result_vect) << std::endl;
    std::cout << "true_result_pair: " << com::to_string(true_result_pair) << std::endl;

    ASSERT_EQUAL(true_result_vect.size(), test_result_vect.size());
    for (int i = 0; i < test_result_vect.size(); i++) { ASSERT_EQUAL(true_result_vect[i], test_result_vect[i]); }

    ASSERT_EQUAL(true_result_pair.size(), test_result_pair.size());
    for (int i = 0; i < test_result_pair.size(); i++) { ASSERT_EQUAL(true_result_pair[i], test_result_pair[i]); }
}

int main() {
    com::vec<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8};

    remove_pairs(0, values);
    remove_pairs(1, values);
    remove_pairs(2, values);
    remove_pairs(3, values);
    remove_pairs(5, values);
}