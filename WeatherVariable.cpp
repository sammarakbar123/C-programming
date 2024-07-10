#include<iostream>
#include <curl/curl.h>
#include <curl.h>
#include <json.hpp>
#include <iomanip> 
#include <ctime> 
using namespace std;
class WeatherVariable {
private:
    std::string name;
    std::string unit;
public:
    WeatherVariable(std::string name, std::string unit);
    std::string getName();
    std::string getUnit();
    void defineVariable(std::string name, std::string unit);
};
WeatherVariable::WeatherVariable(std::string name, std::string unit) {
    this->name = name;
    this->unit = unit;
}

std::string WeatherVariable::getName() {
    return name;
}

std::string WeatherVariable::getUnit() {
    return unit;
}

void WeatherVariable::defineVariable(std::string name, std::string unit) {
    // implement defining a weather variable
}
