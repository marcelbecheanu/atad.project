/**
 * @file time.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief  Provides the definition of Time struct and assoaciated operations.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <stdbool.h>

/**
 * @brief Data struct that represents the data that earthquake origins
 * 
 */

typedef struct time {
    int hour, min, sec;
} Time;


/**
 * @brief 
 * 
 * @param eTime from earthquakes.csv
 * @return Time struct
 */
Time earthquakeTime(char* eTime);