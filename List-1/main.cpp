#include <iostream>
#include <memory>
#include "./headers/DecimalCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto hexCoder = std::make_shared<DecimalCoder<10>>();
    const auto fourthCoder = std::make_shared<DecimalCoder<4>>();

    auto item1 = NthBaseNumber(15, hexCoder);
    auto item2 = NthBaseNumber(5, fourthCoder);

    item2.ChangeBase(hexCoder);

    std::cout << item1 << std::endl << "+ " << item2 << std::endl << "----" << std::endl << item1 + item2;

    return 0;
}