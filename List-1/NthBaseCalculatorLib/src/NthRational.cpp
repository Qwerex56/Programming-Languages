//
// Created by adrianczubaty on 19.12.23.
//

#include <memory>

#include "../headers/NthBaseNumber.h"
#include "../headers/NthRational.h"

using namespace nthBase::rational;

NthRational::NthRational() noexcept {
    auto coder = std::make_shared<UBaseCoder>(10);
    _numerator = NthBaseNumber(0, coder);
    _denumerator = NthBaseNumber(1, coder);
    _base = 10;
}

[[maybe_unused]]
NthRational::NthRational(const nthBase::NthBaseNumber &numerator, const nthBase::NthBaseNumber &denumerator) {
    if (numerator.getBase() != denumerator.getBase()) {
        throw exceptions::bad_base_error();
    }

    if (denumerator == NthBaseNumber(0, std::make_shared<UBaseCoder>(denumerator.getBase()))) {
        throw exceptions::divide_by_zero();
    }

    _numerator = numerator;
    _denumerator = denumerator;
    _base = numerator.getBase();
}

[[maybe_unused]]
NthRational::NthRational(const int64_t numerator, const int64_t denumerator, const uint8_t base) {
    if (denumerator == 0) {
        throw exceptions::divide_by_zero();
    }

    auto coder = std::make_shared<UBaseCoder>(base);

    _numerator = NthBaseNumber(numerator, coder);
    _denumerator = NthBaseNumber(denumerator, coder);
    _base = base;
}

[[maybe_unused]]
NthRational::NthRational(const NthRational &rhs) noexcept {
    if (this == &rhs) {
        return;
    }

    _numerator = rhs._numerator;
    _denumerator = rhs._denumerator;
    _base = rhs._base;
}

[[maybe_unused]]
NthRational::NthRational(const NthRational &&rhs) noexcept {
    if (this == &rhs) {
        return;
    }

    _numerator = rhs._numerator;
    _denumerator = rhs._denumerator;
    _base = rhs._base;
}

NthRational& NthRational::operator =(const NthRational &rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    _numerator = rhs._numerator;
    _denumerator = rhs._denumerator;
    _base = rhs._base;

    return *this;
}

NthRational& NthRational::operator =(NthRational &&rhs) noexcept {
    if (this == &rhs) {
        return *this;
    }

    _numerator = rhs._numerator;
    _denumerator = rhs._denumerator;
    _base = rhs._base;

    return *this;
}

NthRational &NthRational::operator +=(const NthRational &rhs) {
    if (_base != rhs._base) {
        throw exceptions::bad_base_error();
    }

    _numerator = (_numerator * rhs._denumerator) + (rhs._numerator * _denumerator);
    _denumerator *= rhs._denumerator;

    shortRational();

    return *this;
}

NthRational &NthRational::operator -=(const NthRational &rhs) {
    if (_base != rhs._base) {
        throw exceptions::bad_base_error();
    }

    _numerator = (_numerator * rhs._denumerator) - (rhs._denumerator * _denumerator);
    _denumerator *= rhs._denumerator;

    shortRational();

    return *this;
}

NthRational &NthRational::operator *=(const NthRational &rhs) {
    if (_base != rhs._base) {
        throw exceptions::bad_base_error();
    }

    _numerator *= rhs._numerator;
    _denumerator *= rhs._denumerator;

    shortRational();

    return *this;
}

NthRational &NthRational::operator /=(const NthRational &rhs) {
    if (_base != rhs._base) {
        throw exceptions::bad_base_error();
    }

    _numerator *= rhs._denumerator;
    _denumerator *= rhs._numerator;

    shortRational();

    return *this;
}

nthBase::NthBaseNumber NthRational::greatestCommonDivisor() noexcept {
    auto left = _numerator;
    auto right = _denumerator;

    while (right != NthBaseNumber(0, std::make_shared<UBaseCoder>(left.getBase()))) {
        auto division = NthBaseNumber::slowDivision(left, right);
        auto remainder = get<1>(division);

        left = right;
        right = remainder;
    }

    return left;
}

void NthRational::shortRational() noexcept {
    auto gcd = greatestCommonDivisor();
    while (gcd > NthBaseNumber(1, std::make_shared<UBaseCoder>(gcd.getBase()))) {
        _numerator = get<0>(nthBase::NthBaseNumber::slowDivision(_numerator, gcd));
        _denumerator = get<0>(nthBase::NthBaseNumber::slowDivision(_denumerator, gcd));
        gcd = greatestCommonDivisor();
    }
}
