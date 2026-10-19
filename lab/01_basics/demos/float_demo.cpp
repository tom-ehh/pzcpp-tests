// Demo for notebook 01: comparing floating-point numbers.
// One of these tests fails on purpose - read its output.
#include <gtest/gtest.h>

TEST(FloatDemo, ExactComparison) {
    EXPECT_EQ(0.1 * 3, 0.3);
}

TEST(FloatDemo, UlpComparison) {
    EXPECT_DOUBLE_EQ(0.1 * 3, 0.3);
}

TEST(FloatDemo, AbsoluteTolerance) {
    EXPECT_NEAR(0.1 * 3, 0.3, 1e-9);
}
