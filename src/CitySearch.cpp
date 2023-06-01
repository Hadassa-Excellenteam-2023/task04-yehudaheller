#include "CitySearch.h"

void CitySearch::loadDataFromFile(const std::string& filePath) {
    std::ifstream fin(filePath);
    std::string line, name;
    double first, second;

    while (std::getline(fin, line)) {
        if (line.length() > 0) {
            name = line;
            std::getline(fin, line);
            int pos = line.find("-");
            first = std::stod(line.substr(0, pos));
            second = std::stod(line.substr(pos + 1));

            cities[name] = City(name, first, second);
        }
    }
    fin.close();
}

double CitySearch::calculateDistance(const City& city1, const City& city2, int norm) {
    double distance;

    if (norm == 0) {
        distance = std::sqrt(std::pow(city1.y - city2.y, 2) + std::pow(city1.x - city2.x, 2));
    }
    else if (norm == 1) {
        distance = std::max(std::abs(city1.y - city2.y), std::abs(city1.x - city2.x));
    }
    else if (norm == 2) {
        distance = std::abs(city1.y - city2.y) + std::abs(city1.x - city2.x);
    }
    else {
        distance = 0.0; // Invalid norm, distance is zero
    }

    return distance;
}

void CitySearch::runCitySearch() {
    std::cout << "Please enter the selected city name (with line break after it):" << std::endl;
    std::string selectedCity;

    while (std::getline(std::cin, selectedCity) && selectedCity != "0") {
        // Remove the line break from the selected city
        selectedCity.erase(selectedCity.find_last_not_of("\n") + 1);

        // Find the selected city in the map
        auto selected = cities.find(selectedCity);

        if (selected == cities.end()) {
            std::cerr << "ERROR: \"" << selectedCity << "\" is not found in the city list. Please try again." << std::endl;
            continue;
        }

        std::cout << "Please enter the desired radius:" << std::endl;
        double radius;
        std::cin >> radius;

        std::cout << "Please enter the desired norm (0 – L2, Euclidean distance, 1 – Linf, Chebyshev distance, 2 – L1, Manhattan distance):" << std::endl;
        int norm;
        std::cin >> norm;

        // Clear the input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Calculate the rectangular boundaries
        double minX = selected->second.x - radius;
        double maxX = selected->second.x + radius;
        double minY = selected->second.y - radius;
        double maxY = selected->second.y + radius;

        // Filter cities within the rectangular region
        std::vector<City> filteredCities;
        std::vector<std::pair<const std::string, City>> tempCities;

        std::copy_if(
            cities.begin(), cities.end(),
            std::back_inserter(tempCities),
            [&](const std::pair<const std::string, City>& cityPair) {
                const City& city = cityPair.second;
                return city.x >= minX && city.x <= maxX && city.y >= minY && city.y <= maxY;
            }
        );

        // Copy filtered cities from tempCities to filteredCities
        filteredCities.reserve(tempCities.size());
        std::transform(
            tempCities.begin(), tempCities.end(),
            std::back_inserter(filteredCities),
            [](const std::pair<const std::string, City>& cityPair) {
                return cityPair.second;
            }
        );



        // Sort cities based on their distance to the selected city
        std::sort(filteredCities.begin(), filteredCities.end(), [&](const City& city1, const City& city2) {
            return calculateDistance(selected->second, city1, norm) < calculateDistance(selected->second, city2, norm);
            });

        // Print the result
        std::cout << filteredCities.size() << " city/cities found in the given radius." << std::endl;

        int countNorth = std::count_if(filteredCities.begin(), filteredCities.end(), [&](const City& city) {
            return city.y < selected->second.y;
            });

        std::cout << countNorth << " cities are to the north of the selected city." << std::endl;

        std::cout << "City list:" << std::endl;
        std::for_each(filteredCities.begin(), filteredCities.end(), [](const City& city) {
            std::cout << city.name << std::endl;
            });

        std::cout << "Please enter the selected city name (with line break after it):" << std::endl;
    }

    std::cout << "Bye" << std::endl;
}
