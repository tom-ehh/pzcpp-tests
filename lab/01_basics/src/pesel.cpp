#include "pesel.h"

#include <array>
#include <cctype>
#include <cstddef>
#include <iomanip>
#include <optional>
#include <stdexcept>

namespace {

constexpr std::array<int, 10> kWeights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3};

int digitAt(const std::string& pesel, std::size_t index) {
    return pesel[index] - '0';
}

int twoDigitsAt(const std::string& pesel, std::size_t index) {
    return digitAt(pesel, index) * 10 + digitAt(pesel, index + 1);
}

bool hasElevenDigits(const std::string& pesel) {
    if (pesel.size() != 11) {
        return false;
    }
    for (char c : pesel) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

bool hasValidCheckDigit(const std::string& pesel) {
    int sum = 0;
    for (std::size_t i = 0; i < kWeights.size(); ++i) {
        sum += digitAt(pesel, i) * kWeights[i];
    }
    return (10 - sum % 10) % 10 == digitAt(pesel, 10);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int daysInMonth(int year, int month) {
    constexpr std::array<int, 12> kDays{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return month == 2 && isLeapYear(year) ? 29 : kDays[month - 1];
}

// Decodes the birth date; std::nullopt if the month code or the day is invalid.
std::optional<Date> decodeDate(const std::string& pesel) {
    // The month code is the month plus 0, 20, 40, 60 or 80 depending on the century.
    constexpr std::array<int, 5> kCenturyByCode{1900, 2000, 2100, 2200, 1800};
    const int monthCode = twoDigitsAt(pesel, 2);
    const int month = monthCode % 20;
    if (month < 1 || month > 12) {
        return std::nullopt;
    }
    const int year = kCenturyByCode[monthCode / 20] + twoDigitsAt(pesel, 0);
    const int day = twoDigitsAt(pesel, 4);
    if (day < 1 || day > daysInMonth(year, month)) {
        return std::nullopt;
    }
    return Date{year, month, day};
}

}  // namespace

std::ostream& operator<<(std::ostream& os, const Date& date) {
    const char fill = os.fill('0');
    os << std::setw(4) << date.year << '-' << std::setw(2) << date.month << '-'
       << std::setw(2) << date.day;
    os.fill(fill);
    return os;
}

bool isValidPesel(const std::string& pesel) {
    return hasElevenDigits(pesel) && hasValidCheckDigit(pesel) && decodeDate(pesel).has_value();
}

Date birthDateFromPesel(const std::string& pesel) {
    if (!isValidPesel(pesel)) {
        throw std::invalid_argument("invalid PESEL: " + pesel);
    }
    return *decodeDate(pesel);
}
