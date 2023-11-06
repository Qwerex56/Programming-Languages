//
// Created by adrianczubaty on 06/11/23.
//

#include "gtest/gtest.h"
#include "UBaseCoder.h"

TEST(UBaseCoderTest, TwoComplementTest) {
    auto uTwoNumber = UBaseCoder<2>();
    auto testDataPositive = 2ll;
    auto testDataNegative = -2ll;
    auto testDataCoded = CodedNumber({0, 1, 0});

    EXPECT_EQ(uTwoNumber(testDataPositive), CodedNumber({0, 1, 0}));
    EXPECT_EQ(uTwoNumber(testDataNegative), CodedNumber({0, 1, 1}));
    EXPECT_EQ(uTwoNumber(testDataCoded), 2);
    EXPECT_EQ(uTwoNumber.getBase(), 2);
}