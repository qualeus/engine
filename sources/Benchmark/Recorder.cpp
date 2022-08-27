#include "../../include/Benchmark/Recorder.hpp"

namespace bmk {

Recorder *Recorder::last = &root;
Recorder Recorder::root = Recorder(std::make_shared<BlockData>(perf));

Recorder::Recorder(std::shared_ptr<BlockData> bloc) : Performance(bloc), m_parent(last) {
    last = this;
}

Recorder::~Recorder() {
    if (this == m_parent) { return; }
    last = m_parent;

    end();

    Performance *self = this;

    m_parent->childs.emplace_back(std::move(*self));
    if (m_parent->childs.size() > MAX_STORED_CHILDS) { m_parent->childs.pop_front(); }
}

void Recorder::reset() {
    for (int i = 0; i < m_parent->childs.size(); i++) { m_parent->childs[i].reset_childs(); }
    m_parent->reset_childs();
}

}  // namespace bmk