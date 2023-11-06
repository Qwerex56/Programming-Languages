//
// Created by adrianczubaty on 09.10.23.
//

#include "../headers/NthBaseNumber.h"

NthBaseNumber::NthBaseNumber(int64_t init, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<UBaseCoder<10>>();
    _number = (*_spNumberCoder)(init);
}

NthBaseNumber::NthBaseNumber(std::vector<uint8_t> &init, bool isReversed, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<UBaseCoder<10>>();
    if (!isReversed) {
        std::reverse(init.begin(), init.end());
    }
    _number = std::move(init);
}

NthBaseNumber::NthBaseNumber(std::vector<uint8_t> &&init, bool isReversed, const std::shared_ptr<NumberCoder> &nc) {
    _spNumberCoder = nc ? nc : std::make_shared<UBaseCoder<10>>();
    if (!isReversed) {
        std::reverse(init.begin(), init.end());
    }
    _number = std::move(init);
}

NthBaseNumber::NthBaseNumber(const NthBaseNumber &other) {
    if (this == &other) {
        return;
    }

    this->_spNumberCoder = other._spNumberCoder;
    std::copy(other._number.begin(), other._number.end(), this->_number.begin());
}

[[maybe_unused]]
void NthBaseNumber::ChangeBase(const std::shared_ptr<NumberCoder> &newNc) {
    int64_t numberCache = (*_spNumberCoder)(_number);
    _number.clear();

    this->_spNumberCoder = newNc;

    _number = (*_spNumberCoder)(numberCache);
}

bool NthBaseNumber::isNegative(const NthBaseNumber &what) noexcept {
    auto signBit = *(--what._number.end());
    auto base = what.getBase();
    return getSignBit(signBit, base);
}

std::ostream &operator <<(std::ostream &os, NthBaseNumber &number) {
    std::reverse(number._number.begin(), number._number.end());

    for (auto &frag : number._number) {
        if (frag > 9) {
            std::cout << static_cast<char>(frag + 55);
        }
        else
        {
            std::cout << static_cast<int>(frag);
        }
    }

    std::reverse(number._number.begin(), number._number.end());
    return os;
}

NthBaseNumber &NthBaseNumber::operator =(const NthBaseNumber &other) {
    if (this == &other)
        return *this;

    auto otherNumber = (*other._spNumberCoder)(other._number);
    this->_number = (*other._spNumberCoder)(otherNumber);
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
    EqualizeLength(this->_number, other._number, thisBase);

    auto sum = std::make_shared<CodedNumber>();
    auto carry = uint8_t { 0 };

    for (int i = 0; i < this->_number.size(); i++) {
        const auto num1 = this->_number[i];
        const auto num2 = other._number[i];

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

    auto retSum = NthBaseNumber(*sum, true, this->_spNumberCoder);

    ShrinkLength(this->_number, thisBase);
    ShrinkLength(other._number, otherBase);
    ShrinkLength(retSum._number, retSum.getBase());

    return retSum;
}

NthBaseNumber NthBaseNumber::operator -(NthBaseNumber &other) {
    return operator+(other.negate());
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

    for (const auto &factorNum2 : other._number) {
        auto carry = 0;
        multiple = NthBaseNumber(0, this->_spNumberCoder);
        multiple._number.insert(multiple._number.cbegin(), additionalZeros, 0);

        for (const auto &factorNum1 : this->_number) {
            auto smallSum = factorNum1 * factorNum2 + carry;
            CodedNumber codedSmallSum = (*this->_spNumberCoder)(smallSum);

            if (smallSum > this->getBase()) {
                carry = codedSmallSum.back();
                multiple._number.push_back(codedSmallSum.front());
            }
            else {
                multiple._number.push_back(smallSum);
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

const NthBaseNumber NthBaseNumber::operator ++(int) {
    const auto old = *this;
    operator++();
    return old;
}

bool NthBaseNumber::operator ==(const NthBaseNumber &other) const {
    if (this->_number.size() != other._number.size()) {
        return false;
    }

    for (int i = 0; i < this->_number.size(); i++) {
        if (other._number[i] != this->_number[i]) {
            return false;
        }
    }

    return true;
}

bool NthBaseNumber::operator !=(const NthBaseNumber &other) const {
    return !(*this == other);
}

bool NthBaseNumber::operator <(const NthBaseNumber &other) const {
    auto thisSign = getSignBit(*this->_number.crbegin(), this->getBase());
    auto otherSign = getSignBit(*other._number.crbegin(), other.getBase());
    auto const areBothNegative = this->isNegative() && other.isNegative();

    if (thisSign != otherSign) {
        return thisSign > otherSign;
    }

    if (this->_number.size() < other._number.size()) {
        return !areBothNegative;
    }

    if (this->_number.size() > other._number.size()) {
        return areBothNegative;
    }

    auto it = this->_number.crbegin();
    auto oIt = other._number.crbegin();

    while (it != this->_number.crend()) {
        if (*it < *oIt) {
            return true;
        }

        it++;
        oIt++;
    }

    return false;
}

bool NthBaseNumber::operator >(const NthBaseNumber &other) const {
    return other < *this;
}

bool NthBaseNumber::operator <=(const NthBaseNumber &other) const {
    return !(*this > other);
}

bool NthBaseNumber::operator >=(const NthBaseNumber &other) const {
    return !(*this < other);
}

inline void NthBaseNumber::EqualizeLength(std::vector<uint8_t> &lhs, std::vector<uint8_t> &rhs, const int base) {
    auto lenDiff = abs(static_cast<int>(lhs.size() - rhs.size())) + 1;
    auto const once = 1;

    auto pushLength = [&lenDiff, &once, &base](CodedNumber &smaller, CodedNumber &bigger) -> void {
        smaller.insert(smaller.cend(), lenDiff, NthBaseNumber::getSignBit(*smaller.crbegin(), base));
        bigger.insert(bigger.cend(), once, NthBaseNumber::getSignBit(*bigger.crbegin(), base));
    };

    lhs.size() < rhs.size() ?
        pushLength(lhs, rhs) :
        pushLength(rhs, lhs);
}

inline void NthBaseNumber::ShrinkLength(std::vector<uint8_t> &rhs, int const base) {
    auto const what = base / 2;
    auto const biggerEqual = [&what](int i) {
        return i >= what;
    };
    auto const smaller = [&biggerEqual](int i) {
        return !biggerEqual(i);
    };

    auto const shrink = [&biggerEqual, &smaller, &base](CodedNumber &vec) {
        auto posToDel = 1;

        if (biggerEqual(*vec.crbegin())) {
            while (vec[vec.size() - posToDel] == base - 1) {
                posToDel++;
            }
        }
        else {
            while (vec[vec.size() - posToDel] == 0) {
                posToDel++;
            }
        }
        posToDel -= 2;
        for (int i = 0; i < posToDel; i++) {
            vec.pop_back();
        }
    };

    shrink(rhs);
}

void NthBaseNumber::PushCarryOver(NthBaseNumber &where, int carry) {
    auto &number = where._number;

    auto codedCarry = (*where._spNumberCoder)(carry);
    if (*codedCarry.crbegin() == 0) {
        codedCarry.erase(codedCarry.cend());
    }
    number.insert(number.cend(), codedCarry.cbegin(), codedCarry.cend());
}

/// Returns base - 1 if number is negative, 0 otherwise
/// Helps to determine if number is negative
uint8_t NthBaseNumber::getSignBit(const uint8_t &sign, const int base) {
    auto result = sign >= (base / 2) ?
            sign :
            0;
    return result;
}

CodedNumber NthBaseNumber::negate(std::vector<uint8_t> numToNegate, const int base) {
    auto negative = CodedNumber(numToNegate.size(), base - 1);
    auto carry = 1;
    EqualizeLength(numToNegate, negative, base);

    for (auto i = 0; i < negative.size(); i++) {
        negative[i] -= numToNegate[i];
    }

    for (auto &mag : negative) {
        mag += carry;
        if (mag >= base) {
            mag -= base;
            carry = 1;
        }
        else {
            carry = 0;
        }
    }

    ShrinkLength(negative, base);
    return negative;
}
