/**
 * @file date.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief  Provides the definition of Date struct.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include <stdbool.h>

/**
 * @brief Data
 * 
 */

typedef struct date {
    int day, month, year;
} Date;

/**
 * @brief 
 * 
 * @param eDate [in] from earthquakes.csv
 * @return Date [out] struct
 */
Date earthquakeDate(char* eDate);