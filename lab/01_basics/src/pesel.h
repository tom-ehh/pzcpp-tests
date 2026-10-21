#pragma once

#include <compare>
#include <ostream>
#include <string>

struct Date {
    int year;
    int month;
    int day;

    auto operator<=>(const Date&) const = default;
};

// Prints a date as YYYY-MM-DD (also used by GoogleTest in failure messages).
std::ostream& operator<<(std::ostream& os, const Date& date);

// Returns true if `pesel` is a valid PESEL number:
//   - exactly 11 digits,
//   - a correct check digit (weights 1-3-7-9-1-3-7-9-1-3),
//   - a real birth date; the century is encoded in the month:
//     01-12 -> 1900s, 21-32 -> 2000s, 41-52 -> 2100s, 61-72 -> 2200s, 81-92 -> 1800s.
bool isValidPesel(const std::string& pesel);

// Returns the birth date encoded in a valid PESEL.
// Throws std::invalid_argument if `pesel` is not valid.
Date birthDateFromPesel(const std::string& pesel);
