//
// Created by adrianczubaty on 08/12/23.
//

#include "NthBaseNumber.h"

#ifndef LIST_1_NTHBASEMATH_H
#define LIST_1_NTHBASEMATH_H

namespace nthBase::math {
    NthBaseNumber negative(const NthBaseNumber &number);

    [[maybe_unused]]
    NthBaseNumber abs(const NthBaseNumber &number);

    bool isNegative(const NthBaseNumber &number);

    bool isPositive(const NthBaseNumber &number);

    uint8_t getSign(const NthBaseNumber &number);
}

#endif //LIST_1_NTHBASEMATH_H
