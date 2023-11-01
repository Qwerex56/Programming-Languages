//
// Created by adrianczubaty on 10.10.23.
//

#ifndef LIST_1_UBASECODER_H
#define LIST_1_UBASECODER_H

#include "../Interfaces/NumberCoder.h"
#include <cmath>
#include <memory>

template <int _base>
class UBaseCoder : public NumberCoder {
public:
    ~UBaseCoder() override;

    CodedNumber operator ()(int64_t number) final;
    int64_t operator ()(const CodedNumber &codedNumber) final;

    [[nodiscard]]
    inline constexpr int getBase() const final {
        return _base;
    }

private:
    /*
     * Second and third step in converting _number to U`x base.
     * Adds 1 and sign bit
     * */
    void convertToNeg(CodedNumber &number);
};

template<int base>
UBaseCoder<base>::~UBaseCoder() = default;

template<int base>
CodedNumber UBaseCoder<base>::operator()(int64_t number) {
    auto isNegative = false;
    CodedNumber numberInBase;

    if (number < 0) {
        isNegative = true;
        number *= -1;
    }

    while (number > 0) {
        uint8_t remainder = number % base;
        number /= base;

        numberInBase.push_back(remainder);
    }

    // Add additional bit for sign
    numberInBase.push_back(0);

    if (isNegative) {
        convertToNeg(numberInBase);
    }

    return numberInBase;
}

template<int base>
int64_t UBaseCoder<base>::operator()(const CodedNumber &codedNumber) {
    auto accumulator = int64_t { 0 };
    auto factor { 0 };

    for (auto & frag : codedNumber) {
        accumulator += frag * std::pow(base, factor);
        factor += 1;
    }

    if (codedNumber[codedNumber.size() - 1] == getBase() - 1) {
        std::cout << *codedNumber.end() << std::endl;
        accumulator -= (std::pow(base, factor));
    }

    return accumulator;
}

template<int base>
void UBaseCoder<base>::convertToNeg(CodedNumber &number) {
    auto convertedNumber = std::vector(number.size(), static_cast<uint8_t>(base - 1));
    auto carry = 1;

    for (auto i = 0; i < number.size(); i++) {
        convertedNumber[i] -= number[i];
    }

    for (auto & mag : convertedNumber) {
        mag += carry;
        if (mag >= base) {
            mag -= base;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    
    number = convertedNumber;
}

#endif //LIST_1_UBASECODER_H
