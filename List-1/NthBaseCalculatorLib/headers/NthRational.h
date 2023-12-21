//
// Created by adrianczubaty on 14.12.23.
//

#include <memory>
#include <numeric>

#include "NumberCoder.h"
#include "NthBaseExceptions.h"
#include "NthBaseNumber.h"

#ifndef LIST_1_NTHRATIONAL_H
#define LIST_1_NTHRATIONAL_H

namespace nthBase::rational {
    class NthRational {
    public:
        [[maybe_unused]]
        explicit NthRational() noexcept;

        [[maybe_unused]]
        explicit NthRational(const NthBaseNumber& numerator, const NthBaseNumber& denumerator);

        [[maybe_unused]]
        explicit NthRational(int64_t numerator, int64_t denumerator, uint8_t base);

        NthRational(const NthRational& rhs) noexcept;
        NthRational(const NthRational&& rhs) noexcept;
        NthRational& operator =(const NthRational& rhs) noexcept;
        NthRational& operator =(NthRational&& rhs) noexcept;

        NthRational& operator +=(const NthRational& rhs);
        NthRational& operator -=(const NthRational& rhs);
        NthRational& operator *=(const NthRational& rhs);
        NthRational& operator /=(const NthRational& rhs);

        friend NthRational operator +(NthRational lhs, const NthRational& rhs) {
            lhs += rhs;
            return lhs;
        }

        friend NthRational operator -(NthRational lhs, const NthRational& rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend NthRational operator *(NthRational lhs, const NthRational& rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend NthRational operator /(NthRational lhs, const NthRational& rhs) {
            lhs /= rhs;
            return lhs;
        }

        friend std::ostream& operator <<(std::ostream& os, const NthRational& rhs) {
            os << rhs._numerator << " | " << rhs._denumerator;
            return os;
        }

    private:
        NthBaseNumber _numerator;
        NthBaseNumber _denumerator;
        uint8_t _base;

        NthBaseNumber greatestCommonDivisor() noexcept;
        void shortRational() noexcept;
    };
}

#endif //LIST_1_NTHRATIONAL_H
