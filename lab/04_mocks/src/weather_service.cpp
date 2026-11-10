#include "weather_service.h"

std::ostream& operator<<(std::ostream& os, FrostStatus status) {
    switch (status) {
        case FrostStatus::Frost:
            return os << "Frost";
        case FrostStatus::NoFrost:
            return os << "NoFrost";
        case FrostStatus::Unknown:
            return os << "Unknown";
    }
    return os << "FrostStatus(" << static_cast<int>(status) << ")";
}

WeatherService::WeatherService(IWeatherApi& api) : api_(api) {}

FrostStatus WeatherService::frostStatus(int cityId) {
    auto cached = temperatureByCity_.find(cityId);
    if (cached == temperatureByCity_.end()) {
        const std::optional<int> temperature = api_.fetchTemperature(cityId);
        if (!temperature) {
            return FrostStatus::Unknown;
        }
        cached = temperatureByCity_.emplace(cityId, *temperature).first;
    }
    return cached->second <= 0 ? FrostStatus::Frost : FrostStatus::NoFrost;
}
