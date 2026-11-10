// Exercise 2: all PESEL rules as one parameterized test.
#include "pesel.h"

#include <string>

#include <gtest/gtest.h>

struct PeselCase {
    std::string name;  // test name suffix: letters, digits and '_' only
    std::string pesel;
    bool valid;
};

class PeselValidationTest : public ::testing::TestWithParam<PeselCase> {};

TEST_P(PeselValidationTest, ValidatesPesel) {
    FAIL() << "TODO: compare isValidPesel(GetParam().pesel) with GetParam().valid";
}

INSTANTIATE_TEST_SUITE_P(
    Rules, PeselValidationTest,
    ::testing::Values(
        PeselCase{"TooShort", "0101011234", false}
        // TODO: add the remaining cases (see the table in the notebook)
        ),
    [](const ::testing::TestParamInfo<PeselCase>& info) { return info.param.name; });
