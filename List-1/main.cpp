#include <iostream>
#include <memory>
#include "./headers/DecimalCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto decCoder = std::make_shared<DecimalCoder<3>>();
    const auto hexCoder = std::make_shared<DecimalCoder<2>>();

    auto item1 = NthBaseNumber(9, hexCoder);
    auto item2 = NthBaseNumber(2, decCoder);
    auto item3 = NthBaseNumber();

    item3 = item2 + item1;

    std::cout << item1 << "+" << item2 << "=" << item3 << std::endl;

    std::cout << *(new NthBaseNumber(1231829375098723455, std::make_shared<DecimalCoder<20>>()));

    return 0;
}