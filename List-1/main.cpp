#include <iostream>
#include <memory>
#include "./headers/UBaseCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto tCoder = std::make_shared<UBaseCoder<10>>();
    auto item1 = NthBaseNumber(-10, tCoder);
    auto item2 = NthBaseNumber(10, tCoder);
    auto item3 = (item1 + item2);

//    item1.negate();

    std::cout << "Item1: " << item1 << std::endl;
    std::cout << "Item2: " << item2 << std::endl;

    std::cout << (item1 < item2);

    return 0;
}