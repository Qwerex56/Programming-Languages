//
// Created by adrianczubaty on 08/12/23.
//

#include "../headers/NthBaseMath.h"
#include "../headers/NthBaseNumber.h"

namespace math = nthBase::math;
using namespace nthBase;

NthBaseNumber math::negative(const NthBaseNumber &number) {
    auto coder = std::make_shared<UBaseCoder>(number.getBase());
    auto neg = NthBaseNumber(-1, coder) * number;

    return neg;
}

[[maybe_unused]]
NthBaseNumber math::abs(const NthBaseNumber &number) {
    return math::isPositive(number)?
        number :
        math::negative(number);
}

bool math::isNegative(const nthBase::NthBaseNumber &number) {
    using namespace math;

    auto halfBase = number.getBase() / 2;
    return getSign(number) >= halfBase;
}

bool math::isPositive(const nthBase::NthBaseNumber &number) {
    return !math::isNegative(number);
}

uint8_t math::getSign(const nthBase::NthBaseNumber &number) {
    return number.getNumberConst().back();
}