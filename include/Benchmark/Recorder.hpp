#ifndef Recorder_HPP
#define Recorder_HPP

#include "Performance.hpp"

namespace bmk {

class Recorder : public Performance {
   private:
    Recorder *parent;

   public:
    static Recorder root;
    static Recorder *last;
    Recorder(std::shared_ptr<BlockData> bloc);
    ~Recorder();
    void Reset();
};

static bool recording = false;
static BlockData perf = BlockData("Global Root", __FILE__, __LINE__);

}  // namespace 

// Tracking a single task
#define Record(name) Recorder __perf__{std::make_shared<bmk::BlockData>(bmk::BlockData(name , __FILE__, __LINE__))};

// Track and group several micro tasks
// #define RecordCluster(name) Recorder __perf__{std::make_shared<bmk::BlockData>(bmk::BlockData(name , __FILE__, __LINE__))};;


#endif
