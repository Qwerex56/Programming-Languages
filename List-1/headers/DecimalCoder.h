//
// Created by adrianczubaty on 10.10.23.
//

#ifndef LIST_1_DECIMALCODER_H
#define LIST_1_DECIMALCODER_H

#include "NumberCoder.h"
#include <cmath>

template <int _base>
class DecimalCoder : public NumberCoder {
public:
    ~DecimalCoder() override;

    CodedNumber operator ()(uint8_t number) override;
    uint8_t operator ()(CodedNumber codedNumber) override;
};

template<int base>
DecimalCoder<base>::~DecimalCoder() = default;

template<int base>
CodedNumber DecimalCoder<base>::operator()(uint8_t number) {
    CodedNumber numberInBase;

    while (number > 0) {
        uint8_t remainder = number % base;
        number /= base;

        numberInBase.emplace(numberInBase.begin(), remainder);
    }

    return numberInBase;
}

template<int base>
uint8_t DecimalCoder<base>::operator()(std::vector<uint8_t> codedNumber) {
    auto accumulator = uint8_t {0};

    for (auto it = 0, factor = static_cast<int>(codedNumber.size() - 1); it < codedNumber.size(); it++, factor--) {
        accumulator += codedNumber[it] * std::pow(base, factor);
    }

    return accumulator;
}

#endif //LIST_1_DECIMALCODER_H
