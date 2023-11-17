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

int existsFlight (FlightsManager* flightsManager,char* id) {
    int key = hashFunction(id);
    HashtableNode *flight = searchHashtable(flightsManager->flights, key, id);
    if (flight == NULL) return 0;
    return 1;
}

Hashtable *getHashtableFlightCatalog(FlightsManager *flightsManager) {
    return flightsManager->flights;
}

void printFunctionFlight(void *data) {
    int passengers = getOrdListSize(getPassengers((Flight *) data));
//    char *flightId = getFlightId((Flight *) data);
    printf(" %8d)", passengers);
//    free(flightId);
}

void printFlights(FlightsManager *flightsManager) {
    printTable(flightsManager->flights, printFunctionFlight);
    printHashtableUsage(flightsManager->flights);
}

void destroyFlightsCatalog(FlightsManager *flightsManager) {
    if (flightsManager == NULL) return;
    destroyHashtable(flightsManager->flights, destroyFlight);
    free(flightsManager);
}
