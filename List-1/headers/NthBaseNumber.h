//
// Created by adrianczubaty on 09.10.23.
//

#ifndef LIST_1_NTHBASENUMBER_H
#define LIST_1_NTHBASENUMBER_H

#include "../Interfaces/NumberCoder.h"
#include "UBaseCoder.h"
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <numeric>

/// Creates a number in given `u'x` base
class NthBaseNumber {
public:
    explicit NthBaseNumber(int64_t init = 0, const std::shared_ptr<NumberCoder> &nc = nullptr);
    explicit NthBaseNumber(CodedNumber &init, bool isReversed = false, const std::shared_ptr<NumberCoder> &nc = nullptr);
    NthBaseNumber(const NthBaseNumber &other);

    [[maybe_unused]]
    void ChangeBase(const std::shared_ptr<NumberCoder> &newNc);

    [[nodiscard]]
    inline int getBase() const noexcept {
        return this->_spNumberCoder->getBase();
    }

    [[maybe_unused]]
    [[nodiscard]]
    inline bool isNegative() const {
        return isNegative(*this);
    }

    [[maybe_unused]]
    static bool isNegative(const NthBaseNumber &what) noexcept;

    NthBaseNumber& operator =(const NthBaseNumber &other);
    NthBaseNumber operator +(NthBaseNumber &other);
    NthBaseNumber operator -(NthBaseNumber &other);
    NthBaseNumber operator *(NthBaseNumber &other);
    NthBaseNumber& operator ++();

    bool operator ==(const NthBaseNumber &other) const;
    bool operator !=(const NthBaseNumber &other) const;
    bool operator <(NthBaseNumber &other);
    bool operator >(NthBaseNumber &other);
    bool operator <=(NthBaseNumber &other);
    bool operator >=(NthBaseNumber &other);

    friend std::ostream& operator <<(std::ostream &os, NthBaseNumber& number);
private:
    std::shared_ptr<NumberCoder> _spNumberCoder;
    CodedNumber _number;

    static void EqualizeLength(CodedNumber &lhs, CodedNumber &rhs, int base);
    static void ShrinkLength(CodedNumber &lhs, CodedNumber &rhs);
    static void PushCarryOver(NthBaseNumber &where, int carry = 0);
    static uint8_t getSignBit(const uint8_t &sign, const int base);
};

#endif //LIST_1_NTHBASENUMBER_H
