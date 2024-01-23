#ifndef _AIRPORT_
#define _AIRPORT_

#include "utility.h"
#include "flight.h"
#include "orderedList.h"

#define AIRPORT_FLIGHTS_INI_SIZE 100

typedef struct airport Airport;
//cria um novo aeroporto
Airport *createAirport(char *name);
//adiciona voo à lista de voos de um aeroporto
void addFlightToAirport(Airport *airport, unsigned long int id_flight, int origin);
void addDelayToAirport(Airport* airport, int delay);
void sortAirportFlightsByDepartureDate_airport(Airport *airport, void (*radixsortFlightsDate)(void*,void*), void *lookup);

//obtem a lista de voos do aeroporto
OrdList *getAirportOriginOrdList(Airport *airport);
OrdList *getAirportDestinationOrdList(Airport *airport);
//gets
char *getAirportId(Airport *airport);
double getAirportMedian(Airport *airport);
int getAirportListSize(Airport *airport);
int getAirportDelayListSize(Airport *airport);
int getAirportPassengersYear(int year, Airport *airport, int (*compareFunction)(unsigned long int,unsigned long int,void*), int equal, void *lookup, int (*getFunction)(unsigned long int,void*));

//sets
void swapL(int a[], int i, int j);
int partitionL(int a[], int high, int pivot);
void qsortL (int a[], int n);
int sortAirportDelays (Airport* airport);
//liberta espaço em memória do aeroporto
void destroyAirport(void *airport);


#endif