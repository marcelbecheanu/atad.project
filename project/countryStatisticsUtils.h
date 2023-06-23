/**
 * @file countryStatisticsUtils.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief Provides associated operations to countryStatistics.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "map.h"

/**
 * @brief 
 * 
 * @return PtMap 
 */
PtMap loadCountryStatistics();

/**
 * @brief 
 * 
 * @param map 
 */
void showCountryStatisticsByOrder(PtMap map);

/**
 * @brief 
 * 
 * @param countries 
 * @param j 
 */
void swapCountries(CountryStatistics *countries, int j);

/**
 * @brief 
 * 
 * @param map 
 * @return int 
 */
int calculateStatistics(PtMap map);

/**
 * @brief 
 * 
 * @param map 
 * @param regionName 
 */
void calculateStatisticsForRegion(PtMap map, char* regionName);

/**
 * @brief 
 * 
 * @param map 
 */
void calculateStatisticsForCountries(PtMap map);
