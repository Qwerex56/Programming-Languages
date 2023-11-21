//
// Created by adrianczubaty on 06/11/23.
//

#include "gtest/gtest.h"
#include "NthBaseNumber.h"

TEST(NthBaseNumberTest, BINARY_DIG) {
    auto testData1 = NthBaseNumber(123, std::make_shared<UBaseCoder>(2));
    auto testData2 = NthBaseNumber(-15, std::make_shared<UBaseCoder>(2));

    EXPECT_EQ(testData1.getBase(), 2);

    EXPECT_FALSE(testData1.isNegative());
    EXPECT_TRUE(testData2.isNegative());

    EXPECT_FALSE(testData1 == testData2);
    EXPECT_TRUE(testData1 != testData2);
    EXPECT_FALSE(testData1 < testData2);
    EXPECT_TRUE(testData1 > testData2);
    EXPECT_FALSE(testData1 < testData2);
    EXPECT_TRUE(testData1 > testData2);
}

TEST(NthBaseNumberTest, OCT_DIG) {

}

TEST(NthBaseNumberTest, DECIMAL_DIG) {

}