// Compile-time tests: if any static_assert fails, this file does not compile.
constexpr int digitSum(int number) {
    int sum = 0;
    while (number > 0) {
        sum += number % 10;
        number /= 10;
    }
    return sum;
}

static_assert(digitSum(0) == 0);
static_assert(digitSum(7) == 7);
static_assert(digitSum(1234) == 10);
