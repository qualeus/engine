#include "../../include/Partitioners/BruteForce.hpp"

namespace gmt {

com::vec<com::spair<com::sptr<phy::Corpse>>> BruteForce::compute_pairs(com::vec<com::sptr<phy::Corpse>> corpses) {
    com::vec<com::spair<com::sptr<phy::Corpse>>> pairs = {};

    for (int i = 0; i < corpses.size(); i++) {
        for (int j = i + 1; j < corpses.size(); j++) { pairs.push_back({corpses[i], corpses[j]}); }
    }

    return pairs;
}

}  // namespace gmt