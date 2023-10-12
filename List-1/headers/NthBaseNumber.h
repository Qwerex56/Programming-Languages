//
// Created by adrianczubaty on 09.10.23.
//

#ifndef LIST_1_NTHBASENUMBER_H
#define LIST_1_NTHBASENUMBER_H

#include "NumberCoder.h"
#include <iostream>
#include <memory>
#include <utility>

class NthBaseNumber {
public:
    explicit NthBaseNumber(int init, const std::shared_ptr<NumberCoder> &nc = nullptr);
    NthBaseNumber(const NthBaseNumber &other);

    [[maybe_unused]] void ChangeBase(const std::shared_ptr<NumberCoder> &newNc);

    NthBaseNumber& operator =(const NthBaseNumber &other);
    NthBaseNumber& operator +(const NthBaseNumber &other);

    friend std::ostream& operator <<(std::ostream &os, NthBaseNumber& number);
private:
    std::shared_ptr<NumberCoder> _spNumberCoder;
    CodedNumber number;
};

NthBaseNumber::NthBaseNumber(int init, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc;

    if (nc == nullptr) {
        std::cout << "Probably null ref";
    }

    number = (*_spNumberCoder)(init);
}

NthBaseNumber::NthBaseNumber(const NthBaseNumber &other) {
    if (this == &other) {
        return;
    }

    this->_spNumberCoder = other._spNumberCoder;
    std::copy(other.number.begin(), other.number.end(), this->number.begin());
}

[[maybe_unused]] void NthBaseNumber::ChangeBase(const std::shared_ptr<NumberCoder> &newNc) {
    uint8_t numberCache = (*_spNumberCoder)(number);
    number.clear();

    this->_spNumberCoder = newNc;

    number = (*_spNumberCoder)(numberCache);
}

std::ostream &operator <<(std::ostream &os, NthBaseNumber &number) {
    for (auto &frag : number.number) {
        if (frag > 9) {
            std::cout << static_cast<char>(frag + 55) << " ";
        }
        else
        {
            std::cout << static_cast<int>(frag) << " ";
        }
    }

    return os;
}

NthBaseNumber &NthBaseNumber::operator =(const NthBaseNumber &other) {
    if (this == &other)
        return *this;

    auto otherNumber = (*other._spNumberCoder)(other.number);
    this->number = (*this->_spNumberCoder)(otherNumber);

    return *this;
}

NthBaseNumber &NthBaseNumber::operator+(const NthBaseNumber &other) {
    const auto num1 = (*this->_spNumberCoder)(this->number);
    const auto num2 = (*other._spNumberCoder)(other.number);

    const auto result = new NthBaseNumber(num1 + num2, this->_spNumberCoder);

    return *result;
}

#endif //LIST_1_NTHBASENUMBER_H
