#ifndef _FLIGHTS_MANAGER_
#define _FLIGHTS_MANAGER_

#include "flight.h"
#include "airportsManager.h"
#include "usersManager.h"
#include "hashtable.h"

typedef struct flightsManager FlightsManager;
//cria um catalogo de voos
FlightsManager *createFlightsCatalog(int size);
//adiciona um voo ao catalogo de voos
void addFlightToCatalog(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog);
//adiciona um utilizador a um certo voo no catalogo dos voos
void addPassengerToCatalog(FlightsManager *flightsManager, int flightKey, UsersManager *usersManager, int userKey, char *flightId, char *userId);

//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key, char *id);
int existsFlight (FlightsManager* flightsManager,char* id);
Hashtable *getHashtableFlightsCatalog(FlightsManager *flightsManager);

//imprime todos os voos, para efeitos de teste
void printFlights(FlightsManager *flightsManager);

//liberta espaço em memória do catalogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager);

#endif