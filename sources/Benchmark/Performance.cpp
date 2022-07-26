#include "../../include/Benchmark/Performance.hpp"

namespace bmk {

Performance::Performance(std::shared_ptr<BlockData> data) : data(data) { beginning = std::chrono::high_resolution_clock::now(); }
Performance::Performance(Performance &&other) : data(other.data) {
    beginning = other.beginning;
    ending = other.ending;
    childs = std::move(other.childs);
}
Performance::~Performance() { this->End(); }

void Performance::End() { ending = std::chrono::high_resolution_clock::now(); }
void Performance::ResetChilds() { this->childs.clear(); }

double Performance::Time() {
    std::chrono::duration<double, std::milli> ms = ending - beginning;
    return ms.count();
}

double Performance::Beginning() {
    std::chrono::duration<double, std::milli> ms = beginning - start;
    return ms.count();
}

double Performance::Ending() {
    std::chrono::duration<double, std::milli> ms = ending - start;
    return ms.count();
}

}  // namespace bmk