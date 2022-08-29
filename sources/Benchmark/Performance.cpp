#include "../../include/Benchmark/Performance.hpp"

namespace bmk {

Performance::Performance(com::sptr<BlockData> data) : m_data(data) {
    m_beginning = std::chrono::high_resolution_clock::now();
}

Performance::~Performance() {
    end();
}

void Performance::end() {
    m_ending = std::chrono::high_resolution_clock::now();
}
void Performance::reset_childs() {
    childs.clear();
}

double Performance::time() {
    std::chrono::duration<double, std::milli> ms = m_ending - m_beginning;
    return ms.count();
}

double Performance::beginning() {
    std::chrono::duration<double, std::milli> ms = m_beginning - m_start;
    return ms.count();
}

double Performance::ending() {
    std::chrono::duration<double, std::milli> ms = m_ending - m_start;
    return ms.count();
}

}  // namespace bmk