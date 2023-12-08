//
// Created by adrianczubaty on 08/12/23.
//

#include "../headers/NthBaseManip.h"
#include "../headers/NthBaseMath.h"

namespace manip = nthBase::manip;

using namespace nthBase;

void manip::shrinkLength(NthBaseNumber &toShrink) {
    auto sign = math::getSign(toShrink);
    decltype(auto) vec = toShrink.getNumber();

    // remove all sign bits
    while (vec.back() == sign) {
        vec.pop_back();
    }

    vec.shrink_to_fit();
    // makes sure that we leave at least one number
    // and sign bit is still there
    vec.push_back(sign);
}

void manip::add(NthBaseNumber &nb, std::vector<uint8_t>::const_iterator position, const uint8_t &elem) {
    decltype(auto) vec = nb.getNumber();

    vec.insert(position, elem);
}

uint8_t manip::pop(nthBase::NthBaseNumber &nb, std::vector<uint8_t>::const_iterator position) {
    decltype(auto) vec = nb.getNumber();

    return *vec.erase(position);
}

uint8_t manip::set(nthBase::NthBaseNumber &nb, std::vector<uint8_t>::size_type position, const uint8_t &elem) {
    decltype(auto) vec = nb.getNumber();
    auto data = vec.at(position);
    vec.at(position) = elem;

    return data;
}