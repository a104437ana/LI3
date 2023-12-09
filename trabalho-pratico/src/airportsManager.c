#include <stdio.h>
#include <stdlib.h>
#include "airportsManager.h"
#include "hashtable.h"

struct airportsManager {
    Hashtable *airports;
};

//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size) {
    AirportsManager *airportsManager = malloc(sizeof(AirportsManager));
    airportsManager->airports = createHashtable(size);
    return airportsManager;
}

//adiciona um hotel ao catálogo de aeroportos
void addAirportToCatalog(AirportsManager *airportsManager, Airport *airport, Flight *flight, unsigned int key) {
    addFlightToAirport(airport, flight);
    addHashtable(airportsManager->airports, key, airport, getAirportId(airport));
}

//ordena o catálogo de aeroportos
void sortAirportCatalog(AirportsManager *airportsManager) {
    sortOrdlistHashtable(airportsManager->airports, sortAirportFlightsByDepartureDate);
}

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, unsigned int key, char *id) {
    Airport *airport = (Airport *) getData(airportsManager->airports, key, id);
    return airport;
}

Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager) {
    return airportsManager->airports;
}

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager) {
    if (airportsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(airportsManager->airports, destroyAirport); //liberta a hashtable de aeroportos
    free(airportsManager);
}
