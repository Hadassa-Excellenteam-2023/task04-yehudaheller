#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>

struct City {
    std::string name;
    double y;
    double x;

    City(const std::string& cityName, double yCoordinate, double xCoordinate)
        : name(cityName), y(yCoordinate), x(xCoordinate) {}
    City() : name(""), x(0.0), y(0.0) {}
};

class CitySearch {
private:
    std::map<std::string, City> cities;

public:
    void loadDataFromFile(const std::string& filePath);
    double calculateDistance(const City& city1, const City& city2, int norm);
    void runCitySearch();
};


