#include <iostream>
#include <memory>
#include "./headers/UBaseCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto tCoder = std::make_shared<UBaseCoder<2>>();
    auto item1 = NthBaseNumber(-8, tCoder);
    auto item2 = NthBaseNumber(7, tCoder);
    auto item3 = (item1 + item2);

    std::cout << item1 << " + " << item2 << std::endl;

    std::cout << item3 << std::endl;
    return 0;
}