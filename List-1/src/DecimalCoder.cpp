//
// Created by adrianczubaty on 10.10.23.
//

#include "../headers/DecimalCoder.h"

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
    return 0;
}