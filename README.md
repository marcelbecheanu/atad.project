# Seismic Data Extraction and Analysis Project

This project consists of developing a C program to extract and present useful information from a file containing data on natural and artificial earthquakes that occurred in various countries. The program is a command interpreter that allows the user to obtain different types of information and perform statistical analyses.

## Data Structures Used

The program uses the following data structures and Abstract Data Types (ADTs) to store the information:

- **Earthquake**: Structure that represents a seismic event, containing information such as date, time, latitude, longitude, type, depth, and magnitude of the earthquake.
- **CountryStatistics**: Structure that represents the statistics of a country, including code, name, region, population, area, GDP per capita, literacy rate, birth rate, and death rate.
- **CountryLocation**: Structure that stores information about the location of countries or territories, such as code, latitude, longitude, territory name, and associated country name.

In addition to the mentioned structures, the List and Map ADTs are used to store collections of earthquakes and country statistics, respectively.

## Data Loading

The program supports loading data from three CSV files:

1. **earthquakes.csv**: Contains information about earthquakes and other explosions.
2. **world_country_locations.csv**: Contains information about the locations of countries/territories.
3. **world_country_statistics.csv**: Contains statistical data of the countries.

It is important to note that the program expects the files to be in the specified format and that the first line of each file is a header line.

## Available Commands

The program offers the following commands:

1. **LOADCL**: Loads the country/territory locations file.
2. **LOADEA**: Loads the earthquakes file.
3. **LOADST**: Loads the country statistics file.
4. **CLEAR**: Clears the loaded data from memory.
5. **QUIT**: Exits the program.
6. **SHOWALL**: Displays data for all earthquakes.
7. **SHOW_Y**: Displays earthquakes available in a specific year.
8. **SHOW_T**: Displays earthquakes available in a specific country/territory.
9. **SHOW_YT**: Displays earthquakes available in a specific country/territory and year.
10. **LIST_T**: Lists the country/territory codes that have earthquake data.
11. **COUNT**: Counts the number of earthquakes within a magnitude range for a specific country/territory.
12. **HISTOGRAM**: Displays a histogram of the distribution of earthquake magnitudes.

## Requirements and Program Execution

To run the program, it is necessary to have a C development environment installed. The source files should be compiled, and the resulting executable can be run from the command line.
