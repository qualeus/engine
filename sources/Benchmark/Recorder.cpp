#include "../../include/Benchmark/Recorder.hpp"

namespace bmk {

Recorder *Recorder::last = &root;
Recorder Recorder::root = Recorder(std::make_shared<BlockData>(perf));

Recorder::Recorder(std::shared_ptr<BlockData> bloc) : Performance(bloc), parent(last) { last = this; }
Recorder::~Recorder() {
    if (this == parent) { return; }
    last = parent;

    this->End();

    Performance *self = this;

    parent->childs.emplace_back(std::move(*self));
    if (parent->childs.size() > MAX_STORED_CHILDS) { parent->childs.pop_front(); }
}

void Recorder::Reset() {
    for (int i = 0; i < parent->childs.size(); i++) { parent->childs[i].ResetChilds(); }
    parent->ResetChilds();
}

}  // namespace bmk