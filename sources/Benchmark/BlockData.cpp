#include "../../include/Benchmark/BlockData.hpp"

namespace bmk {

BlockData::BlockData(std::string name, std::string file, int line) {
    m_name = name;
    m_file = file;
    m_line = line;
}

BlockData ::~BlockData() { }
std::string BlockData::get_name() {
    return m_name;
}
std::string BlockData::get_file() {
    return m_file;
}
int BlockData::get_line() {
    return m_line;
}

}  // namespace bmk