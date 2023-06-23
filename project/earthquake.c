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
#include <string.h>
#include "earthquake.h"

/**
 * @brief Cria um objeto Earthquake.
 *
 * Esta função cria e inicializa um objeto Earthquake com os parâmetros fornecidos.
 *
 * @param id O ID do terremoto.
 * @param countryCode O código do país associado ao terremoto.
 * @param date A data do terremoto.
 * @param time A hora do terremoto.
 * @param latitude A latitude da localização do terremoto.
 * @param longitude A longitude da localização do terremoto.
 * @param type O tipo do terremoto.
 * @param depth A profundidade do terremoto.
 * @param magnitude A magnitude do terremoto.
 * @param magnitudeType O tipo de medida de magnitude utilizado.
 *
 * @return Earthquake O objeto Earthquake criado.
 */
Earthquake createEarthquake(int id, char *countryCode, Date date, Time time, float latitude, float longitude, char *type, float depth, float magnitude, char *magnitudeType)
{
    Earthquake eq;
    eq.id = id;
    strcpy(eq.countryCode, countryCode);
    eq.date = date;
    eq.time = time;
    eq.latitude = latitude;
    eq.longitude = longitude;
    strcpy(eq.type, type);
    eq.depth = depth;
    eq.magnitude = magnitude;
    strcpy(eq.magnitudeType, magnitudeType);

    return eq;
}
