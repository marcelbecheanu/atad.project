/**
 * @file earthquakeUtils.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief  Provides associated operations to earthquakes.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "list.h"
#include "countryLocations.h"


typedef struct earthquakeData {
    char code[3];
    char territoryName[45];
    int numberOfEarthquakes;
    float averageDepth;
    float averageMagnitude;
} EarthquakeData;

/**
 * @brief Loads all earthquakes from .csv
 * 
 * @param array [in] Array list of Country Locations
 * 
 * @return PtList 
 */
PtList loadEarthquakes(CountryLocationsArray *array);

/**
 * @brief Caltulates the euclidian distance between two points
 * 
 * @param x1 [in] earthquake latitude
 * @param y1 [in] earthquake latitude
 * @param x2 [in] country location latitude
 * @param y2 [in] country location longitude
 * @return distance [out] calculated
 */
float euclideanDistance(float x1, float y1, float x2, float y2);

/**
 * @brief 
 * 
 * @param earthquakeLatitude [in] latitude of earthquake
 * @param earthquakeLongitude [in] longitude of earthquake
 * @param locations [in] array
 * @param numLocations [in] size of array
 * @return char* [out] code of nearest country
 */
char* findNearestCountry(float earthquakeLatitude, float earthquakeLongitude, CountryLocation* locations, int numLocations);

/**
 * @brief 
 * 
 * @param list [in]
 * @param locations [in] 
 */
void displayCountriesWithEarthquake(PtList list, CountryLocationsArray locations);

/**
 * @brief Prints all earthquake elements of a list
 * 
 * @param list [in] list to print
 */
 void printEarthquakes(PtList list);

/**
 * @brief 
 * 
 * @param earthquakes 
 * @return PtList 
 */
PtList filterEarthquakesByYear(PtList earthquakes);

/**
 * @brief 
 * 
 * @param e1 
 * @param e2 
 * @return int 
 */
int compareEarthquakeYears(Earthquake* e1, Earthquake* e2);

/**
 * @brief Compares the country codes between two earthquakes
 * 
 * @param e1 [in] first earthquake element
 * @param e2 [in] fist earthquake element
 * @return int [out] result of srtcmp
 */
int compareEarthquakeCountryCodes(Earthquake* e1, Earthquake* e2);

/**
 * @brief 
 * 
 * @param earthquakes 
 */
void sortEarthquakesByCountryCode(PtList earthquakes);

/**
 * @brief 
 * 
 * @param earthquakes 
 * @return PtList 
 */
PtList filterEarthquakesByYear(PtList earthquakes);

/**
 * @brief 
 * 
 */
void showEarthquakesbyYear(PtList earthquakes);

/**
 * @brief Filters earthquakes by country code
 *
 * @param earthquakes [in] earthquakes list
 * @return Lista de earthquake filtrada pelo código do país.
 */
PtList filterEarthquakesByCountry(PtList earthquakes);

/**
 * @brief Shows the earthquakes filtered by country/code
 *
 * @param earthquakes [in] earthquakes list
 */
void showEarthquakesByCountry(PtList earthquakes);

/**
 * @brief 
 * 
 * @param earthquakes 
 * @return PtList 
 */
PtList filterEarthquakesByCountryYear(PtList earthquakes);

/**
 * @brief Shows the earthquakes filtered by country/code
 *
 * @param earthquakes [in] earthquakes list
 */
void showEarthquakesByCountryYear(PtList earthquakes);

/**
 * @brief 
 * 
 * @param list 
 */
void countEarthquake(PtList list);

/**
 * @brief 
 * 
 * @param locations 
 * @param earthquakes 
 */
void showTopEarthquakeData(CountryLocationsArray locations, PtList earthquakes);

/**
 * @brief 
 * 
 * @param earthquakeData 
 * @param earthquakes 
 * @param sizeOfCountries 
 */
void fillListWithEarthquakeByCountries(EarthquakeData* earthquakeData, PtList earthquakes, int sizeOfCountries);

/**
 * @brief 
 * 
 * @param earthquakeData 
 * @param size 
 */
void sortEarthquakeDataByNumberOfEarthquakes(EarthquakeData* earthquakeData, int size);

/**
 * @brief 
 * 
 * @param earthquakeData 
 * @param size 
 */
void printListWithEarthquakes(EarthquakeData* earthquakeData, int size);