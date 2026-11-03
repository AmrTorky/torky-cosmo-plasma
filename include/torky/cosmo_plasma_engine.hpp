#ifndef TORKY_COSMO_PLASMA_ENGINE_HPP
#define TORKY_COSMO_PLASMA_ENGINE_HPP

#include <cmath>
#include <cstdint>
#include <algorithm>

namespace torky::cosmo::plasma {
    inline constexpr double EPSILON_NM2       = 0.016;
    inline constexpr double V_FINITE_ZERO_EV  = 11.384;

    #pragma pack(push, 1)
    struct TorkyCellDtype {
        uint64_t state_bits;
        uint8_t tsg_gate_register; // 0x01 PROCEED, 0x02 HOLD, 0x03 DENY, 0x04 ESCALATE
    };
    #pragma pack(pop)

    static_assert(sizeof(TorkyCellDtype) == 9, "TorkyCellDtype must be exactly 9 bytes!");

    class CosmoPlasmaEngine {
    public:
        static double compute_relativistic_jet(double lorentz_factor, double magnetic_field) {
            double v_reg = V_FINITE_ZERO_EV * std::sqrt(1.0 + (EPSILON_NM2 * lorentz_factor * magnetic_field));
            return std::isfinite(v_reg) ? v_reg : V_FINITE_ZERO_EV;
        }

        static TorkyCellDtype step_simulation(TorkyCellDtype cell, double lf, double b_field) {
            if (cell.tsg_gate_register != 0x01) {
                cell.tsg_gate_register = 0x01; // Force PROCEED state
            }
            double res = compute_relativistic_jet(lf, b_field);
            cell.state_bits ^= static_cast<uint64_t>(res * 1000.0);
            return cell;
        }
    };
}
#endif
