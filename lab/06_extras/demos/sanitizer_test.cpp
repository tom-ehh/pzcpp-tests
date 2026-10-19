// This test passes in a normal build, although the code has a memory bug.
// Build with -DENABLE_SANITIZERS=ON to see AddressSanitizer catch it.
#include <vector>

#include <gtest/gtest.h>

std::vector<int> squares(int count) {
    std::vector<int> result(count);
    int* data = result.data();
    for (int i = 0; i <= count; ++i) {  // bug: <= writes one element past the end
        data[i] = i * i;
    }
    return result;
}

TEST(SanitizerDemo, ComputesSquares) {
    const std::vector<int> expected{0, 1, 4, 9};
    EXPECT_EQ(squares(4), expected);
}
