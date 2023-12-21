#include <iostream>
#include <memory>

#include "NthBase.h"

int main() {
    auto coder = std::make_shared<UBaseCoder>(UBaseCoder(10));
    auto item1 = nthBase::NthBaseNumber(2, coder);
    auto item2 = nthBase::NthBaseNumber(1, coder);
    auto item3 = item1 / item2;

    std::cout << item3 << std::endl;

    auto rat1 = nthBase::rational::NthRational(2, 2, 10);
    auto rat2 = nthBase::rational::NthRational(2, 2, 10);

    auto rat3 = rat1 + rat2;

    std::cout << rat3 << std::endl;

    return 0;
}