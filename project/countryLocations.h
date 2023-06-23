/**
 * @file countryLocations.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief Provides the countryLocationsArray type.
 * 
 * This is a struct that represents an array and permits to
 * store elements of countryLocation type.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#define ARRAY_OK 0
#define ARRAY_NULL 1
#define ARRAY_NO_MEMORY 3


/**
 * @brief Data struct that reprsents information about countries and depedent territories 
 * that are associated with other countries
 * 
 */
typedef struct countryLocation
{
    char code[3]; // Igual a countryStatistics se país mas diferente se for dependente
    float latitude;
    float longitude;
    char territoryName[45];   // Nome do território
    char countryName[45];     // Nome do país associado se território dependente, se não N.A.
    char territoryRegion[30]; // Nome da região se for território dependente, se não N.A
                              // Existem duas novas regiões INDIAN OCEAN e SOUTH ATLANTIC
} CountryLocation;

/**
 * @brief Data struct that reprsents an array of earthquakes
 * 
 */
typedef struct countryLocationsArray{
    CountryLocation *locations;
    int size;
} *CountryLocationsArray;

/**
 * @brief Creates an array of country locations
 * 
 * @return CountryLocationsArray [out]
 */
CountryLocationsArray createCountryLocationsArray();

/**
 * @brief Releases all elements from countryLocationsArray and destroys it
 * 
 * @param array [in] of countryLocationsArray type
 * @return ARRAY_OK if 'array' if successful
 * @return ARRAY_NULL if 'array' is NULL
 */
int destroyCountryLocationsArray(CountryLocationsArray *array);

/**
 * @brief Ensures that countryLocationArray have capacity to add new elements
 * 
 * @param array [in] of countryLocationsArray type
 * @return ARRAY_OK if 'array' if successful
 * @return ARRAY_NULL if 'array' is NULL
 */
int ensureCapacityOfCountryLocationsArray(CountryLocationsArray array);

/**
 * @brief 
 * 
 * @param array [in] of countryLocationsArray type
 * @param location [in] of CountryLocation type
 * @return ARRAY_OK if 'array' if successful
 * @return ARRAY_NULL if 'array' is NULL
 */
int countryLocationsArrayAdd(CountryLocationsArray array, CountryLocation location);
/**
 * @brief 
 * 
 * @param array [in] of countryLocationsArray type
 * @return ARRAY_OK if 'array' if successful
 * @return ARRAY_NULL if 'array' is NULL
 */
int loadCountryLocations(CountryLocationsArray array);

/**
 * @brief 
 * 
 * @param array [in] of countryLocationsArray type
 * @param ptSize [in] pointer to variable
 * @return ARRAY_OK if 'array' if successful
 * @return ARRAY_NULL if 'array' is NULL
 */
int countryLocationsArraySize(CountryLocationsArray array, int *ptSize);

/**
 * @brief 
 * 
 * @param array [in] of countryLocationsArray type
 */
void showCountryLocations(CountryLocationsArray array);

/**
 * @brief 
 * 
 * @param array [in] of countryLocationsArray type
 * @return ARRAY_OK if 'array' if successful
 * @return ARRAY_NULL if 'array' is NULL
 */
int clearCountryLocationsArray(CountryLocationsArray array, int* discardedRecords);
