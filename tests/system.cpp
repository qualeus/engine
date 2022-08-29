#include "../include/System/System.hpp"

#include "test.hpp"

void test_corpses_accesses() {
    phy::System system = phy::System();

    for (int i = 0; i < 100000; i++) { system.add_corpse(phy::Corpse()); }

    for (int i = 0; i < 100000; i++) {
        auto direct_access  = system.get_corpse(i);
        auto hashmap_access = system.get_corpse_by_id(direct_access->get_id());

        ASSERT_EQUAL(direct_access->get_id(), hashmap_access->get_id())
    }
}

void test_basic_step() {
    phy::System system = phy::System();

    for (int i = 0; i < 2; i++) {
        auto corpse = phy::Corpse();
        corpse.add_shape(com::make_sptr<phy::Circle>(phy::Circle({0, 0}, 10 * (1 + i), 0, 1, 1)));
        system.add_corpse(corpse);
    }

    for (int i = 0; i < 100; i++) {
        system.step();

        std::cout << "\nstep " << com::to_string(i) << " (time: " << com::to_string(system.get_time()) << ")" << std::endl;

        for (int j = 0; j < system.get_corpses_size(); j++) {

            auto corpse   = system.get_corpse(j);
            auto position = corpse->get_pos();

            corpse->apply_force(gmt::VectorI(0.0f, -9.81f), position);  // Gravity

            std::cout << "corpse  [" << com::to_string(corpse->get_id()) << "] pos: " << com::to_string(position) << std::endl;
        }
    }

    // ASSERT_THROW(false)  // throw for log access
}

int main() {
    test_corpses_accesses();
    test_basic_step();
}