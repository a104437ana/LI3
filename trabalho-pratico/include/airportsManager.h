#ifndef _AIRPORTS_MANAGER_
#define _AIRPORTS_MANAGER_

#include "airport.h"
#include "hashtable.h"
#include "flight.h"
#include "orderedList.h"
#include "results.h"

typedef struct airportsManager AirportsManager;
//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size);
//atualiza o catálogo de aeroportos
void updateAirportCatalog(int delay, char *id, char *id_flight, AirportsManager *airportsCatalog);

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, unsigned int key, char *id);
Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager);
void sortAirports (AirportsManager* airportsManager);
int compareDelays (void *pointer1, void *pointer2);
void airport_catalog_compute_Q5(char* airport,Date* begin,Date* end,AirportsManager* airports, QueryResult* result,Hashtable* lookup);
void airport_calalog_compute_Q7 (int n, AirportsManager *airports, QueryResult* result);
//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager);

#endif