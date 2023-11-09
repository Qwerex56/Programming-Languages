#include <iostream>
#include "NthBaseNumber.h"
#include <memory>

int main() {
    auto coder = std::make_shared<UBaseCoder>(UBaseCoder(10));
    auto item1 = NthBaseNumber(13, coder);
    auto item2 = NthBaseNumber(10, coder);

    auto foo = item1 + item2;

    std::cout << foo;
    return 0;
}