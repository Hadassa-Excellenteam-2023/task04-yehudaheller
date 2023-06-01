#include <iostream>
#include "CitySearch.h"

int main() {
    CitySearch citySearch;
    citySearch.loadDataFromFile("data.txt");
    citySearch.runCitySearch();

    return 0;
}
