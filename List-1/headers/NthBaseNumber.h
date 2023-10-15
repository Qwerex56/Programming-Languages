//
// Created by adrianczubaty on 09.10.23.
//

#ifndef LIST_1_NTHBASENUMBER_H
#define LIST_1_NTHBASENUMBER_H

#include "NumberCoder.h"
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>

class NthBaseNumber {
public:
    explicit NthBaseNumber(uint64_t init = 0, const std::shared_ptr<NumberCoder> &nc = nullptr);
    explicit NthBaseNumber(CodedNumber &init, const std::shared_ptr<NumberCoder> &nc = nullptr);
    NthBaseNumber(const NthBaseNumber &other);

    [[maybe_unused]] void ChangeBase(const std::shared_ptr<NumberCoder> &newNc);

    NthBaseNumber& operator =(const NthBaseNumber &other);
    NthBaseNumber operator +(NthBaseNumber &other);

    friend std::ostream& operator <<(std::ostream &os, NthBaseNumber& number);
private:
    std::shared_ptr<NumberCoder> _spNumberCoder;
    CodedNumber number;
};

NthBaseNumber::NthBaseNumber(uint64_t init, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<DecimalCoder<10>>();
    number = (*_spNumberCoder)(init);
}

NthBaseNumber::NthBaseNumber(std::vector<uint8_t> &init, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<DecimalCoder<10>>();
    number = std::move(init);
}

NthBaseNumber::NthBaseNumber(const NthBaseNumber &other) {
    if (this == &other) {
        return;
    }

    this->_spNumberCoder = other._spNumberCoder;
    std::copy(other.number.begin(), other.number.end(), this->number.begin());
}

[[maybe_unused]] void NthBaseNumber::ChangeBase(const std::shared_ptr<NumberCoder> &newNc) {
    uint64_t numberCache = (*_spNumberCoder)(number);
    number.clear();

    this->_spNumberCoder = newNc;

    number = (*_spNumberCoder)(numberCache);
}

std::ostream &operator <<(std::ostream &os, NthBaseNumber &number) {
    for (auto &frag : number.number) {
        if (frag > 9) {
            std::cout << static_cast<char>(frag + 55);
        }
        else
        {
            std::cout << static_cast<int>(frag);
        }
    }

    return os;
}

NthBaseNumber &NthBaseNumber::operator =(const NthBaseNumber &other) {
    if (this == &other)
        return *this;

    auto otherNumber = (*other._spNumberCoder)(other.number);
    this->number = (*other._spNumberCoder)(otherNumber);
    this->_spNumberCoder = other._spNumberCoder;

    return *this;
}

NthBaseNumber NthBaseNumber::operator +(NthBaseNumber &other) {
    const auto thisBase = this->_spNumberCoder->getBase();
    const auto otherBase = other._spNumberCoder->getBase();

    if (thisBase != otherBase) {
        thisBase > otherBase ?
            other.ChangeBase(this->_spNumberCoder) :
            this->ChangeBase(other._spNumberCoder);
    }

    std::reverse(this->number.begin(), this->number.end());
    std::reverse(other.number.begin(), other.number.end());

    const auto iterator = (int)fmin(static_cast<int>(this->number.size()), static_cast<int>(other.number.size()));
    const auto max = (int) fmax(static_cast<int>(this->number.size()), static_cast<int>(other.number.size()));
    const auto &longer = this->number.size() > other.number.size() ? this->number : other.number;

    auto sum = std::make_shared<CodedNumber>();
    auto carry = uint8_t {};

    for (int it = 0; it < iterator; it++) {
        const auto num1 = this->number[it];
        const auto num2 = other.number[it];

        uint8_t smallSum = num1 + num2 + carry;

        if (smallSum >= thisBase) {
            carry = smallSum - (thisBase - 1);
            smallSum -= thisBase;
        }
        else {
            carry = 0;
        }

        sum->push_back(smallSum);
    }

    if (iterator == max) {
        sum->push_back(carry);
    }

    for (int it = iterator; it < max; it++){
        sum->push_back(carry + longer[it]);
        carry = 0;
    }

    std::reverse(sum->begin(), sum->end());
    std::reverse(this->number.begin(), this->number.end());
    std::reverse(other.number.begin(), other.number.end());

    return NthBaseNumber(*sum, this->_spNumberCoder);
}

#endif //LIST_1_NTHBASENUMBER_H
