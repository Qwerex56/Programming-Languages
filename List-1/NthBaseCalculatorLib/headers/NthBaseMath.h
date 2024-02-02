//
// Created by adrianczubaty on 08/12/23.
//

//#include "NthBaseNumber.h"

#ifndef LIST_1_NTHBASEMATH_H
#define LIST_1_NTHBASEMATH_H

#include <cstdint>

#include "./NthBaseNumber.h"

namespace nthBase::math {
    NthBaseNumber negative(const NthBaseNumber &number);

    [[maybe_unused]]
    NthBaseNumber abs(const NthBaseNumber &number) noexcept;

    [[maybe_unused]]
    bool isNegative(const NthBaseNumber &number) noexcept;

    [[maybe_unused]]
    bool isPositive(const NthBaseNumber &number) noexcept;

    [[maybe_unused]]
    uint8_t getSign(const NthBaseNumber &number) noexcept;

    // --- TODO: ----
    // Add implementation
    [[maybe_unused]] [[deprecated("Unimplemented")]]
    NthBaseNumber factorial(const NthBaseNumber& a) noexcept;

    [[maybe_unused]] [[deprecated("Unimplemented")]]
    NthBaseNumber pow(const NthBaseNumber& a, const NthBaseNumber& b) noexcept;
}

#endif //LIST_1_NTHBASEMATH_H
