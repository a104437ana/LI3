#include <stdio.h>
#include "flightsManager.h"

struct flightsManager {
    Hashtable *flights;
};

FlightsManager *createFlightsCatalog(int size) {
    FlightsManager *flightsManager = malloc(sizeof(FlightsManager));
    flightsManager->flights = createHashtable(size);
    return flightsManager;
}

void addFlightToCatalog(FlightsManager *flightsManager, Flight *flight, unsigned int key) {
    addHashtable(flightsManager->flights, key, flight);
}
//gets

Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key) {
    Flight *flight = (Flight*) getData(flightsManager->flights, key);
    return flight;
}

Hashtable *getHashtableFlightCatalog(FlightsManager *flightsManager) {
    return flightsManager->flights;
}
