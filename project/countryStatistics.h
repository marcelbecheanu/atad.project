/**
 * @file countryStatistics.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief  Provides the definition of countryStatistics struct.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief Data struct that repsents the statistics of a country.
 *
 */
typedef struct countryStatistics {
    char code[4]; // Código de 2 letras que representa o país
    char name[64];
    char region[64]; // UN Regions + ANTARCTICA + SOUTH ATLANTIC + INDIAN OCEAN
    long population;
    long area;
    long gdp_capita; // Produto interno bruto per capita. 
    float literacy;  // Percentagem de literacia. 
    float birthrate; // Número de nascimentos por 1000 pessoas por ano.
    float deathrate; // Número de mortes por 1000 pessoas por ano. 
} CountryStatistics;

/**
 * @brief Creates a new statistic
 * 
 * @param code [in] country code statistic
 * @param name [in] country name statistic
 * @param region [in] country region statistic
 * @param population [in] country population statistic
 * @param area [in] country area statistic
 * @param gdp_capita [in] gdp_capita statistic
 * @param literacy [in] literacy statistic
 * @param birthdate [in] birthdade statistic
 * @param deathrate [in] deathrate statistic
 * @return CountryStatistics [out] elem 
 */
CountryStatistics statisticsCreate(char* code, char* name, char* region, long population, long area,
long gdp_capita, float literacy, float birthdate, float deathrate);