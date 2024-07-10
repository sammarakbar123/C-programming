#include<iostream>
#include <curl/curl.h>
#include <curl.h>
#include <json.hpp>
#include <iomanip> 
#include <ctime>   
using namespace std;
class AirQualityForecastingSystem {
private:
    std::string apiKey;
    std::string baseUrl;
public:
    AirQualityForecastingSystem(std::string apiKey, std::string baseUrl);
    std::string fetchAirQualityData(Location location);
    void displayAirQualityData(std::string data);
};
AirQualityForecastingSystem::AirQualityForecastingSystem(std::string apiKey, std::string baseUrl) {
    this->apiKey = apiKey;
    this->baseUrl = baseUrl;
}

std::string AirQualityForecastingSystem::fetchAirQualityData(Location location) {
    // implement fetching air quality data from API
}

void AirQualityForecastingSystem::displayAirQualityData(std::string data) {
    // implement displaying air quality data
}
std::string AirQualityForecastingSystem::fetchAirQualityData(Location location) {
    std::string url = "(link unavailable)" + location.getLatitude() + "," + location.getLongitude();
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "cURL error: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
    }

    return readBuffer;
}
void AirQualityForecastingSystem::handleAPIResponse(std::string response) {
    // Parse the API response and extract the relevant data
    // ...

    // Store the data in a local data structure
    // ...
}

void AirQualityForecastingSystem::handleAPIError(std::string error) {
    // Handle the API error gracefully
    // ...
}

