#include <stdio.h>
#include <stdlib.h>
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
    addHashtable(flightsManager->flights, key, flight, getFlightId(flight));
}

void addPassengerToCatalog(FlightsManager *flightsManager, int flightKey, UsersManager *usersManager, int userKey, char *flightId, char *userId) {
    Flight *flight = getFlightCatalog(flightsManager, flightKey, flightId);
    User *user = getUserCatalog(usersManager, userKey, userId);
    addUserToFlight(flight, user);
    addFlightToUser(user, flight);
}
//gets

Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key, char *id) {
    Flight *flight = (Flight*) getData(flightsManager->flights, key, id);
    return flight;
}

Hashtable *getHashtableFlightCatalog(FlightsManager *flightsManager) {
    return flightsManager->flights;
}

void printFunctionFlight(void *data) {
    char *flightId = getFlightId((Flight *) data);
    printf(" %8s)", flightId);
    free(flightId);
}

void printFlights(FlightsManager *flightsManager) {
    printTable(flightsManager->flights, printFunctionFlight);
    printHashtableUsage(flightsManager->flights);
}
