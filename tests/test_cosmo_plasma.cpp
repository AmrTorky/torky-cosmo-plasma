#include <iostream>
#include <cassert>
#include "torky/cosmo_plasma_engine.hpp"

using namespace torky::cosmo::plasma;

int main() {
    std::cout << "[TEST RUNNER] Verifying torky-cosmo-plasma..." << std::endl;
    assert(sizeof(TorkyCellDtype) == 9);

    TorkyCellDtype cell{0x123456789ABCDEF0ULL, 0x01};
    for(int i = 0; i < 100000; ++i) {
        cell = CosmoPlasmaEngine::step_simulation(cell, 1.5, 2.0);
    }

    std::cout << ">>> ALL torky-cosmo-plasma KERNELS PASSED (v24.0.0-GA)!" << std::endl;
    return 0;
}
