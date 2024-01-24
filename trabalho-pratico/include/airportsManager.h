#ifndef _AIRPORTS_MANAGER_
#define _AIRPORTS_MANAGER_

#include "hashtable.h"
#include "results.h"

typedef struct airportsManager AirportsManager;
//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size);
//atualiza o catálogo de aeroportos
void updateAirportCatalog(int delay, char *id_origin, char *id_destination, unsigned long int id_flight, AirportsManager *airportsCatalog);

//ordena a lista de aeroportos pelo atraso
void sortAirports (AirportsManager* airportsManager);
//ordena a lista de voos de um aeroporto
void sortAirportFlightsByDepartureDate_airportsCatalog(char *id, AirportsManager *airportsCatalog, void (*sortFunction)(void*,void*), void *lookup);

//compara os atrasos de dois aeroportos
int compareDelays (void *pointer1, void *pointer2, void *lookup);

//gets
int getNumberMedianAirports(AirportsManager *airportsCatalog);
int getNumberAirports_airportsCatalog(AirportsManager *airportsCatalog);
int getAirportPassengersYear_airportsCatalog(int year, char *id, int (*compareFunction)(unsigned long int,unsigned long int,void*), int equal, void *lookup, int (*getFunction)(unsigned long int,void*), AirportsManager *airportsCatalog);
char *getNextAirportId(int index, AirportsManager *airportsCatalog);

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager);

//queries
void airport_catalog_compute_Q5(char* airport,Date* begin,Date* end,AirportsManager* airports, QueryResult* result, HashtableInt *lookup);
void airport_calalog_compute_Q7 (int n, AirportsManager *airports, QueryResult* result);

#endif