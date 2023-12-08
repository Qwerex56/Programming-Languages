//
// Created by adrianczubaty on 08/12/23.
//

#include "./NthBaseNumber.h"

#ifndef LIST_1_NTHBASEMANIP_H
#define LIST_1_NTHBASEMANIP_H

namespace nthBase::manip {
    [[maybe_unused]]
    void shrinkLength(NthBaseNumber &toShrink);

    void add(NthBaseNumber &nb,
             std::vector<uint8_t>::const_iterator position,
             const uint8_t &elem);

    uint8_t pop(NthBaseNumber &nb,
                std::vector<uint8_t>::const_iterator position);

    uint8_t set(NthBaseNumber &nb,
                std::vector<uint8_t>::size_type position,
                const uint8_t &elem);
}

#endif //LIST_1_NTHBASEMANIP_H
