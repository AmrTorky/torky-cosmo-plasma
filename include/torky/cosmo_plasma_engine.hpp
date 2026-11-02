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
        uint8_t  gov_gate;     // TSG Gate Register (0x01 - 0x04)
        int16_t  phase_q16;    // Phase Q16 Fixed-Point
        int16_t  field_q16;    // Field Q16 Fixed-Point
        uint32_t syndrome_u32; // SHA-256 Merkle Syndrome
    };
    #pragma pack(pop)

    static_assert(sizeof(TorkyCellDtype) == 9, "CRITICAL: TorkyCellDtype must be precisely 9 bytes!");

    class CosmoPlasmaEngine {
    public:
        static inline double evaluate_relativistic_jet(double r_nm, double velocity_v) {
            double gamma = 1.0 / std::sqrt(1.0 - std::min(velocity_v * velocity_v, 0.9999));
            double potential = 1.0 / std::sqrt((r_nm * r_nm) + EPSILON_NM2);
            return gamma * potential;
        }
        static inline double evaluate_v_finite(double r_nm) {
            return 1.0 / std::sqrt((r_nm * r_nm) + EPSILON_NM2);
        }
    };
}
#endif
