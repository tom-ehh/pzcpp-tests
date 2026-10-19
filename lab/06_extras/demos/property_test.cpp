// Property-based testing with RapidCheck: random inputs + shrinking.
#include <algorithm>
#include <vector>

#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

// Buggy on purpose: starts from 0 instead of the first element.
int maxElement(const std::vector<int>& values) {
    int result = 0;
    for (int value : values) {
        result = std::max(result, value);
    }
    return result;
}

RC_GTEST_PROP(MaxElementTest, ResultIsOneOfTheValues, (const std::vector<int>& values)) {
    RC_PRE(!values.empty());
    const int result = maxElement(values);
    RC_ASSERT(std::find(values.begin(), values.end(), result) != values.end());
}

RC_GTEST_PROP(MaxElementTest, ResultIsNotSmallerThanAnyValue, (const std::vector<int>& values)) {
    const int result = maxElement(values);
    for (int value : values) {
        RC_ASSERT(result >= value);
    }
}
