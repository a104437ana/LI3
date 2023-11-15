#ifndef _FLIGHTS_MANAGER_
#define _FLIGHTS_MANAGER_

#include "flight.h"
#include "hashtable.h"
#include "usersManager.h"
//ligar lista de passageiros a lista de flights de um user
typedef struct flightsManager FlightsManager;

FlightsManager *createFlightsCatalog(int size);
void addFlightToCatalog(FlightsManager *flightsManager, Flight *flight, unsigned int key);
void addPassengerToCatalog(FlightsManager *flightsManager, int flightKey, UsersManager *usersManager, int userKey, char *flightId, char *userId);
//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key, char *id);
Hashtable *getHashtableFlightCatalog(FlightsManager *flightsManager);

void printFlights(FlightsManager *flightsManager);

void destroyFlightsCatalog(FlightsManager *flightsManager);

#endif