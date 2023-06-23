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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "time.h"


Time earthquakeTime(char* eTime) {
    Time t;

    char* token = strtok(eTime, ":"); // Split the time string using ":"

    // Extract hour
    if (token != NULL) {
        t.hour = atoi(token); // Convert the token to an integer
        token = strtok(NULL, ":"); // Move to the next token
    }

    // Extract minute
    if (token != NULL) {
        t.min = atoi(token); // Convert the token to an integer
        token = strtok(NULL, ":"); // Move to the next token
    }

    // Extract second
    if (token != NULL) {
        t.sec = atoi(token); // Convert the token to an integer
    }

    return t;
}