//
// Created by adrianczubaty on 09.10.23.
//

#ifndef LIST_1_NTHBASENUMBER_H
#define LIST_1_NTHBASENUMBER_H

#include "../Interfaces/NumberCoder.h"
#include "DecimalCoder.h"
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <numeric>

class NthBaseNumber {
public:
    explicit NthBaseNumber(uint64_t init = 0, const std::shared_ptr<NumberCoder> &nc = nullptr);
    explicit NthBaseNumber(CodedNumber &init, const std::shared_ptr<NumberCoder> &nc = nullptr);
    NthBaseNumber(const NthBaseNumber &other);

    [[maybe_unused]] void ChangeBase(const std::shared_ptr<NumberCoder> &newNc);
    inline int getBase() noexcept {
        return this->_spNumberCoder->getBase();
    }

    NthBaseNumber& operator =(const NthBaseNumber &other);
    NthBaseNumber operator +(NthBaseNumber &other);
    NthBaseNumber operator -(NthBaseNumber &other);
    NthBaseNumber operator *(NthBaseNumber &other);
    NthBaseNumber operator /(NthBaseNumber &other);
    NthBaseNumber& operator ++();
    NthBaseNumber operator ++(int);

    bool operator ==(const NthBaseNumber &other) const;
    bool operator !=(const NthBaseNumber &other) const;
    bool operator <(NthBaseNumber &other);
    bool operator >(NthBaseNumber &other);
    bool operator <=(NthBaseNumber &other);
    bool operator >=(NthBaseNumber &other);

    friend std::ostream& operator <<(std::ostream &os, NthBaseNumber& number);
private:
    std::shared_ptr<NumberCoder> _spNumberCoder;
    CodedNumber number;

    static void EqualizeLength(CodedNumber &lhs, CodedNumber &rhs);
    static void ShrinkLength(CodedNumber &lhs, CodedNumber &rhs);
    static void PushCarryOver(NthBaseNumber &where, int carry = 0);
};

#endif //LIST_1_NTHBASENUMBER_H
