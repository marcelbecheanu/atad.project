/**
 * @file earthquake.h
 * @author Mauro Amaro (202000905 - EI-01), Marcel Becheanu(202002358 - EI-03), 
 * David Saroco(202002037 - EI-03), Inês Palet(201701984 - EI-05)
 * @brief  Provides the definition of Earthquake struct.
 * @version 0.1
 * @date 2023-06-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include <stdbool.h>
#include "date.h"
#include "time.h"

/**
 * @brief 
 * 
 */
typedef struct earthquake
{

    int id;
    // Código de 2 letras do país ou território mais próximo (countryLocation)
    char countryCode[3]; // Calculado a partir das localizações durante importação
    Date date;
    Time time;
    float latitude;
    float longitude;
    char type[20]; // Earthquake | Explosion | Nuclear Explosion | Rock Burst
    float depth;
    float magnitude;
    char magnitudeType[3]; // MB | MD | MH | ML | MS | MW

} Earthquake;

/**
 * @brief Creates an Earthquake element
 * 
 * @param id [in] of earthquake elem
 * @param countryCode [in] of earthquake elem
 * @param date [in] of earthquake elem
 * @param time [in] of earthquake elem
 * @param latitude [in] of earthquake elem
 * @param longitude [in] of earthquake elem
 * @param type [in] of earthquake elem
 * @param depth [in] of earthquake elem
 * @param magnitude [in] of earthquake elem
 * @param magnitudeType [in] of earthquake elem
 * @return Earthquake [out] elem
 */
Earthquake createEarthquake(int id, char *countryCode, Date date, Time time, float latitude, float longitude, char *type, float depth, float magnitude, char *magnitudeType);

