#include <iostream>
#include <cassert>
#include <cmath>
#include "torky/cosmo_plasma_engine.hpp"

using namespace torky::cosmo::plasma;

int main() {
    std::cout << "[TEST RUNNER] Verifying torky-cosmo-plasma..." << std::endl;
    assert(sizeof(TorkyCellDtype) == 9);
    double v0 = CosmoPlasmaEngine::evaluate_v_finite(0.0);
    assert(v0 > 0.0);
    double jet = CosmoPlasmaEngine::evaluate_relativistic_jet(0.5, 0.9);
    assert(!std::isnan(jet));
    std::cout << ">>> ALL torky-cosmo-plasma KERNELS PASSED (v24.0.0-GA)!" << std::endl;
    return 0;
}
