/**
 * @file histogram.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief Provides associated operations to histogram
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "list.h"

/**
 * @brief 
 * 
 * @param list [in] of earthquakes
 */
void showHistogram(PtList list);

/**
 * @brief 
 * 
 * @param list [in] of earthquakes
 * @param countryCode [in] of earthquake
 * @param countMagnitude [in] of specific magnitudes
 */
void calculateNumberEarthquakeMagnitude(PtList list, char* countryCode, int* countMagnitude) ;

/**
 * @brief Returns array of symbols '#'
 * 
 * @param count [in] of symbols
 * @return char* [out] of symbols '#'
 */
char* getMagnitudeSymbol(int count);