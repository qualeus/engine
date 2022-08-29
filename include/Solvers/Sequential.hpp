#ifndef Sequential_HPP
#define Sequential_HPP

#include "Solver.hpp"

namespace gmt {

class Sequential : public Solver {
   public:
    Sequential();
    void solve();
};

}  // namespace gmt

#endif