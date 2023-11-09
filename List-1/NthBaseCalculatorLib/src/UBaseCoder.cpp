//
// Created by adrianczubaty on 07/11/23.
//

#include "../headers/UBaseCoder.h"

UBaseCoder& UBaseCoder::operator =(const UBaseCoder &rhs) {
    if (this == &rhs) {
        return *this;
    }

    this->_base = rhs._base;
    return *this;
}

CodedNumber UBaseCoder::operator()(int64_t number) {
    auto isNegative = false;
    CodedNumber numberInBase;

    if (number < 0) {
        isNegative = true;
        number *= -1;
    }

    while (number > 0) {
        uint8_t remainder = number % _base;
        number /= _base;

        numberInBase.push_back(remainder);
    }

    // Add additional bit for sign
    numberInBase.push_back(0);

    if (isNegative) {
        convertToNeg(numberInBase);
    }

    return numberInBase;
}

int64_t UBaseCoder::operator()(const CodedNumber &codedNumber) {
    auto accumulator = int64_t { 0 };
    auto factor { 0 };

    for (auto & frag : codedNumber) {
        accumulator += frag * std::pow(_base, factor);
        factor += 1;
    }

    if (codedNumber[codedNumber.size() - 1] >= getBase() / 2) {
        std::cout << *codedNumber.end() << std::endl;
        accumulator -= std::pow(_base, factor);
    }

    return accumulator;
}

void UBaseCoder::convertToNeg(CodedNumber &number) {
    auto convertedNumber = std::vector(number.size(), static_cast<uint8_t>(_base - 1));
    auto carry = 1;

    for (auto i = 0; i < number.size(); i++) {
        convertedNumber[i] -= number[i];
    }

    for (auto & mag : convertedNumber) {
        mag += carry;
        if (mag >= _base) {
            mag -= _base;
            carry = 1;
        } else {
            carry = 0;
        }
    }

    number = convertedNumber;
}