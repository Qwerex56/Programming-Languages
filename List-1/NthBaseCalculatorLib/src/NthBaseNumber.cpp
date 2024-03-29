//
// Created by adrianczubaty on 09.10.23.
//

#include "../headers/NthBaseNumber.h"

#include "../headers/NthBaseMath.h"
#include "../headers/NthBaseManip.h"

#include "../headers/NthBaseExceptions.h"

using namespace nthBase;

NthBaseNumber::NthBaseNumber(int64_t init, const std::shared_ptr<NumberCoder> &nc) {
    _numberCoder = nc ? nc : std::make_shared<UBaseCoder>(NATURAL_SYSTEM);
    _number = (*_numberCoder)(init);
}

[[maybe_unused]]
NthBaseNumber::NthBaseNumber(std::vector<uint8_t> &init,
                             const std::shared_ptr<NumberCoder> &nc,
                             bool isReversed) {
    _numberCoder = nc ? nc : std::make_shared<UBaseCoder>(NATURAL_SYSTEM);
    if (!isReversed) {
        std::reverse(init.begin(), init.end());
    }
    _number = std::move(init);
}

NthBaseNumber::NthBaseNumber(std::vector<uint8_t> &&init,
                             const std::shared_ptr<NumberCoder> &nc,
                             bool isReversed) {
    _numberCoder = nc ? nc : std::make_shared<UBaseCoder>(NATURAL_SYSTEM);
    if (!isReversed) {
        std::reverse(init.begin(), init.end());
    }
    _number = std::move(init);
}

NthBaseNumber& NthBaseNumber::operator =(const NthBaseNumber &other) {
    if (this == &other)
        return *this;

    this->_numberCoder = other._numberCoder;
    this->_number = CodedNumber(other._number);

    return *this;
}

[[maybe_unused]]
NthBaseNumber::NthBaseNumber(const NthBaseNumber &other) {
    if (this == &other) {
        return;
    }

    this->_numberCoder = other._numberCoder;
    this->_number = CodedNumber(other._number);
}

[[maybe_unused]]
NthBaseNumber::NthBaseNumber(const NthBaseNumber &&other) noexcept {
    if (this == &other) {
        return;
    }

    this->_numberCoder = other._numberCoder;
    this->_number = CodedNumber(other._number);
}

/// Limited usage to numbers of size int64
[[maybe_unused]]
void NthBaseNumber::ChangeBase(const std::shared_ptr<NumberCoder> &newNc) {
    int64_t numberCache = (*_numberCoder)(_number);
    _number.clear();

    this->_numberCoder = newNc;

    _number = (*_numberCoder)(numberCache);
}

/// Works very slowly,
/// Limited to positive integers
[[maybe_unused]]
std::tuple<NthBaseNumber, NthBaseNumber> NthBaseNumber::slowDivision(NthBaseNumber &lhs,
                                                                     NthBaseNumber &rhs) {
    auto mem = NthBaseNumber(0, lhs._numberCoder); mem._number.clear();

    auto result = NthBaseNumber(0, lhs._numberCoder); result._number.clear();
    auto &resultNum = result._number;

    auto divide = [&]() {
        auto partQuot = NthBaseNumber(0, lhs._numberCoder);
        auto remainder = NthBaseNumber(0, lhs._numberCoder);

        for (int i = 0; i < lhs.getBase(); i++) {
            auto factor = NthBaseNumber(i, lhs._numberCoder);
            auto part = rhs * factor;

            manip::shrinkLength(mem);
            if (mem < part) {
                partQuot = NthBaseNumber(--i, lhs._numberCoder);
                break;
            }
        }

        remainder = math::negative(rhs * partQuot) + mem;

        mem._number.clear(); mem._number.push_back(0);
        mem._number.insert(mem._number.begin(), remainder._number.front());

        resultNum.insert(result._number.begin(), partQuot._number.front());
    };

    std::for_each(lhs._number.crbegin(), lhs._number.crend(), [&](auto const &item) {
        mem._number.insert(mem._number.begin(), item);
        divide();
    });

    auto modulo = mem;
    return {result, modulo};
}

NthBaseNumber& NthBaseNumber::operator +=(const NthBaseNumber &rhs) {
    const auto thisBase = this->_numberCoder->getBase();
    const auto otherBase = rhs._numberCoder->getBase();

    if (thisBase != otherBase) {
        throw different_base_error();
    }

    auto result = NthBaseNumber(0, this->_numberCoder); result._number.clear();
    auto carry = uint8_t { 0 };
    
    auto longer = this->getSize() > rhs.getSize()? 
            this->getSize() : 
            rhs.getSize();
    
    auto getI = [](size_t position, const NthBaseNumber& num) -> uint8_t {
        uint8_t number;

        try {
            number = num.getNumberConst().at(position);
        } catch (std::out_of_range &exc) {
            number = uint8_t  { 0 };
        }

        return number;
    };

    for (int i = 0; i < longer; i++) {
        auto num1 = getI(i, *this);
        const auto num2 = getI(i, rhs);

        num1 += num2 + carry;

        if (num1 >= thisBase) {
            carry = 1;
            num1 -= thisBase;
        }
        else {
            carry = 0;
        }

        manip::add(result, result.getNumber().cend(), num1);
    }

    *this = result;
    manip::shrinkLength(*this);

    return *this;
}

NthBaseNumber& NthBaseNumber::operator -=(const NthBaseNumber &rhs) {
    return operator+=(math::negative(rhs));
}

NthBaseNumber& NthBaseNumber::operator *=(const NthBaseNumber &other) {
    if (other == NthBaseNumber(0, other._numberCoder) || *this == NthBaseNumber(0, other._numberCoder)) {
        *this = NthBaseNumber(0, other._numberCoder);
        return *this;
    }

    const auto thisBase = this->getBase();
    const auto otherBase = other.getBase();

    this->_number.insert(this->_number.cend(), 2, this->_number.back());

    if (thisBase != otherBase) {
        throw different_base_error();
    }

    auto additionalZeros = 0;

    auto sum = NthBaseNumber(0, this->_numberCoder);

    for (const auto &factorNum2 : other.getNumberConst()) {
        auto carry = 0;
        auto multiple = NthBaseNumber(0, this->_numberCoder);

        multiple._number.clear();
        multiple._number.insert(multiple._number.cbegin(), additionalZeros++, 0);

        for (const auto &factorNum1 : this->_number) {
            auto partialSum = factorNum1 * factorNum2 + carry;

            if (partialSum >= this->getBase()) {
                carry = partialSum / thisBase;
                multiple._number.push_back(partialSum % thisBase);
            }
            else {
                multiple._number.push_back(partialSum);
                carry = 0;
            }
        }

        sum += multiple;
    }

    if (math::isNegative(other)) {
        auto addNeg = math::negative(*this);
        addNeg._number.insert(addNeg._number.cbegin(), additionalZeros, 0);

        sum += addNeg;
    }

    *this = sum;

    return *this;
}

NthBaseNumber& NthBaseNumber::operator /=(const NthBaseNumber &rhs) {
    if (rhs == NthBaseNumber(0, rhs._numberCoder)) throw divide_by_zero();
    return *this;
}

NthBaseNumber& NthBaseNumber::operator %=(const nthBase::NthBaseNumber &rhs) {
    if (rhs == NthBaseNumber(0, rhs._numberCoder)) throw divide_by_zero();
    return *this;
}

NthBaseNumber& NthBaseNumber::operator ++() {
    auto inc = NthBaseNumber(1, this->_numberCoder);
    *this += inc;
    return *this;
}

const NthBaseNumber NthBaseNumber::operator ++(int) {
    const auto old = *this;
    operator++();
    return old;
}

NthBaseNumber& NthBaseNumber::operator--() {
    auto decrement = NthBaseNumber(-1, this->_numberCoder);
    *this += decrement;
    return *this;
}

const NthBaseNumber NthBaseNumber::operator--(int) {
    const auto old = *this;
    operator--();
    return old;
}

bool NthBaseNumber::operator ==(const NthBaseNumber &rhs) const {
    if (this->getSize() != rhs.getSize()) {
        return false;
    }

    for (int i = 0; i < this->_number.size(); i++) {
        if (rhs._number[i] != this->_number[i]) {
            return false;
        }
    }

    return true;
}

bool NthBaseNumber::operator !=(const NthBaseNumber &other) const {
    return !(*this == other);
}

bool NthBaseNumber::operator <(const NthBaseNumber &other) const {
    auto thisSign = math::getSign(*this);
    auto otherSign = math::getSign(other);
    auto const areBothNegative = math::isNegative(*this) && math::isNegative(other);

    if (thisSign != otherSign) {
        return thisSign > otherSign;
    }

    if (this->getSize() < other.getSize()) {
        return !areBothNegative;
    }

    if (this->getSize() > other.getSize()) {
        return areBothNegative;
    }

    auto it = this->_number.crbegin();
    auto oIt = other._number.crbegin();

    while (*it == *oIt) {
        it++;
        oIt++;

        if (it == this->_number.crend()) {
            return false;
        }
    }

    return *it < *oIt;
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

[[maybe_unused]]
void NthBaseNumber::pushCarryOver(NthBaseNumber &where, int carry) {
    auto &number = where._number;

    auto codedCarry = (*where._numberCoder)(carry);
    if (*codedCarry.crbegin() == 0) {
        codedCarry.erase(codedCarry.cend());
    }
    number.insert(number.cend(), codedCarry.cbegin(), codedCarry.cend());
}