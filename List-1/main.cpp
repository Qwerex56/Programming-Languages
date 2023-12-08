#include <iostream>
#include "NthBaseNumber.h"
#include <memory>

int main() {
    auto coder = std::make_shared<UBaseCoder>(UBaseCoder(10));
    auto item1 = nthBase::NthBaseNumber(23, coder);
    auto item2 = nthBase::NthBaseNumber(43, coder);

    std::cout << item1;
}