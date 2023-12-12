//
// Created by adrianczubaty on 12/12/23.
//

#ifndef LIST_1_NTHBASEEXCEPTIONS_H
#define LIST_1_NTHBASEEXCEPTIONS_H

#include <stdexcept>

namespace nthBase {
    class bad_base_error : public std::exception {
    public:
        explicit bad_base_error() _GLIBCXX_TXN_SAFE { }
#if __cplusplus >= 201103L
        bad_base_error(const bad_base_error&) = default;
        bad_base_error& operator=(const bad_base_error&) = default;
        bad_base_error(bad_base_error&&) = default;
        bad_base_error& operator=(bad_base_error&&) = default;
#endif
        ~bad_base_error() _GLIBCXX_NOTHROW override = default;
        [[nodiscard]]
        const char * what() const noexcept override {
            return "Bad base error, use base greater than or equal to 2";
        }
    };

    class different_base_error : public std::exception {
    public:
        explicit different_base_error() _GLIBCXX_TXN_SAFE { }
#if __cplusplus >= 201103L
        different_base_error(const different_base_error&) = default;
        different_base_error& operator=(const different_base_error&) = default;
        different_base_error(different_base_error&&) = default;
        different_base_error& operator=(different_base_error&&) = default;
#endif
        ~different_base_error() _GLIBCXX_NOTHROW override = default;
        [[nodiscard]]
        const char * what() const noexcept override {
        return "Different base error, bases are different, use numbers with equal bases or change base in one of the numbers";
        }
    };

    class divide_by_zero : public std::exception {
    public:
        explicit divide_by_zero() _GLIBCXX_TXN_SAFE { }

#if __cplusplus >= 201103L
        divide_by_zero(const divide_by_zero&) = default;
        divide_by_zero& operator=(const divide_by_zero&) = default;
        divide_by_zero(divide_by_zero&&) = default;
        divide_by_zero& operator=(divide_by_zero&&) = default;
#endif
        ~divide_by_zero() _GLIBCXX_NOTHROW override = default;
        [[nodiscard]]
        const char * what() const noexcept override {
            return "Cannot divide by 0";
        }
    };
}

#endif //LIST_1_NTHBASEEXCEPTIONS_H
