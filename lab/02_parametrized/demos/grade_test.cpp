// Demo for notebook 02: the grade table from notebook 01 as parameterized tests.
#include <ostream>
#include <stdexcept>
#include <string>

#include <gtest/gtest.h>

int grade(int points) {
    if (points < 0 || points > 100) {
        throw std::out_of_range("points must be in [0, 100]");
    }
    if (points < 50) return 2;
    if (points < 70) return 3;
    if (points < 90) return 4;
    return 5;
}

struct GradeCase {
    int points;
    int expected;
};

// Lets GoogleTest print a GradeCase in failure messages.
void PrintTo(const GradeCase& c, std::ostream* os) {
    *os << "{points: " << c.points << ", expected: " << c.expected << "}";
}

class GradeTest : public ::testing::TestWithParam<GradeCase> {};

TEST_P(GradeTest, MapsPointsToGrade) {
    const GradeCase& c = GetParam();
    EXPECT_EQ(grade(c.points), c.expected);
}

INSTANTIATE_TEST_SUITE_P(
    Boundaries, GradeTest,
    ::testing::Values(GradeCase{0, 2}, GradeCase{49, 2},
                      GradeCase{50, 3}, GradeCase{69, 3},
                      GradeCase{70, 4}, GradeCase{89, 4},
                      GradeCase{90, 5}, GradeCase{100, 5}),
    [](const ::testing::TestParamInfo<GradeCase>& info) {
        return "Points" + std::to_string(info.param.points);
    });

class InvalidPointsTest : public ::testing::TestWithParam<int> {};

TEST_P(InvalidPointsTest, Throws) {
    EXPECT_THROW(grade(GetParam()), std::out_of_range);
}

INSTANTIATE_TEST_SUITE_P(OutOfRange, InvalidPointsTest,
                         ::testing::Values(-1, 101, -1000, 1000));
