#include <iostream>
#include <memory>
#include "./headers/UBaseCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto tCoder = std::make_shared<UBaseCoder<2>>();
    auto item = NthBaseNumber(-5, tCoder);
    auto i = (*tCoder)({1, 1, 0, 1});

    std::cout << item << std::endl;
    std::cout << i << std::endl;

    return 0;
}