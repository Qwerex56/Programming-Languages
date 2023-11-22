#include <iostream>
#include "NthBaseNumber.h"
#include <memory>

int main() {
    auto coder = std::make_shared<UBaseCoder>(UBaseCoder(10));
    auto item1 = NthBaseNumber(928, coder);
    auto item2 = NthBaseNumber(38, coder);
    auto item3 = NthBaseNumber::slowDivision(item1, item2);

    std::cout << get<0>(item3) << " = " << item1 << " / " << item2 << "\nRemainder: " << get<1>(item3);
}