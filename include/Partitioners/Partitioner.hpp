#ifndef Partitioner_HPP
#define Partitioner_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "../Geometry/Geometry.hpp"

namespace gmt {

class Partitioner {
   public:
    virtual com::vec<com::spair<com::sptr<phy::Corpse>>> compute_pairs(com::vec<com::sptr<phy::Corpse>> corpses) = 0;
};

}  // namespace gmt

#endif