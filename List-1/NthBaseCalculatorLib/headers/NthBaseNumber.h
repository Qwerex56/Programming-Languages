//
// Created by adrianczubaty on 09.10.23.
//

#ifndef LIST_1_NTHBASENUMBER_H
#define LIST_1_NTHBASENUMBER_H

#define NATURAL_SYSTEM 10

#include "NumberCoder.h"
#include "UBaseCoder.h"
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <numeric>

namespace nthBase {
    class NthBaseNumber {
    public:
        explicit NthBaseNumber(int64_t init = 0, const std::shared_ptr<NumberCoder> &nc = nullptr);

        [[maybe_unused]]
        explicit NthBaseNumber(CodedNumber &init, const std::shared_ptr<NumberCoder> &nc = nullptr, bool isReversed = false);

        explicit NthBaseNumber(CodedNumber &&init, const std::shared_ptr<NumberCoder> &nc = nullptr, bool isReversed = false);

        [[maybe_unused]]
        NthBaseNumber(const NthBaseNumber &other);

        [[maybe_unused]]
        NthBaseNumber(const NthBaseNumber &&other) noexcept;

        NthBaseNumber& operator =(const NthBaseNumber &other);

        [[maybe_unused]]
        void ChangeBase(const std::shared_ptr<NumberCoder> &newNc);

        [[nodiscard]]
        inline int getBase() const noexcept {
            return this->_numberCoder->getBase();
        }

        [[nodiscard]]
        [[maybe_unused]]
        inline size_t getSize() const noexcept {
            return std::size(this->_number);
        }

        [[nodiscard]]
        [[maybe_unused]]
        inline CodedNumber& getNumber() noexcept {
            return this->_number;
        }

        [[nodiscard]]
        [[maybe_unused]]
        inline CodedNumber getNumberConst() const {
            return this->_number;
        }

        NthBaseNumber& operator +=(const NthBaseNumber &rhs);
        NthBaseNumber& operator -=(const NthBaseNumber &rhs);
        NthBaseNumber& operator *=(const NthBaseNumber &rhs);
        NthBaseNumber& operator /=(const NthBaseNumber &rhs);
        NthBaseNumber& operator %=(const NthBaseNumber &rhs);

        NthBaseNumber& operator ++();
        const NthBaseNumber operator ++(int);

        NthBaseNumber& operator --();
        const NthBaseNumber operator --(int);

        bool operator ==(const NthBaseNumber &rhs) const;
        bool operator !=(const NthBaseNumber &rhs) const;
        bool operator <(const NthBaseNumber &rhs) const;
        bool operator >(const NthBaseNumber &rhs) const;
        bool operator <=(const NthBaseNumber &rhs) const;
        bool operator >=(const NthBaseNumber &rhs) const;

        friend std::ostream& operator <<(std::ostream &os, NthBaseNumber &number) {
            const auto TO_ASCII = 55;
            auto vec = number.getNumber();

            std::for_each(vec.crbegin(), vec.crend(), [&](const auto &item) {
                if (item > 9) std::cout << static_cast<char>(item + TO_ASCII);
                else std::cout << static_cast<int>(item);
            });

            return os;
        }

        friend NthBaseNumber operator +(NthBaseNumber lhs, const NthBaseNumber &rhs) {
            lhs += rhs;
            return lhs;
        }

        friend NthBaseNumber operator -(NthBaseNumber lhs, const NthBaseNumber &rhs) {
            lhs -= rhs;
            return lhs;
        }

        friend NthBaseNumber operator *(NthBaseNumber lhs, const NthBaseNumber &rhs) {
            lhs *= rhs;
            return lhs;
        }

        friend NthBaseNumber operator /(NthBaseNumber lhs, const NthBaseNumber &rhs) {
            lhs /= rhs;
            return lhs;
        }

        friend NthBaseNumber operator %(NthBaseNumber lhs, const NthBaseNumber &rhs) {
            lhs %= rhs;
            return lhs;
        }

        [[maybe_unused]]
        [[maybe_unused]]
        static std::tuple<NthBaseNumber, NthBaseNumber> slowDivision(NthBaseNumber &lhs, NthBaseNumber &rhs);
    private:
        std::shared_ptr<NumberCoder> _numberCoder;
        CodedNumber _number;

        [[maybe_unused]]
        static void pushCarryOver(NthBaseNumber &where, int carry = 0);
    };
}

#endif //LIST_1_NTHBASENUMBER_H
