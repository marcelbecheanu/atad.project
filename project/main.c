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
#include <stdbool.h>

#include "input.h"

#include "list.h"
#include "map.h"

#include "countryLocations.h"
#include "countryStatistics.h"
#include "earthquakeUtils.h"
#include "countryStatisticsUtils.h"
#include "histogram.h"

/**
 * @brief Prints the command menu.
 */
void printMenu();
/**
 * @brief Waits for user to press a key.
 */
void waitForKeypress();

/**
 * @brief Program entry point.
 * @return int error code: EXIT_SUCCESS or EXIT_FAILURE
 */
int main()
{
    /* Feel free to change whatever you want. */

    // TODO: variables ?
    PtList earthquakes = NULL;
    PtMap statistics = NULL;
    CountryLocationsArray locations = createCountryLocationsArray();

    /* Command interpreter. */
    char command[100];
    while (true)
    {

        printMenu();
        readString(command, 100);

        if (strcasecmp(command, "QUIT") == 0)
        {
            // TODO: Any memory cleanup before the end of the program?
            if(earthquakes != NULL){listDestroy(&earthquakes);}
            if(statistics != NULL){mapDestroy(&statistics);}
            if(locations != NULL){destroyCountryLocationsArray(&locations);}

            // Break loop, effectively leaving the command line
            break;
        }
        else if (strcasecmp(command, "LOADEA") == 0)
		{   
            int sizeLocations;
            countryLocationsArraySize(locations, &sizeLocations);

            if(sizeLocations == 0){
                printf("Please load country locations first.");
                continue;
            }

             earthquakes = loadEarthquakes(&locations);

			if(earthquakes == NULL){
                continue;
            } 

            int size;
			listSize(earthquakes, &size);

			//listPrint(earthquakes); Print EarthquakesList
			printf("%d earthquake records imported", size);

		}
        else if (strcasecmp(command, "LOADCL") == 0)
        {
            // Insert call for function here ...
            int result = loadCountryLocations(locations); // Corrected function call
            if (result == 0)
            {
                int size = 0;
                countryLocationsArraySize(locations, &size);
                printf("%d country location records imported\n", size);
            }
            else
            {
                printf("File not found.\n");
            }
        }
        else if (strcasecmp(command, "LOADST") == 0)
        {
            
            statistics = loadCountryStatistics();

			if(statistics == NULL){
                continue;
            } 

            int size;
			mapSize(statistics, &size);

			//mapPrint(statistics);
			printf("%d country records imported", size);
        }
        else if (strcasecmp(command, "SHOWALL") == 0)
        {
			printEarthquakes(earthquakes); //Prints all earthquakes (50 records per page)
        }
        else if (strcasecmp(command, "SHOW_Y") == 0)
        {
			showEarthquakesbyYear(earthquakes);
        }
        else if (strcasecmp(command, "SHOW_T") == 0)
        {
			showEarthquakesByCountry(earthquakes);
        }
        else if (strcasecmp(command, "SHOW_YT") == 0)
        {
			showEarthquakesByCountryYear(earthquakes);
        }
        else if(strcasecmp(command, "CLEAR") == 0){

            // Clear locations
            int discardedCountryLocations;
            clearCountryLocationsArray(locations, &discardedCountryLocations);

            //Clear earthquakes
            int earthquakesCleared;
            listSize(earthquakes, &earthquakesCleared);
            listClear(earthquakes);

            //Clear statistics
            int statisticsCleared;
            mapSize(statistics, &statisticsCleared);
            mapClear(statistics);

            //Print cleared records
            printf("%d records deleted from Earthquakes", earthquakesCleared);
            printf("\n%d records deleted from Country Statistics", statisticsCleared);
            printf("\n%d records deleted from Country Locations", discardedCountryLocations);

        }
        else if(strcasecmp(command, "LIST_T") == 0){
            displayCountriesWithEarthquake(earthquakes,locations);
        }
        else if(strcasecmp(command, "COUNT") == 0){
            countEarthquake(earthquakes);
        }
        else if(strcasecmp(command, "HISTOGRAM") == 0){
            showHistogram(earthquakes);
        }
        else if(strcasecmp(command, "COUNTRY_S") == 0){
            showCountryStatisticsByOrder(statistics);
        }
        else if (strcasecmp(command, "REGION_AVG") == 0)
        {
            calculateStatistics(statistics);
        }
        else if (strcasecmp(command, "TOPN") == 0)
        {
            showTopEarthquakeData(locations, earthquakes);
        }
        else
        {
            printf("Command not found.\n");
        }

        waitForKeypress();
    }

    return EXIT_SUCCESS;
}

void printMenu()
{
    printf("\n===================================================================================");
    printf("\n                          EarthQuake Data Analysis ");
    printf("\n===================================================================================");
    printf("\nA. Base commands (LOADCL, LOADEA, LOADST, CLEAR).");
    printf("\nB. Aggregated info about earthquakes (SHOWALL, SHOW_Y, SHOW_T, SHOW_YT, LIST_T, COUNT, HISTOGRAM");
    printf("\nC. Aggregated info about countries and regions (COUNTRY_S, REGION_AVG).");
    printf("\nD. Complex indicators; require earthquake and country data (TOPN).");
    printf("\n\nExit (QUIT)\n\n");
    printf("COMMAND?> ");
}

void waitForKeypress()
{
    printf("\n\nPress any key to continue ...");
    getchar();
}
