#include <iostream>
#include <memory>
#include <cmath>

#include "NthBase.h"

int main() {
    auto coder = std::make_shared<UBaseCoder>(UBaseCoder(10));
    auto item1 = nthBase::NthBaseNumber(2, coder);
    auto item2 = nthBase::NthBaseNumber(1, coder);
    auto item3 = item1 / item2;

    std::cout << item3;

    sin(4);
}