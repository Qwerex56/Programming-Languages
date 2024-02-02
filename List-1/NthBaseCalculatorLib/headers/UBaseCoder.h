//
// Created by adrianczubaty on 10.10.23.
//

#ifndef LIST_1_UBASECODER_H
#define LIST_1_UBASECODER_H

#include "NumberCoder.h"
#include <cmath>
#include <memory>

class UBaseCoder : public NumberCoder {
public:
    explicit UBaseCoder(int base = 10) : NumberCoder(base) { };
    UBaseCoder& operator =(const UBaseCoder &rhs);
    ~UBaseCoder() override = default;

    CodedNumber operator ()(int64_t number) final;
    int64_t operator ()(const CodedNumber &codedNumber) final;

    [[nodiscard]]
    inline constexpr int getBase() const final {
        return _base;
    }

private:
    void convertToNeg(CodedNumber &number);
};

#endif //LIST_1_UBASECODER_H
