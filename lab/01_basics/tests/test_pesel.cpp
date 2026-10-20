// Exercise 1: write your first tests.
// Replace each FAIL() with real assertions (see the notebook for details).
#include "pesel.h"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(PeselTest, AcceptsValidPesel) {
    FAIL() << "TODO: check that isValidPesel() returns true for a valid PESEL";
}

TEST(PeselTest, RejectsWrongCheckDigit) {
    FAIL() << "TODO: check that isValidPesel() returns false when the check digit is wrong";
}

TEST(PeselTest, BirthDateOfInvalidPeselThrows) {
    FAIL() << "TODO: check that birthDateFromPesel() throws std::invalid_argument for an invalid PESEL";
}
