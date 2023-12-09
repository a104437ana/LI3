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
void addFlightToAirport(Airport *airport, void *flight);
//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate(void *airport);

//obtem a lista de voos do aeroporto
OrdList *getAirportOrdList(Airport *airport);

//gets
char *getAirportId(Airport *airport);

//sets

//liberta espaço em memória do aeroporto
void destroyAirport(void *airport);


#endif