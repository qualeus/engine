#ifndef Brute_HPP
#define Brute_HPP

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "Partitioner.hpp"

namespace gmt {

class BruteForce : public Partitioner {
   public:
    com::vec<com::spair<com::sptr<phy::Corpse>>> compute_pairs(com::vec<com::sptr<phy::Corpse>> corpses);
};

}  // namespace gmt

#endif