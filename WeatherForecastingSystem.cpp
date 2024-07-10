#include<iostream>
using namespace std;
class WeatherForecastingSystem {
private:
    std::string apiKey;
    std::string baseUrl;
public:
    WeatherForecastingSystem(std::string apiKey, std::string baseUrl);
    std::string fetchWeatherForecast(Location location, std::vector<WeatherVariable> variables);
    void displayWeatherForecast(std::string data);
};
WeatherForecastingSystem::WeatherForecastingSystem(std::string apiKey, std::string baseUrl) {
    this->apiKey = apiKey;
    this->baseUrl = baseUrl;
}

std::string WeatherForecastingSystem::fetchWeatherForecast(Location location, std::vector<WeatherVariable> variables) {
    // implement fetching weather forecast data from API
}

void WeatherForecastingSystem::displayWeatherForecast(std::string data) {
    // implement displaying weather forecast data
}
