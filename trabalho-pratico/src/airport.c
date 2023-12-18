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
    memcpy(airport->name, name, 4);
    airport->flightsByDepartureDate = createOrdList(AIRPORT_FLIGHTS_INI_SIZE);

    return airport;
}

//adiciona voo à lista de voos de um aeroporto
void addFlightToAirport(Airport *airport, char *id_flight) {
    char *flight = strdup(id_flight);
    addOrdList(airport->flightsByDepartureDate, flight);
}

int compareFlightsIds(void *id1, void *id2) {
//    char *id1 = getFlightId((Flight *) flight1), *id2 = getFlightId((Flight *) flight2);
    return strcoll(id1, id2);
}

//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate(void *airport, Hashtable *lookupTable) {
    OrdList *flightsByDepartureDate = ((Airport *) airport)->flightsByDepartureDate;
    quickSort(flightsByDepartureDate, 0, getOrdListSize(flightsByDepartureDate)-1, compareFlightsIds, 0); //ordena por ids
    radixSortFlightDate(flightsByDepartureDate, lookupTable); //ordena por datas
    setOrdListOrd(flightsByDepartureDate, 1);
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
    destroyOrdList(((Airport *) airport)->flightsByDepartureDate, free);
    free(((Airport *) airport)->name);
}
