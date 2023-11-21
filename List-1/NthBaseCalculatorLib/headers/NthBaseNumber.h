//
// Created by adrianczubaty on 09.10.23.
//

#ifndef LIST_1_NTHBASENUMBER_H
#define LIST_1_NTHBASENUMBER_H

#define NATURAL_SYSTEM 10

#include "NumberCoder.h"
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

    [[maybe_unused]] explicit NthBaseNumber(CodedNumber &init, bool isReversed = false, const std::shared_ptr<NumberCoder> &nc = nullptr);
    explicit NthBaseNumber(CodedNumber &&init, bool isReversed = false, const std::shared_ptr<NumberCoder> &nc = nullptr);

    [[maybe_unused]] NthBaseNumber(const NthBaseNumber &other);

    [[maybe_unused]] NthBaseNumber(const NthBaseNumber &&other) noexcept;
    NthBaseNumber& operator =(const NthBaseNumber &other);

    [[maybe_unused]]
    void ChangeBase(const std::shared_ptr<NumberCoder> &newNc);

    [[nodiscard]]
    inline int getBase() const noexcept {
        return this->_numberCoder->getBase();
    }

    [[maybe_unused]]
    [[nodiscard]]
    inline bool isNegative() const {
        return isNegative(*this);
    }

    [[maybe_unused]]
    inline NthBaseNumber& negate() noexcept {
        this->_number = negate(this->_number, this->getBase());
        return *this;
    }

    [[maybe_unused]]
    [[nodiscard]]
    inline NthBaseNumber getNegate() const noexcept {
        auto negative = NthBaseNumber(negate(this->_number, this->getBase()), true, this->_numberCoder);
        return negative;
    }

    NthBaseNumber& operator +=(NthBaseNumber &other);
    NthBaseNumber& operator -=(NthBaseNumber &other);
    NthBaseNumber& operator *=(NthBaseNumber &other);

    NthBaseNumber& operator ++();
    const NthBaseNumber operator ++(int);

    bool operator ==(const NthBaseNumber &other) const;
    bool operator !=(const NthBaseNumber &other) const;
    bool operator <(const NthBaseNumber &other) const;
    bool operator >(const NthBaseNumber &other) const;
    bool operator <=(const NthBaseNumber &other) const;
    bool operator >=(const NthBaseNumber &other) const;

    friend std::ostream& operator <<(std::ostream &os, NthBaseNumber &number);
    friend NthBaseNumber operator +(NthBaseNumber lhs, NthBaseNumber &rhs);
    friend NthBaseNumber operator -(NthBaseNumber lhs, NthBaseNumber &rhs);
    friend NthBaseNumber operator *(NthBaseNumber lhs, NthBaseNumber &rhs);

    [[maybe_unused]]
    static inline CodedNumber getNegate(NthBaseNumber &what) {
        return negate(what._number, what.getBase());
    }

    [[maybe_unused]]
    static inline bool isNegative(const NthBaseNumber &what) noexcept;
private:
    std::shared_ptr<NumberCoder> _numberCoder;
    CodedNumber _number;

    static void EqualizeLength(CodedNumber &lhs, CodedNumber &rhs, int base);
    static void ShrinkLength(CodedNumber &toShrink, int base);
    static void PushCarryOver(NthBaseNumber &where, int carry = 0);
    static uint8_t getSignBit(const uint8_t &sign, int base);
    static CodedNumber negate(CodedNumber numToNegate, int base);
};

#endif //LIST_1_NTHBASENUMBER_H
