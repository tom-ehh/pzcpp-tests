#pragma once

#include <optional>

// Access to an external weather service (e.g. over HTTP).
class IWeatherApi {
public:
    virtual ~IWeatherApi() = default;

    // Current temperature in a city, in whole degrees Celsius,
    // or std::nullopt when the request fails.
    virtual std::optional<int> fetchTemperature(int cityId) = 0;
};
