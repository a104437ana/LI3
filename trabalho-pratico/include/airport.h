#ifndef _AIRPORT_
#define _AIRPORT_

#include "utility.h"
#include "orderedList.h"

typedef struct airport Airport;
//cria um novo aeroporto
Airport *createAirport(char *name);
//adiciona voo à lista de voos de um aeroporto
void addFlightToAirport(Airport *airport, unsigned long int id_flight, int origin);
void addDelayToAirport(Airport* airport, int delay);
//ordena a lista de voos de um aeroporto
void sortAirportFlightsByDepartureDate_airport(Airport *airport, void (*radixsortFlightsDate)(void*,void*), void *lookup);
//ordena a lista de atrasos de um aeroporto
int sortAirportDelays (Airport* airport);

//gets
char *getAirportId(Airport *airport);
double getAirportMedian(Airport *airport);
int getAirportListSize(Airport *airport);
int getAirportDelayListSize(Airport *airport);
//obtem a lista de voos do aeroporto
OrdList *getAirportOriginOrdList(Airport *airport);
OrdList *getAirportDestinationOrdList(Airport *airport);
//obtem o número de passageiros do aeroporto num dado ano
int getAirportPassengersYear(int year, Airport *airport, int (*compareFunction)(unsigned long int,unsigned long int,void*), int equal, void *lookup, int (*getFunction)(unsigned long int,void*));

//sets

//sort
void swapL(int a[], int i, int j);
int partitionL(int a[], int high, int pivot);
void qsortL (int a[], int n);
//liberta espaço em memória do aeroporto
void destroyAirport(void *airport);


#endif