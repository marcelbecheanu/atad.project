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
#include "map.h"
#include "countryStatistics.h"
#include "stringWrap.h"
#include "input.h"

#define MAX_COUNTRY_STATISTICS 10000

CountryStatistics statisticsCreate(char* code, char* name, char* region, long population, long area,
long gdp_capita, float literacy, float birthdate, float deathrate){

    // Create an instance of the CountryStatistics structure
    CountryStatistics statistics;

    // Copy the provided values to the corresponding fields in the structure
    strcpy(statistics.code, code);
    strcpy(statistics.name, name);
    strcpy(statistics.region, region);
    statistics.population = population;
    statistics.area = area;
    statistics.gdp_capita = gdp_capita;
    statistics.literacy = literacy;
    statistics.birthrate = birthdate;
    statistics.deathrate = deathrate;

    return statistics;
}

