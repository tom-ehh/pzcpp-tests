// Death tests: checking that the program stops when it must.
#include <cstdlib>
#include <iostream>

#include <gtest/gtest.h>

int safeDivide(int dividend, int divisor) {
    if (divisor == 0) {
        std::cerr << "fatal: division by zero\n";
        std::abort();
    }
    return dividend / divisor;
}

TEST(SafeDivideDeathTest, AbortsOnDivisionByZero) {
    EXPECT_DEATH(safeDivide(1, 0), "division by zero");
}

TEST(SafeDivideTest, DividesNormally) {
    EXPECT_EQ(safeDivide(7, 2), 3);
}
