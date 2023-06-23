#include <stdio.h>
#include "listElem.h"

void listElemPrint(ListElem elem) {
	printf("%-4d %-15s %02d/%02d/%04d  %02d:%02d:%02d  %-9.3f  %-9.3f  %-14s  %-6.0f %-10.1f %s\n", elem.id, elem.countryCode, elem.date.month, 
	elem.date.day, elem.date.year, elem.time.hour, elem.time.min, elem.time.sec, elem.latitude, elem.longitude, elem.type, elem.depth, elem.magnitude, elem.magnitudeType); 
}