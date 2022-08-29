#ifndef Performance_HPP
#define Performance_HPP

#define MAX_STORED_CHILDS 500

#include "BlockData.hpp"

namespace bmk {

class Performance {
   private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_beginning;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_ending;
    com::sptr<BlockData> m_data;

   public:
    std::deque<Performance> childs;

    Performance(com::sptr<BlockData> data);
    ~Performance();

    void end();

    double time();
    double beginning();
    double ending();

    void reset_childs();
};

static std::chrono::time_point<std::chrono::high_resolution_clock> m_start = std::chrono::high_resolution_clock::now();

}  // namespace bmk

#endif