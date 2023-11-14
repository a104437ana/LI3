#ifndef _FLIGHTS_MANAGER_
#define _FLIGHTS_MANAGER_

#include "flight.h"
#include "hashtable.h"
//ligar lista de passageiros a lista de flights de um user
typedef struct flightsManager FlightsManager;

FlightsManager *createFlightsCatalog(int size);
void addFlightToCatalog(FlightsManager *flightsManager, Flight *flight, unsigned int key);
void addPassengerToCatalog(FlightsManager *flightsManager, int flightKey, UsersManager *usersManager, int userKey);
//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key);
Hashtable *getHashtableFlightCatalog(FlightsManager *flightsManager);

#endif