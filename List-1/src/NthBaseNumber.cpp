//
// Created by adrianczubaty on 09.10.23.
//

#include "../headers/NthBaseNumber.h"

NthBaseNumber::NthBaseNumber(uint64_t init, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<DecimalCoder<10>>();
    number = (*_spNumberCoder)(init);
}

NthBaseNumber::NthBaseNumber(std::vector<uint8_t> &init, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<DecimalCoder<10>>();
    std::reverse(init.begin(), init.end());
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
    std::reverse(number.number.begin(), number.number.end());

    for (auto &frag : number.number) {
        if (frag > 9) {
            std::cout << static_cast<char>(frag + 55);
        }
        else
        {
            std::cout << static_cast<int>(frag);
        }
    }

    std::reverse(number.number.begin(), number.number.end());
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
        other.ChangeBase(this->_spNumberCoder);
    }

    // Makes sure that both of the vectors are same size
    EqualizeLength(this->number, other.number);

    auto sum = std::make_shared<CodedNumber>();
    auto carry = uint8_t {};

    for (int i = 0; i < this->number.size(); i++) {
        const auto num1 = this->number[i];
        const auto num2 = other.number[i];

        uint8_t smallSum = num1 + num2 + carry;

        if (smallSum >= thisBase) {
            carry = 1;
            smallSum -= thisBase;
        }
        else {
            carry = 0;
        }

        sum->push_back(smallSum);
    }

    auto retSum = NthBaseNumber(*sum, this->_spNumberCoder);
    PushCarryOver(retSum, carry);
    ShrinkLength(this->number, other.number);

    return retSum;
}

NthBaseNumber NthBaseNumber::operator -(NthBaseNumber &other) {
    const auto thisBase = this->_spNumberCoder->getBase();
    const auto otherBase = other._spNumberCoder->getBase();

    if (thisBase != otherBase) {
        other.ChangeBase(this->_spNumberCoder);
    }

    if (*this < other) {
        throw "Cannot substract";
    }

    // Makes sure that both of the vectors are same size
    EqualizeLength(this->number, other.number);

    auto sum = std::make_shared<CodedNumber>();
    auto carry = uint8_t {};

    for (int i = 0; i < this->number.size(); i++) {
        const auto num1 = this->number[i];
        const auto num2 = other.number[i];

        uint8_t smallSum = num1 - num2 - carry;

        if (smallSum < 0) {
            carry = 1;
            smallSum += thisBase;
        }
        else {
            carry = 0;
        }

        sum->push_back(smallSum);
    }

    auto retSum = NthBaseNumber(*sum, this->_spNumberCoder);
    ShrinkLength(this->number, other.number);

    return retSum;
}

NthBaseNumber NthBaseNumber::operator*(NthBaseNumber &other) {
    const auto thisBase = this->_spNumberCoder->getBase();
    const auto otherBase = other._spNumberCoder->getBase();

    if (thisBase != otherBase) {
        other.ChangeBase(this->_spNumberCoder);
    }

    auto additionalZeros = 0;

    auto multiple = NthBaseNumber(0, this->_spNumberCoder);

    auto sum = NthBaseNumber(0, this->_spNumberCoder);

    for (const auto &factorNum2 : other.number) {
        auto carry = 0;
        multiple = NthBaseNumber(0, this->_spNumberCoder);
        multiple.number.insert(multiple.number.cbegin(), additionalZeros, 0);

        for (const auto &factorNum1 : this->number) {
            auto smallSum = factorNum1 * factorNum2 + carry;
            CodedNumber codedSmallSum = (*this->_spNumberCoder)(smallSum);

            if (smallSum > this->getBase()) {
                carry = codedSmallSum.back();
                multiple.number.push_back(codedSmallSum.front());
            }
            else {
                multiple.number.push_back(smallSum);
                carry = 0;
            }
        }

        PushCarryOver(multiple, carry);
        sum = sum + multiple;
        additionalZeros += 1;
    }

    return sum;
}

NthBaseNumber& NthBaseNumber::operator ++() {
    auto inc = NthBaseNumber(1, std::shared_ptr<NumberCoder>(this->_spNumberCoder));
    *this = *this + inc;
    return *this;
}

/*NthBaseNumber NthBaseNumber::operator ++(int) {
    auto old = *this;
    operator++();
    return old;
}*/

bool NthBaseNumber::operator ==(const NthBaseNumber &other) const {
    if (this->number.size() != other.number.size()) {
        return false;
    }

    for (int i = 0; i < this->number.size(); i++) {
        if (other.number[i] != this->number[i]) {
            return false;
        }
    }

    return true;
}

bool NthBaseNumber::operator !=(const NthBaseNumber &other) const {
    return !(*this == other);
}

bool NthBaseNumber::operator <(NthBaseNumber &other) {
    EqualizeLength(this->number, other.number);

    auto it = this->number.crbegin();
    auto otherIt = other.number.crbegin();

    if (*otherIt == 0) {
        return false;
    }

    while (it != this->number.crend()) {
        if (static_cast<int>(*it) < static_cast<int>(*otherIt)) {
            return true;
        }

        it++;
        otherIt++;
    }

    return false;
}

bool NthBaseNumber::operator >(NthBaseNumber &other) {
    return other < *this;
}

bool NthBaseNumber::operator <=(NthBaseNumber &other) {
    return !(*this > other);
}

bool NthBaseNumber::operator >=(NthBaseNumber &other) {
    return !(*this < other);
}

inline void NthBaseNumber::EqualizeLength(std::vector<uint8_t> &lhs, std::vector<uint8_t> &rhs) {
    if (lhs.size() == rhs.size()) {
        return;
    }

    auto lenDiff = abs(static_cast<int>(lhs.size() - rhs.size()));

    lhs.size() < rhs.size() ?
        lhs.insert(lhs.cend(), lenDiff, 0) :
        rhs.insert(rhs.cend(), lenDiff, 0);
}

inline void NthBaseNumber::ShrinkLength(std::vector<uint8_t> &lhs, std::vector<uint8_t> &rhs) {
    lhs.shrink_to_fit();
    rhs.shrink_to_fit();
}

void NthBaseNumber::PushCarryOver(NthBaseNumber &where, int carry) {
    auto base = where.getBase();
    auto &number = where.number;

    auto codedCarry = (*where._spNumberCoder)(carry);
    number.insert(number.cend(), codedCarry.cbegin(), codedCarry.cend());
}