//
// Created by adrianczubaty on 09/12/23.
//

#ifndef LIST_1_NTHBASE_H
#define LIST_1_NTHBASE_H

#include <memory>

#include "./NthBaseExceptions.h"
#include "./NthBaseMath.h"
#include "./NthBaseManip.h"
#include "./NthBaseNumber.h"

namespace nthBase {
    [[maybe_unused]]
    inline std::shared_ptr<UBaseCoder> makeSharedCoder(const uint8_t base) {
        if (base < 2) throw bad_base_error();
        return std::make_shared<UBaseCoder>(base);
    }

    [[maybe_unused]]
    inline NthBaseNumber createNumberInBase(const int64_t number, const uint8_t base) {
        if (base < 2) throw bad_base_error();
        auto sharedCoder = makeSharedCoder(base);
        return NthBaseNumber(number, sharedCoder);
    }
}

#endif //LIST_1_NTHBASE_H
