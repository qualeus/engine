#ifndef Solver_HPP
#define Solver_HPP

namespace gmt {

class Solver {
   public:
    Solver();
    virtual void solve() = 0;
};

}  // namespace gmt

#endif