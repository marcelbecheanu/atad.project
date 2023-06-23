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
#include <ctype.h>

#include "input.h"
#include "list.h"
#include "listElem.h"
#include "earthquakeUtils.h"
#include "countryLocations.h"

/**
 * @brief Loads all earthquakes from .csv to a list
 * 
 * @return PtList 
 */
PtList loadEarthquakes(CountryLocationsArray *locations) {

    PtList list = listCreate();

    FILE* stream = fopen("dataset/earthquakes.csv", "r");
    if(stream == NULL){
        printf("File not found.\n");
        return list;
    }

    char line[1024];

    // Read and discard the header line
    fgets(line, 1024, stream);

    while (fgets(line, 1024, stream))
    {
   
        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 9, ";");
        
        int id = atoi(tokens[0]);
        Date date = earthquakeDate(tokens[1]);
        Time time = earthquakeTime(tokens[2]);
        float latitude = atof(tokens[3]);
        float longitude = atof(tokens[4]);
        char* type = (char*) malloc(20 * sizeof(char));
        strcpy(type, tokens[5]);
        float depth = atof(tokens[6]);
        float magnitude = atof(tokens[7]);
        char* magnitudeType = (char*) malloc(3 * sizeof(char));
        strcpy(magnitudeType, tokens[8]);

        char* nearestCountryCode = findNearestCountry(latitude, longitude, (*locations)->locations, (*locations)->size);
        Earthquake e = createEarthquake(id, nearestCountryCode, date, time, latitude, longitude, type, depth, magnitude, magnitudeType);

        int size;
        listSize(list, &size);
        listAdd(list, size, e);

        free(type);
        free(magnitudeType);

	    free(tokens);
        free(tmp);

    }

    fclose(stream);

    return list;
}

// Function to calculate the euclidian distance between two points
float euclideanDistance(float x1, float y1, float x2, float y2) {
    return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

// Function to show the territory/country nearest of the earthquake based on the calculated euclidian distance
char* findNearestCountry(float earthquakeLatitude, float earthquakeLongitude, CountryLocation* locations, int numLocations)
 {
    char* nearestCountryCode = NULL;
    float minDistance = INFINITY;

    for (int i = 0; i < numLocations; i++) {
        float distance = euclideanDistance(earthquakeLatitude, earthquakeLongitude, locations[i].latitude, locations[i].longitude);
        if (distance < minDistance) {
            minDistance = distance;
            nearestCountryCode = locations[i].code;
        }
    }
    
    return nearestCountryCode;
}

void displayCountriesWithEarthquake(PtList list, CountryLocationsArray locations){
    
    int sizeOfList = 0;
    int sizeOfListEarthQuake = 0;
    if(listSize(list, &sizeOfListEarthQuake) != LIST_OK || countryLocationsArraySize(locations, &sizeOfList) != ARRAY_OK) {
        printf("Não foi possível aceder à lista!");
        return;
    }

    printf("Número de Países encontrados: %d\n", sizeOfList);

    // Criar um vetor para armazenar os códigos de países/territórios encontrados
    char** listOfCodesOfCountries = (char**) malloc(sizeOfList * sizeof(char*));
    int numCountries = 0;

    // Percorrer a lista de terramotos e adicionar os códigos de países/territórios únicos ao vetor
    for (int i = 0; i < sizeOfListEarthQuake; i++) {
        Earthquake e;
        if(listGet(list, i, &e) == LIST_OK) {
            char* countryCode = e.countryCode;
            int found = 0;

            // Verificar se o código do país já existe no vetor
            for (int j = 0; j < numCountries; j++) {
                if (strcmp(listOfCodesOfCountries[j], countryCode) == 0) {
                    found = 1;
                    break;
                }
            }

            // Se o código do país não existir no vetor, adicioná-lo
            if (!found) {
                listOfCodesOfCountries[numCountries] = strdup(countryCode);
                numCountries++;
            }
        }
    }

    // Mostrar os códigos de países/territórios encontrados
    for (int i = 0; i < numCountries; i++) {
        printf("%s\n", listOfCodesOfCountries[i]);
        free(listOfCodesOfCountries[i]);
    }

    //showCountryLocations(locations);
    printf("%d countries with earthquake data", numCountries);

    free(listOfCodesOfCountries);
}

//Commands related to SHOW functions

// Function to print earthquakes in a paginated manner
void printEarthquakes(PtList list) {
    int size;
    listSize(list, &size);

    int currentPage = 0;
    int pageSize = 50;

    while (currentPage * pageSize < size) {
        printf("Number of records found: %d\n", size);

        printf("%-4s %-15s %-11s %-10s %-9s %-12s %-16s %-6s %-10s %s\n",
               "\nID", "Country Code", "Date", "Time", "Latitude", "Longitude", "Type", "Depth", "Magnitude", "Magnitude Type");
        printf("--------------------------------------------------------------------------------------------------\n");

        // Print earthquake records for the current page
        for (int i = currentPage * pageSize; i < (currentPage + 1) * pageSize && i < size; i++) {

            Earthquake earthquake;
            listGet(list, i, &earthquake);

        // Print earthquake data
           listElemPrint(earthquake);
        }

        int choice;
        printf("\n1. Next 50\n2. Return\nOPTION> ");

        if (scanf("%d", &choice) != 1) {
            break;
        }

        if (choice == 2) {
            break;
        }

        currentPage++;
    }
}

// Compare years of two earthquakes
int compareEarthquakeYears(Earthquake* e1, Earthquake* e2) {
    int year1 = e1->date.year;
    int year2 = e2->date.year;

    return year1 - year2;
}

// Function to sort earthquakes by year in ascending order
/*void sortEarthquakesByYear(PtList earthquakes) {
    int size;
    listSize(earthquakes, &size);

    // Bubble sort algorithm
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Earthquake earthquake1, earthquake2, oldElem;
            listGet(earthquakes, j, &earthquake1);
            listGet(earthquakes, j + 1, &earthquake2);

            if (compareEarthquakeYears(&earthquake1, &earthquake2) > 0) {
                listSet(earthquakes, j, earthquake2, &oldElem);
                listSet(earthquakes, j + 1, oldElem, &earthquake1);
            }
        }
    }
} */

// Compare country codes of two earthquakes
int compareEarthquakeCountryCodes(Earthquake* e1, Earthquake* e2) {
    return strcmp(e1->countryCode, e2->countryCode);
}

// Function to sort earthquakes by country code on ascending order
void sortEarthquakesByCountryCode(PtList earthquakes) {
    int size;
    listSize(earthquakes, &size);

    // Bubble sort algorithm
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Earthquake earthquake1, earthquake2, oldElem;
            listGet(earthquakes, j, &earthquake1);
            listGet(earthquakes, j + 1, &earthquake2);

            if (compareEarthquakeCountryCodes(&earthquake1, &earthquake2) > 0) {
                listSet(earthquakes, j, earthquake2, &oldElem);
                listSet(earthquakes, j + 1, oldElem, &earthquake1);
            }
        }
    }
}


// Command function for SHOW_Y

// Function to filter earthquakes by year
PtList filterEarthquakesByYear(PtList earthquakes) {
    
    int year;
    do {
      printf("Enter the year: ");
    } while(!readInteger(&year)); /* loops while invalid */

    int size;
    listSize(earthquakes, &size);

    PtList filteredList = listCreate(); //Libertar memória

    int filteredSize;
    listSize(filteredList, &filteredSize);

    // Filter earthquakes by year
    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(earthquakes, i, &earthquake);

        if (earthquake.date.year == year) {
            listAdd(filteredList, filteredSize, earthquake);
            filteredSize++;
        }
    }

    if (filteredSize == 0) {
        printf("Earthquake data not available for year %d.\n", year);
    }

    //sortEarthquakesByYear(earthquakes); // comment when testing valgrind

    return filteredList;
}

// Function to show earthquakes by year
void showEarthquakesbyYear(PtList earthquakes) {

    PtList filteredList = filterEarthquakesByYear(earthquakes);
    printEarthquakes(filteredList);
    listDestroy(&filteredList);
}


// Command function for SHOW_T

PtList filterEarthquakesByCountry(PtList earthquakes) {
    char countryCode[3];
    printf("Enter the country code: ");
    readString(countryCode, 3);

    // Convert country code to Upper
    for (int i = 0; countryCode[i]; i++) {
        countryCode[i] = toupper(countryCode[i]);
    }

    int size;
    listSize(earthquakes, &size);

    PtList filteredList = listCreate();

    int filteredSize;
    listSize(filteredList, &filteredSize);

    // Filter by code
    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(earthquakes, i, &earthquake);

        char earthquakeCountryCode[3];
        strcpy(earthquakeCountryCode, earthquake.countryCode);

        if (strcmp(earthquakeCountryCode, countryCode) == 0) {
            listAdd(filteredList, filteredSize, earthquake);
            filteredSize++;
        }
    }

    if (filteredSize == 0) {
        printf("Earthquake data not available for country code %s.\n", countryCode);
    }

    sortEarthquakesByCountryCode(filteredList);

    return filteredList;
}

void showEarthquakesByCountry(PtList earthquakes) {

    PtList filteredList = filterEarthquakesByCountry(earthquakes);
    printEarthquakes(filteredList);
    listDestroy(&filteredList);
}


// Command function for SHOW_YT

PtList filterEarthquakesByCountryYear(PtList earthquakes) {

    char countryCode[3];
    int year;

    do {
      printf("Enter the year: ");
    } while(!readInteger(&year)); /* loops while invalid */

    printf("Enter the country code: ");
    readString(countryCode, 100);

    // Convert country code to Upper
    for (int i = 0; countryCode[i]; i++) {
        countryCode[i] = toupper(countryCode[i]);
    }

    int size;
    listSize(earthquakes, &size);

    PtList filteredList = listCreate();

    int filteredSize;
    listSize(filteredList, &filteredSize);

    // Filter by code and year
    for (int i = 0; i < size; i++) {
        Earthquake earthquake;
        listGet(earthquakes, i, &earthquake);

        char earthquakeCountryCode[3];
        strcpy(earthquakeCountryCode, earthquake.countryCode);
        int earthquakeYear = earthquake.date.year;

        // Compare country code and year
        if (strcmp(earthquakeCountryCode, countryCode) == 0 && earthquakeYear == year) {
            listAdd(filteredList, filteredSize, earthquake);
            filteredSize++;
        }
    }

    if (filteredSize == 0) {
        printf("Earthquake data not available for country code %s and year %d.\n", countryCode, year);
    }

    return filteredList;
}


void showEarthquakesByCountryYear(PtList earthquakes) {

    PtList filteredList = filterEarthquakesByCountryYear(earthquakes);
    printEarthquakes(filteredList);
    listDestroy(&filteredList);
}


//Command function for COUNT

void countEarthquake(PtList list) {

    int sizeOfEarthQuake = 0;
    if(listSize(list, &sizeOfEarthQuake) != LIST_OK || sizeOfEarthQuake == 0){
        printf("Please load first Earthquakes.");
        return;
    }

    double minimum, maximum;
    printf("Please insert the minimum and maximum magnitude: \n");
    readDouble(&minimum);
    readDouble(&maximum);

    if(minimum > maximum) {
        double temp = minimum;
        minimum = maximum;
        maximum = temp;
    }

    char countryCode[3];
    printf("Please insert the country code: \n");
    readString(countryCode, 3);

    int hasCountry = 0;
    int hasMagnitude = 0;
    int earthquakeCount = 0;
    int mwCount = 0, mbCount = 0, msCount = 0;

    for (int i = 0; i < sizeOfEarthQuake; i++) {
        Earthquake earthquake;
        if(listGet(list, i, &earthquake) == LIST_OK) {
            if(strcmp(countryCode, earthquake.countryCode) == 0){
                hasCountry = 1;
                if(earthquake.magnitude >= minimum && earthquake.magnitude <= maximum){
                    hasMagnitude = 1;
                    earthquakeCount++;
                    if(strcmp(earthquake.magnitudeType, "MW") == 0) {
                        mwCount++;
                    } else if(strcmp(earthquake.magnitudeType, "MB") == 0) {
                        mbCount++;
                    } else if(strcmp(earthquake.magnitudeType, "MS") == 0) {
                        msCount++;
                    }
                }
            }
        }
    }

    if(hasCountry == 0) {
        printf("Earthquake data not available for %s.", countryCode);
        readChar(NULL);
        return;
    }

    if(hasMagnitude == 0) {
        printf("Earthquake data not available for magnitude between [%.00f, %.00f].", minimum, maximum);
        readChar(NULL);
        return;
    }

    printf("Number of earthquakes that the country had within the given interval: %d\n", earthquakeCount);
    printf("Earthquakes percentage per type:\n");
    printf("   MW  |   MB  |   MS  |\n");
    printf("  %.1f%% | %.1f%% | %.1f%% |\n",(mwCount / (double)earthquakeCount) * 100, (mbCount / (double)earthquakeCount) * 100, (msCount / (double)earthquakeCount) * 100);
    
    readChar(NULL);

}

void showTopEarthquakeData(CountryLocationsArray locations, PtList earthquakes){

    int sizeOfCountries = 0, sizeOfEarthquake = 0;
    if(countryLocationsArraySize(locations, &sizeOfCountries) != ARRAY_OK || sizeOfCountries == 0 || listSize(earthquakes, &sizeOfEarthquake) != LIST_OK || sizeOfEarthquake == 0){
        printf("Please load 'country location data' and 'earthquake data' first.");
        return;
    }

    int numCountriesToShow = 0;
    while (numCountriesToShow <= 0 || numCountriesToShow > sizeOfCountries)
    {
        printf("Insira o valor de N (máximo %d): \n", sizeOfCountries);
        readInteger(&numCountriesToShow);
        if(numCountriesToShow > 0 && numCountriesToShow <= sizeOfCountries)
            break;
        printf("N tem que ser maior que zero e menor ou igual a %d.\n", sizeOfCountries);
    }

    EarthquakeData* earthquakeData = (EarthquakeData *)malloc(sizeOfCountries * sizeof(EarthquakeData));
    
    // Fill list with countries.
    for (int i = 0; i < sizeOfCountries; i++) {
        strcpy(earthquakeData[i].code, locations->locations[i].code);
        strcpy(earthquakeData[i].territoryName, locations->locations[i].territoryName);
    }

    fillListWithEarthquakeByCountries(earthquakeData, earthquakes, sizeOfCountries);
    sortEarthquakeDataByNumberOfEarthquakes(earthquakeData, sizeOfCountries);
    printListWithEarthquakes(earthquakeData, numCountriesToShow);
    
    free(earthquakeData);
}

void fillListWithEarthquakeByCountries(EarthquakeData* earthquakeData, PtList earthquakes, int sizeOfCountries) {
    int sizeOfEarthquakes = 0;
    listSize(earthquakes, &sizeOfEarthquakes);
    for (int i = 0; i < sizeOfCountries; i++) {
        earthquakeData[i].numberOfEarthquakes = 0;
        earthquakeData[i].averageMagnitude = 0.0;
        earthquakeData[i].averageDepth = 0.0;

        for (int j = 0; j < sizeOfEarthquakes; j++) {
            Earthquake earthquake;
            listGet(earthquakes, j, &earthquake);

            if (strcmp(earthquakeData[i].code, earthquake.countryCode) == 0) {
                earthquakeData[i].numberOfEarthquakes += 1;
                earthquakeData[i].averageMagnitude += earthquake.magnitude;
                earthquakeData[i].averageDepth += earthquake.depth;
            }
        }

        if (earthquakeData[i].numberOfEarthquakes > 0) {
            earthquakeData[i].averageMagnitude /= earthquakeData[i].numberOfEarthquakes;
            earthquakeData[i].averageDepth /= earthquakeData[i].numberOfEarthquakes;
        }
    }
}
void sortEarthquakeDataByNumberOfEarthquakes(EarthquakeData* earthquakeData, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (earthquakeData[j].numberOfEarthquakes < earthquakeData[j + 1].numberOfEarthquakes) {
                EarthquakeData temp = earthquakeData[j];
                earthquakeData[j] = earthquakeData[j + 1];
                earthquakeData[j + 1] = temp;
            }
        }
    }
}

void printListWithEarthquakes(EarthquakeData* earthquakeData, int size) {
    printf("Code Territory Name                                #quakes  Depth   Avg Magnitude Avg\n");
    for (int i = 0; i < size; i++) {
        printf("%-4s %-44s %-8d %.2f    %.2f\n",
            earthquakeData[i].code,
            earthquakeData[i].territoryName,
            earthquakeData[i].numberOfEarthquakes,
            earthquakeData[i].averageDepth,
            earthquakeData[i].averageMagnitude);
    }
}