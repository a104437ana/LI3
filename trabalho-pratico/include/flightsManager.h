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
int addFlightToCatalog(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog);
//adiciona o utilizador à lista de passageiros do voo
void addUserToFlight(char *id_flight, char *id_user, FlightsManager *flightsCatalog);

//liberta espaço em memória do catalogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager);

void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result);

//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key, char *id);
int existsFlight (FlightsManager* flightsManager,char* id);
Hashtable *getHashtableFlightsCatalog(FlightsManager *flightsManager);
int getSDFlight(int time, char *id, FlightsManager *flightsCatalog);
char *getSFlightDate(char *id, FlightsManager *flightsCatalog);
#endif