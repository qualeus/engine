#include "../../include/Benchmark/BlockData.hpp"

namespace bmk {

BlockData::BlockData(std::string name, std::string file, int line) {
    this->name = name;
    this->file = file;
    this->line = line;
}

BlockData ::~BlockData() {}
std::string BlockData::get_name() { return this->name; }
std::string BlockData::get_file() { return this->file; }
int BlockData::get_line() { return this->line; }

}  // namespace bmk