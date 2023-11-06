//
// Created by adrianczubaty on 06/11/23.
//

#include "gtest/gtest.h"

bool isTrue(bool w) {
    return w;
}

TEST(TrueTest, TrueFalse) {
    EXPECT_EQ(isTrue(true), false);
}
