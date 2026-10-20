#pragma once

#include <map>
#include <ostream>

#include "weather_api.h"

enum class FrostStatus { Frost, NoFrost, Unknown };

// Prints FrostStatus values (also used by GoogleTest in failure messages).
std::ostream& operator<<(std::ostream& os, FrostStatus status);

class WeatherService {
public:
    explicit WeatherService(IWeatherApi& api);

    // Frost when the temperature is 0 °C or lower, NoFrost when it is above 0 °C,
    // Unknown when the API request fails.
    // Successful readings are cached: the API is asked at most once per city.
    // Failures are not cached - the next call for that city asks the API again.
    FrostStatus frostStatus(int cityId);

private:
    IWeatherApi& api_;
    std::map<int, int> temperatureByCity_;
};
