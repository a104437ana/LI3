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
void updateAirportCatalog(int delay, char *id_origin, char *id_destination, int id_flight, AirportsManager *airportsCatalog);

void sortAirports (AirportsManager* airportsManager);
void sortAirportFlightsByDepartureDate_airportsCatalog(char *id, AirportsManager *airportsCatalog, void (*sortFunction)(void*,void*), void *lookup);
int compareDelays (void *pointer1, void *pointer2, void *lookup);
void airport_catalog_compute_Q5(char* airport,Date* begin,Date* end,AirportsManager* airports, QueryResult* result, HashtableInt *lookup);
void airport_calalog_compute_Q7 (int n, AirportsManager *airports, QueryResult* result);
//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager);

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, char *id);
Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager);
int getAirportListSize_airportsCatalog(char *id, AirportsManager *airportsCatalog);
int getAirportPassengersYear_airportsCatalog(int year, char *id, int (*compareFunction)(int,int,void*), int equal, void *lookup, int (*getFunction)(int,void*), AirportsManager *airportsCatalog);
char *getNextAirportId(int index, AirportsManager *airportsCatalog);
int getNumberAirports_airportsCatalog(AirportsManager *airportsCatalog);
int getNumberMedianAirports(AirportsManager *airportsCatalog);

#endif