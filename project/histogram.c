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
#include <math.h>
#include "histogram.h"
#include "input.h"

void showHistogram(PtList list)
{
    int numOfCountries = 0;
    printf("Por favor, insira quantos países deseja utilizar no histograma (máximo 3): ");
    readInteger(&numOfCountries);

    char **listOfCodesOfCountries = (char **)malloc(numOfCountries * sizeof(char *));

    for(int i = 0; i < numOfCountries; i++)
    {
        listOfCodesOfCountries[i] = (char *)malloc(4 * sizeof(char));
        printf("Por favor, insira o código do %dº país: ", i + 1);
        readString(listOfCodesOfCountries[i], 4);
    }

    int countMagnitude[numOfCountries][6]; // Matriz para armazenar countMagnitude de cada país

    // Inicializa os valores da matriz com zero
    memset(countMagnitude, 0, numOfCountries * 6 * sizeof(int));

    for(int i = 0; i < numOfCountries; i++ )
    {
        calculateNumberEarthquakeMagnitude(list, listOfCodesOfCountries[i], countMagnitude[i]);
    }

    // Imprimir os resultados
    char* ranges[] = {"<= 6", "]6.0, 6.5]", "]6.5, 7.0]", "]7.0, 7.5]", "]7.5, 8.0]","> 8"};
    printf("Código | Magnitude | Número de Terramotos (escala logarítmica)\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < 6; i++)
    {
        for(int j = 0; j < numOfCountries; j++){
            char* symbols = getMagnitudeSymbol(countMagnitude[j][i]); // receber os Symbols
            printf("%s |  %s  | %s %d\n", listOfCodesOfCountries[j], ranges[i], symbols, countMagnitude[j][i]);
            free(symbols);  // Liberar a memória alocada
        }
        printf("-------------------------------------------------------------\n");
    }
        
    // Limpar
    for (int i = 0; i < numOfCountries; i++)
    {
        free(listOfCodesOfCountries[i]);
    }
    
    free(listOfCodesOfCountries);
}

void calculateNumberEarthquakeMagnitude(PtList list, char* countryCode, int* countMagnitude) {
    int sizeOfList = 0;
    if(listSize(list, &sizeOfList) != LIST_OK || sizeOfList == 0) {
        printf("Por favor, carregue os terramotos primeiro.");
        return;
    }

    for (int i = 0; i < sizeOfList; i++)
    {
        Earthquake earthquake;
        if (listGet(list, i, &earthquake) == LIST_OK) {
            if (strcmp(countryCode, earthquake.countryCode) == 0) {
                float magnitude = earthquake.magnitude;
                if (magnitude <= 6)
                    countMagnitude[0]++;
                else if (magnitude > 6 && magnitude <= 6.5)
                    countMagnitude[1]++;
                else if (magnitude > 6.5 && magnitude <= 7)
                    countMagnitude[2]++;
                else if (magnitude > 7 && magnitude <= 7.5)
                    countMagnitude[3]++;
                else if (magnitude > 7.5 && magnitude <= 8)
                    countMagnitude[4]++;
                else
                    countMagnitude[5]++;
            }
        }
    }
}

char* getMagnitudeSymbol(int count) {
    int escala = count == 0 ? 0 : log2l(count) + 1;
    int numSimbolos = escala * 3;
    char* symbols = (char*)malloc((numSimbolos + 1) * sizeof(char));
    memset(symbols, '#', numSimbolos);
    symbols[numSimbolos] = '\0';
    return symbols;
}