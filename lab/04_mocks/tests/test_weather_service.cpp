// Exercise 4: test WeatherService with a mocked IWeatherApi.
// First write MockWeatherApi in mock_weather_api.h, then replace each FAIL().
#include "weather_service.h"

#include <optional>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "mock_weather_api.h"

TEST(WeatherServiceTest, ReportsFrostBelowZero) {
    FAIL() << "TODO: API returns -5 -> Frost";
}

TEST(WeatherServiceTest, ReportsNoFrostAboveZero) {
    FAIL() << "TODO: API returns 3 -> NoFrost";
}

TEST(WeatherServiceTest, ZeroDegreesIsFrost) {
    FAIL() << "TODO: API returns 0 -> Frost (boundary value)";
}

TEST(WeatherServiceTest, ReportsUnknownWhenApiFails) {
    FAIL() << "TODO: API returns std::nullopt -> Unknown";
}

TEST(WeatherServiceTest, AsksApiOnlyOncePerCity) {
    FAIL() << "TODO: two frostStatus(1) calls -> fetchTemperature(1) called exactly once";
}

TEST(WeatherServiceTest, AsksApiForEachCity) {
    FAIL() << "TODO: frostStatus(1) and frostStatus(2) -> fetchTemperature called once for each city";
}
