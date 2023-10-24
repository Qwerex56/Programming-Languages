#include <iostream>
#include <memory>
#include "./headers/DecimalCoder.h"
#include "./headers/NthBaseNumber.h"

int main() {
    const auto decCoder = std::make_shared<DecimalCoder<10>>();

    auto item1 = NthBaseNumber(61203756, decCoder);
    auto item2 = NthBaseNumber(91824234, decCoder);

    std::cout << item1 << " < " << item2 << std::endl;
    std::cout << (item1 < item2) << std::endl << std::endl;

    std::cout << item1 << " > " << item2 << std::endl;
    std::cout << (item1 > item2) << std::endl << std::endl;

    std::cout << item1 << " <= " << item2 << std::endl;
    std::cout << (item1 <= item2) << std::endl << std::endl;

    std::cout << item1 << " >= " << item2 << std::endl;
    std::cout << (item1 >= item2) << std::endl << std::endl;

    auto item3 = (item1 * item2);
    std::cout << item3;

    return 0;
}