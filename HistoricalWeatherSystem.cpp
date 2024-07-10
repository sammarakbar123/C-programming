#include<iostream>
#include <curl/curl.h>
#include <curl.h>
#include <json.hpp>
#include <iomanip> 
#include <ctime> 
using namespace std;
class HistoricalWeatherSystem {
private:
    std::string apiKey;
    std::string baseUrl;
public:
    HistoricalWeatherSystem(std::string apiKey, std::string baseUrl);
    std::string fetchHistoricalWeatherData(Location location, std::string date);
    void displayHistoricalWeatherData(std::string data);
};
HistoricalWeatherSystem::HistoricalWeatherSystem(std::string apiKey, std::string baseUrl) {
    this->apiKey = apiKey;
    this->baseUrl = baseUrl;
}

std::string HistoricalWeatherSystem::fetchHistoricalWeatherData(Location location, std::string date) {
    // implement fetching historical weather data from API
}

void HistoricalWeatherSystem::displayHistoricalWeatherData(std::string data) {
    // implement displaying historical weather data
}
std::string HistoricalWeatherSystem::fetchHistoricalWeatherData(Location location, std::string date) {
    std::string url = "(link unavailable)" + location.getLatitude() + "," + location.getLongitude() + "&date=" + date;
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

void HistoricalWeatherSystem::handleAPIResponse(std::string response) {
    // Parse the API response and extract the relevant data
    // ...

    // Store the data in a local data structure
    // ...
}

void HistoricalWeatherSystem::handleAPIError(std::string error) {
    // Handle the API error gracefully
    // ...
}


