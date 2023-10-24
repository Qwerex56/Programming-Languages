//
// Created by adrianczubaty on 10.10.23.
//

#ifndef LIST_1_NUMBERCODER_H
#define LIST_1_NUMBERCODER_H

#include <iostream>
#include <vector>
#include <cstdint>

#define CodedNumber std::vector<uint8_t>

class NumberCoder {
public:
    virtual ~NumberCoder() = default;

    virtual CodedNumber operator ()(uint64_t numberToCode) = 0;
    virtual uint64_t operator ()(CodedNumber numberToDecode) = 0;

    [[nodiscard]] virtual inline constexpr int getBase() const = 0;
};

#endif //LIST_1_NUMBERCODER_H
