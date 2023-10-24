//
// Created by adrianczubaty on 10.10.23.
//

#ifndef LIST_1_DECIMALCODER_H
#define LIST_1_DECIMALCODER_H

#include "../Interfaces/NumberCoder.h"
#include <cmath>

template <int _base>
class DecimalCoder : public NumberCoder {
public:
    ~DecimalCoder() override;

    CodedNumber operator ()(uint64_t number) override;
    uint64_t operator ()(CodedNumber codedNumber) override;

    [[nodiscard]] inline constexpr int getBase() const override {
        return _base;
    }
};

template<int base>
DecimalCoder<base>::~DecimalCoder() = default;

template<int base>
CodedNumber DecimalCoder<base>::operator()(uint64_t number) {
    CodedNumber numberInBase;

    while (number > 0) {
        uint8_t remainder = number % base;
        number /= base;

        numberInBase.push_back(remainder);
    }

    return numberInBase;
}

template<int base>
uint64_t DecimalCoder<base>::operator()(std::vector<uint8_t> codedNumber) {
    auto accumulator = uint64_t {0};
    auto factor { 0 };

    for (auto & frag : codedNumber) {
        accumulator += frag * std::pow(base, factor);
        factor += 1;
    }

    return accumulator;
}
#endif //LIST_1_DECIMALCODER_H
