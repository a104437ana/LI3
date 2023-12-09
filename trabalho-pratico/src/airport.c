#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport.h"
#include "flight.h"
#include "orderedList.h"
#include "utility.h"

struct airport {
    char name[4];
    OrdList *flightsByDepartureDate;
};

//cria um novo aeroporto
Airport *createAirport(char *name) {
    Airport *airport = malloc(sizeof(Airport));
//    airport->name = strdup(name);
    airport->name[0] = name[0];
    airport->name[1] = name[1];
    airport->name[2] = name[2];
    airport->name[3] = name[3];
    airport->flightsByDepartureDate = createOrdList(AIRPORT_FLIGHTS_INI_SIZE);

    return airport;
}

//adiciona voo à lista de voos de um aeroporto
void addFlightToAirport(Airport *airport, void *flight) {
    addOrdList(airport->flightsByDepartureDate, flight);
}

int compareFlightsIds(void *flight1, void *flight2) {
    char *id1 = getFlightId((Flight *) flight1), *id2 = getFlightId((Flight *) flight2);
    return strcoll(id1, id2);
}

//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate(void *airport) {
    OrdList *flightsByDepartureDate = ((Airport *) airport)->flightsByDepartureDate;
    quickSort(flightsByDepartureDate, 0, getOrdListSize(flightsByDepartureDate)-1, compareFlightsIds, 0);
    radixSortFlightDate(flightsByDepartureDate);
}

//obtem a lista de voos do aeroporto
OrdList *getAirportOrdList(Airport *airport) {
    return airport->flightsByDepartureDate;
}

//gets
char *getAirportId(Airport *airport) {
    return airport->name;
}

//sets

//liberta espaço em memória do aeroporto
void destroyAirport(void *airport) {
    destroyOnlyOrdList(((Airport *) airport)->flightsByDepartureDate);
    free(((Airport *) airport)->name);
    free(airport);
}
