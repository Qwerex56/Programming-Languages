#include <iostream>
#include <memory>
#include "./headers/DecimalCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto tCoder = std::make_shared<DecimalCoder<3>>();
    const auto nCode = std::make_shared<DecimalCoder<27>>();

    CodedNumber number = {2,2,1,1,0,1,2,1,0,2,1,0,1};

    auto item1 = NthBaseNumber(number, tCoder);

    std::cout << item1 << std::endl;

    item1.ChangeBase(nCode);

    std::cout << item1 << std::endl;

    return 0;
}