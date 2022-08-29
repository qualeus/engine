#ifndef Recorder_HPP
#define Recorder_HPP

#include "Performance.hpp"

namespace bmk {

class Recorder : public Performance {
   private:
    Recorder *m_parent;

   public:
    static Recorder root;
    static Recorder *last;
    Recorder(com::sptr<BlockData> bloc);
    ~Recorder();
    void reset();
};

static bool recording = false;
static BlockData perf = BlockData("Global Root", __FILE__, __LINE__);

}  // namespace bmk

// Tracking a single task
#define Record(name) Recorder __perf__{com::make_sptr<bmk::BlockData>(bmk::BlockData(name, __FILE__, __LINE__))};

// Track and group several micro tasks
// #define RecordCluster(name) Recorder __perf__{com::make_sptr<bmk::BlockData>(bmk::BlockData(name , __FILE__, __LINE__))};;

#endif
