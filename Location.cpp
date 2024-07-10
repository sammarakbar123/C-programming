#include <iostream>
#include <vector>
#include <map>
class Location {
private:
    string name;
    double latitude;
    double longitude;
public:
    Location(string name, double latitude, double longitude);
    string getName();
    double getLatitude();
    double getLongitude();
    void addLocation(string name, double latitude, double longitude);
    void removeLocation(string name);
    vector<Location> listLocations();
};
Location(string name, double latitude, double longitude) {
    this->name = name;
    this->latitude = latitude;
    this->longitude = longitude;
}


string Location::getName()
{
    return string();
}

double Location::getLatitude()
{
    return 0.0;
}

double Location::getLongitude()
{
    return 0.0;
}

void Location::addLocation(string name, double latitude, double longitude)
{
}

void Location::removeLocation(string name)
{
}

vector<Location> Location::listLocations()
{
    return vector<Location>();
}

string getName() {
    return name;
}

double getLatitude() {
    return latitude;
}

double getLongitude() {
    return longitude;
}

void addLocation(string name, double latitude, double longitude) {
    // implement adding location to a data structure (e.g. vector)
}

void removeLocation(string name) {
    // implement removing location from data structure
}

vector<Location>listLocations() {
    // implement listing all locations in data structure
}

