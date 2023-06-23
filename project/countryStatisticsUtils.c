
/**
 * @file countryLocations.c
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief Docente - Miguel Bugalho
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "input.h"
#include "map.h"
#include "countryStatisticsUtils.h"

PtMap loadCountryStatistics(){

    PtMap map = mapCreate();

    FILE *stream = fopen("dataset/world_country_statistics.csv", "r");
    if (stream == NULL){ 
        printf("Failed to open the country statistics file.\n");
        return map;
    }

     char line[1024];
     
    // Read and discard the header line
    fgets(line, 1024, stream);

    while (fgets(line, 1024, stream)){

        char* tmp = strdup(line);
        char** tokens = splitString(tmp, 9, ";");

        char* code = tokens[0];
        char* name = tokens[1];
        char* region = tokens[2];

        long population = -1;
        if(strcmp(tokens[3], "N.A.") != 0)
            population = atol(tokens[3]);

        long area = -1;
        if(strcmp(tokens[4], "N.A.") != 0)
            area = atol(tokens[4]);
             
        long gdp_capita = -1;
        if(strcmp(tokens[5], "N.A.") != 0)
             gdp_capita = atof(tokens[5]);

        float literacy = -1;
        if(strcmp(tokens[6], "N.A.") != 0)
             literacy = atof(tokens[6]);

        float birthdate = -1;
        if(strcmp(tokens[7], "N.A.") != 0)
             birthdate = atof(tokens[7]);

        float deathrate = -1;
        if(strcmp(tokens[8], "N.A.") != 0)
             deathrate = atof(tokens[8]);

        StringWrap keyVal = stringWrapCreate(tokens[1]);
        CountryStatistics statistics = statisticsCreate(code, name, region, population, area, gdp_capita, literacy, birthdate, deathrate);

        mapPut(map, keyVal, statistics);

        free(tokens);
        free(tmp);
    }

    fclose(stream);
    return map;
}

void showCountryStatisticsByOrder(PtMap map)
{

    int sizeOfMap;
    mapSize(map, &sizeOfMap);

    if (map == NULL){
        printf("First you need to load data from statistics.");
        return;
    }

    int criteria = 0; // 1: Literacy 2: GDP (per capita)
    while (true)
    {
        printf("What is the main criteria to sort:\n");
        printf("1: Literacy\n");
        printf("2: GDP (per capita)\n");
        printf("Option: ");
        readInteger(&criteria);
        if (criteria == 1 || criteria == 2)
            break;
        printf("Please choose a valid option.\n");
    }

    int sort = 0; // 1: Ascending 2: Descending
    while (true)
    {
        printf("What is direction of the sort:\n");
        printf("1: Ascending\n");
        printf("2: Descending\n");
        printf("Option: ");
        readInteger(&sort);
        if (sort == 1 || sort == 2)
            break;
        printf("Please choose a valid option.\n");
    }

    // Allocate memory to store the country statistics
    CountryStatistics *countries = (CountryStatistics *)malloc(sizeOfMap * sizeof(CountryStatistics));
    if (countries == NULL)
    {
        printf("Error: Failed to allocate memory.\n");
        return;
    }

    // Iterate over the map and retrieve the country statistics
    MapKey *keys = mapKeys(map);
    for (int i = 0; i < sizeOfMap; i++)
    {
        MapValue value;
        mapGet(map, keys[i], &value);
        countries[i] = value;
    }

    // Perform sorting of country statistics
    for (int i = 0; i < sizeOfMap; i++)
    {
        for (int j = 0; j < sizeOfMap - i - 1; j++)
        {
            
            if (criteria == 1) // Primary criterion: literacy percentage
            {
                if (sort == 1)
                {
                    // Ascending order by (literacy, GDP, code)
                    if (countries[j].literacy > countries[j + 1].literacy ||
                        (countries[j].literacy == countries[j + 1].literacy &&
                            countries[j].gdp_capita > countries[j + 1].gdp_capita) ||
                        (countries[j].literacy == countries[j + 1].literacy &&
                            countries[j].gdp_capita == countries[j + 1].gdp_capita &&
                            strcmp(countries[j].code, countries[j + 1].code) > 0))
                    {
                        swapCountries(countries, j);
                    }
                }
                else
                { 
                    // Descending order by (GDP, literacy, code)
                    if (countries[j].literacy < countries[j + 1].literacy ||
                        (countries[j].literacy == countries[j + 1].literacy &&
                            countries[j].gdp_capita < countries[j + 1].gdp_capita) ||
                        (countries[j].literacy == countries[j + 1].literacy &&
                            countries[j].gdp_capita == countries[j + 1].gdp_capita &&
                            strcmp(countries[j].code, countries[j + 1].code) < 0))
                    {
                        swapCountries(countries, j);
                    }
                }
            }
            else
            { 
                if (sort == 1)
                { 
                    // Ascending order by (GDP, literacy, code)
                    if (countries[j].gdp_capita > countries[j + 1].gdp_capita ||
                    (countries[j].gdp_capita == countries[j + 1].gdp_capita &&
                    countries[j].literacy > countries[j + 1].literacy) ||
                    (countries[j].gdp_capita == countries[j + 1].gdp_capita &&
                    countries[j].literacy == countries[j + 1].literacy &&
                    strcmp(countries[j].code, countries[j + 1].code) > 0))
                    {
                        swapCountries(countries, j);
                    }   
                }
                else
                { 
                    // Descending order by (GDP, literacy, code)
                    if (countries[j].gdp_capita < countries[j + 1].gdp_capita ||
                    (countries[j].gdp_capita == countries[j + 1].gdp_capita &&
                    countries[j].literacy < countries[j + 1].literacy) ||
                    (countries[j].gdp_capita == countries[j + 1].gdp_capita &&
                    countries[j].literacy == countries[j + 1].literacy &&
                    strcmp(countries[j].code, countries[j + 1].code) < 0))
                    {
                        swapCountries(countries, j);
                    }
                }
            }
        }
    }

    // Print Data

    printf("%-2s %-32s %-21s %-21s %-10s %-10s %-5s %-5s %-5s\n", "Cd", "Name", "Region", "Population", "Area", "GDP", "Lit", "Brate", "Drate");

    for (int i = 0; i < sizeOfMap; i++)
    {
        printf("%-2s ", countries[i].code);
        printf("%-32s ", countries[i].name);
        printf("%-21s ", countries[i].region);
        printf("%-21ld ", countries[i].population);
        printf("%-10ld ", countries[i].area);

        if(countries[i].gdp_capita == -1)
            printf("%-10s ", "-");
        else
            printf("%-10ld ", countries[i].gdp_capita);

        if(countries[i].literacy == -1)
            printf("%-5s ", "-");
        else
            printf("%-5.2f ", countries[i].literacy);

        if(countries[i].birthrate == -1)
            printf("%-5s ", "-");
        else
            printf("%-5.2f ", countries[i].birthrate);

        if( countries[i].deathrate == -1)
            printf("%-5s ", "-");
        else
            printf("%-5.2f ", countries[i].deathrate);

        printf("\n");
       
    }

    free(countries);
    free(keys);
}


// Simple function to swap to elements
void swapCountries(CountryStatistics *countries, int j)
{
    CountryStatistics temp = countries[j];
    countries[j] = countries[j + 1];
    countries[j + 1] = temp;
}

void calculateStatisticsForRegion(PtMap map, char* regionName) {
    // Initialize variables to store statistics
    int totalPopulation = 0;
    double totalArea = 0.0;
    double totalGDP = 0.0;
    double totalLiteracyWeighted = 0.0;
    int ignoredCountries = 0;
    int consideredCountries = 0;

    // Retrieve the keys from the map
    MapKey* keys = mapKeys(map);
    int sizeOfMap;
    mapSize(map, &sizeOfMap);

    // Iterate through the map entries
    for (int i = 0; i < sizeOfMap; i++) {
        MapKey key = keys[i];
        MapValue value;
        mapGet(map, key, &value);

        // Check if the country belongs to the specified region
        if (strcmp(value.region, regionName) == 0) {
            // Check if the country's data is available
            if (value.population != -1 && value.area != -1 && value.gdp_capita != -1 && value.literacy != -1) {
                totalPopulation += value.population;
                totalArea += value.area;
                totalGDP += value.gdp_capita * value.population;
                totalLiteracyWeighted += value.literacy * value.population;
                consideredCountries++;
            } else {
                ignoredCountries++;
            }
        }
    }

    // Calculate the derived statistics
    double populationDensity = totalPopulation / totalArea;
    double gdpPerCapita = totalGDP / totalPopulation;
    double averageLiteracy = totalLiteracyWeighted / totalPopulation;

    // Display the statistics
    if (consideredCountries == 0) {
        printf("\nNo data available for region: %s\n", regionName);
    } else {
        printf("\nAverages for region: %s\n", regionName);
        printf("%d countries considered for that region and %d ignored due to lack of data\n", consideredCountries, ignoredCountries);
        printf("Region               Total Population     Total Area       Population Density   Avg Literacy    GDP per Capita   GDP Region     \n");
        printf("%-20s%-20d%-20.0f%-20.2f%-20.2f%-20.2f%-20.0f\n\n", regionName, totalPopulation, totalArea, populationDensity, averageLiteracy, gdpPerCapita, totalGDP);
    }

    // Free the allocated memory
    free(keys);
}

void calculateStatisticsForCountries(PtMap map) {
    
    // Initialize variables to store statistics
    long totalPopulation = 0;
    double totalArea = 0.0;
    double totalGDP = 0.0;
    double totalLiteracyWeighted = 0.0;
    int ignoredCountries = 0;
    int consideredCountries = 0;

    // Retrieve the keys from the map
    MapKey* keys = mapKeys(map);
    int sizeOfMap;
    mapSize(map, &sizeOfMap);

    // Iterate through the map entries
    for (int i = 0; i < sizeOfMap; i++) {

        MapKey key = keys[i];
        MapValue value;
        mapGet(map, key, &value);

        // Check if the country belongs to the specified region
        if (value.population != -1 && value.area != -1  && value.gdp_capita != -1 && value.literacy != -1 && value.birthrate !=-1 && value.deathrate !=-1) {
            totalPopulation += value.population;
            totalArea += value.area;
            totalGDP += value.gdp_capita * value.population;
            totalLiteracyWeighted += value.literacy * value.population;
            consideredCountries++;
        } else {
            ignoredCountries++;
        }
    }

    // Calculate the derived statistics
    double populationDensity = totalPopulation / totalArea;  
    double gdpPerCapita = totalGDP / totalPopulation;
    double averageLiteracy = totalLiteracyWeighted / totalPopulation;

    // Display the statistics
    printf("\nGlobal Statistics\n");
    printf("%d countries considered and %d ignored by lack of data\n", consideredCountries, ignoredCountries);
    printf("Region               Total Population     Total Area       Population Density   Avg Literacy    GDP per Capita   GDP Region     \n");
    printf("%-20s%-20ld%-20.0f%-20.2f%-20.2f%-20.2f%-20.0f\n\n", "ALL", totalPopulation, totalArea, populationDensity, averageLiteracy, gdpPerCapita, totalGDP);

    // Free the allocated memory
    free(keys);
}

int calculateStatistics(PtMap map) {

    if(map == NULL){
        printf("First you need to load data from statistics.");
        return MAP_NULL;
    }

    char regionName[50];
    printf("Please insert the name of the region: ");

    readString(regionName, 50);

    //Convert regionName to UpperCase
    for (int i = 0; regionName[i]; i++) {
        regionName[i] = toupper(regionName[i]);
    } 

    //Calculates region specific statistics
    calculateStatisticsForRegion(map, regionName);

    //Calculates general statistics (all)
    calculateStatisticsForCountries(map);

    return 0;
}
