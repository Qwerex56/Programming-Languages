//
// Created by adrianczubaty on 10.10.23.
//

#ifndef LIST_1_NUMBERCODER_H
#define LIST_1_NUMBERCODER_H

#include <iostream>
#include <vector>
#include <cstdint>
#include "./NthBaseExceptions.h"

#define CodedNumber std::vector<uint8_t>

class NumberCoder {
public:
    explicit NumberCoder(int base = 10) : _base(base) {
        if (base < 2) throw nthBase::bad_base_error();
    }
    virtual ~NumberCoder() = default;

    virtual CodedNumber operator ()(int64_t numberToCode) = 0;
    virtual int64_t operator ()(const CodedNumber &numberToDecode) = 0;

    [[nodiscard]] virtual inline constexpr int getBase() const = 0;

protected:
    int _base;
};

#endif //LIST_1_NUMBERCODER_H
