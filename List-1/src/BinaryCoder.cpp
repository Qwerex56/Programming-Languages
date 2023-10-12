//
// Created by adrianczubaty on 08.10.23.
//

#include "../headers/BinaryCoder.h"
#include <iostream>

//template <int maxBase>
class BinaryCoder{
public:
    explicit BinaryCoder(uint8_t base) : _base(base) {
        _halfCarry = ceil((16 - _base) / 2.0);
        _safeNum = ceil(_base / 2.0);

        if (_base % 2 == 1) {
            _halfCarry = (17 - _base) / 2;
        }
    }

    auto operator()(int numToCode) const {
        auto bc = std::vector<HALF_BYTE>(1);
        for (int i = 0; i < INT_SIZE_BITS; i++) {
            auto nthBit = numToCode >> (INT_SIZE_BITS - i - 1);
            numToCode = numToCode & ~(1 << (INT_SIZE_BITS - i - 1));

            // Check if all sections are lower than half base
            for (auto & j : bc) {
                auto section = j.to_ulong();

                if (section < _safeNum) {
                    continue;
                }

                j = section + _halfCarry;
            }

            // If biggest part is about to overflow add next part
            if (bc[0].to_ulong() > _safeNum) {
                auto it = bc.begin();
                bc.insert(it, std::bitset<4>(0));
            }

            // Shift next bit from number to code
            auto binCarry = 0u;
            for (int j = (int)bc.size() - 1; j >= 0; j--) {
                auto binCarryCache = bc[j] >> 3;
                bc[j] <<= 1;
                if (j == bc.size() - 1) {
                    bc[j].set(0, nthBit);
                }
                else {
                    bc[j].set(0, binCarry);
                }
                binCarry = binCarryCache.to_ulong();
            }
        }
        return bc;
    }

private:
    uint8_t _base;
    uint8_t _halfCarry;
    uint8_t _safeNum;
};
