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
#include "countryLocations.h"


CountryLocationsArray createCountryLocationsArray()
{
    // Allocate memory for the CountryLocationsArray structure
    CountryLocationsArray countryLocationsArray = (CountryLocationsArray)malloc(sizeof(struct countryLocationsArray));

    // Check if memory allocation was successful
    if (countryLocationsArray == NULL) return NULL;

    // Initialize the locations field to NULL and size field to 0
    countryLocationsArray->locations = NULL;
    countryLocationsArray->size = 0;

    // Return the initialized CountryLocationsArray structure
    return countryLocationsArray;
}


int destroyCountryLocationsArray(CountryLocationsArray *array)
{
    // Check if the pointer to the array or the array itself is NULL
    if (array == NULL || *array == NULL) return -1;

    int discardedElements = 0;

    // Check if the locations array within the structure is not NULL
    if ((*array)->locations != NULL) {
        // Call the function clearCountryLocationsArray() to clear the locations array
        clearCountryLocationsArray(*array, &discardedElements);
    }

    // Free the memory allocated for the CountryLocationsArray structure
    // and set the pointer to the array to NULL to avoid accessing deallocated memory
    free(*array);
    *array = NULL;

    // Return 0 to indicate successful destruction
    return 0;
}

int ensureCapacityOfCountryLocationsArray(CountryLocationsArray array)
{
    int newCapacity = array->size + 1;
    printf("Current size: %d, New capacity: %d\n", array->size, newCapacity); 

    CountryLocation *newArray = (CountryLocation*)realloc(array->locations, newCapacity * sizeof(CountryLocation));
    if (newArray == NULL){

    // If realloc fails (returns NULL), allocate a new array and copy the existing elements
    if (newArray == NULL) {
        newArray = (CountryLocation *)malloc(newCapacity * sizeof(CountryLocation));
        
        // If memory allocation fails, return ARRAY_NO_MEMORY error code
        if (newArray == NULL) return ARRAY_NO_MEMORY;
        memcpy(newArray, array->locations, array->size * sizeof(CountryLocation));
        free(array->locations);
    }

    array->locations = newArray;
    array->size = newCapacity;
    return ARRAY_OK;
    }
}

int countryLocationsArrayAdd(CountryLocationsArray array, CountryLocation location){
    // Check if the array is NULL
    if (array == NULL) return -1;

    // If the size of the array is 0, allocate memory for the locations array
    if (array->size == 0)
    {
        array->locations = (CountryLocation*)malloc(sizeof(CountryLocation));

        // If memory allocation fails, return -1 to indicate an error
        if (array->locations == NULL) return -1;
    }
    else
    {
        // Reallocate memory for the locations array with increased size
        CountryLocation *temp = (CountryLocation*)realloc(array->locations, (array->size + 1) * sizeof(CountryLocation));

        // If reallocation fails, return -1 to indicate an error
        if (temp == NULL) return -1;

        // Update the locations array with the new array
        array->locations = temp;
    }

    // Add the new location to the locations array at the end
    array->locations[array->size] = location;

    // Increment the size field of the array
    array->size++;

    // Return 0 to indicate successful addition
    return 0;
}

int countryLocationsArraySize(CountryLocationsArray array, int *ptSize) {
    // Check if the array is NULL
    if (array == NULL) return ARRAY_NULL; 
    // Assign the size of the array to the provided pointer
    *ptSize = array->size;
    return ARRAY_OK;
}



int loadCountryLocations(CountryLocationsArray array)
{
    if (array == NULL) return -1; // Check that array is not NULL

    FILE *file = fopen("dataset/world_country_locations.csv", "r");
    if (file == NULL)
    {
        printf("Failed to open the country locations file.\n");
        return -1;
    }

    char line[256];
    
    // Ignore and discard frist line
    fgets(line, sizeof(line), file);

    while (fgets(line, sizeof(line), file))
    {
        // Split the line into tokens using ';' as the delimiter
        char *token;
        token = strtok(line, ";");

        // Read the country location data from the tokens
        CountryLocation location;

        strcpy(location.code, "");
        location.latitude = 0.0;
        location.longitude = 0.0;
        strcpy(location.territoryName, "");
        strcpy(location.countryName, "");
        strcpy(location.territoryRegion, "");

        if (token != NULL) strcpy(location.code, token);

        token = strtok(NULL, ";");
        if (token != NULL)
            if(strcmp(token, "N.A.") != 0)
                location.latitude = atof(token);
            else
                location.latitude = -1;

        token = strtok(NULL, ";");
        if (token != NULL)
            if(strcmp(token, "N.A.") != 0)
                location.longitude = atof(token);
            else
                location.longitude = -1;

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(location.territoryName, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(location.countryName, token);

        token = strtok(NULL, ";");
        if (token != NULL) strcpy(location.territoryRegion, token);


        // Add the country location to the array
        countryLocationsArrayAdd(array, location);
    }

    fclose(file);
    return 0;
}

void showCountryLocations(CountryLocationsArray array)
{
    if (array == NULL || array->locations == NULL) return;

    for (int i = 0; i < array->size; i++)
    {
        printf("Code: %s\n", array->locations[i].code);
        printf("Latitude: %f\n", array->locations[i].latitude);
        printf("Longitude: %f\n", array->locations[i].longitude);
        printf("Territory Name: %s\n", array->locations[i].territoryName);
        printf("Country Name: %s\n", array->locations[i].countryName);
        printf("Territory Region: %s\n", array->locations[i].territoryRegion);
        printf("\n");
    }
}

int clearCountryLocationsArray(CountryLocationsArray array, int* discardedRecords) {

    if (array == NULL) {
        return ARRAY_NULL; // Nothing to clear if the array is NULL
    }

    int previousSize = array->size;

    free(array->locations);
    
    // Reset the size to 0
    array->size = 0;

    if (discardedRecords != NULL) {
        *discardedRecords = previousSize;
    }

    array->locations = NULL;

    return ARRAY_OK; 
}