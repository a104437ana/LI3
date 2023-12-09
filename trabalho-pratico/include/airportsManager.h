#ifndef _AIRPORTS_MANAGER_
#define _AIRPORTS_MANAGER_

#include "airport.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct airportsManager AirportsManager;
//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size);
//adiciona um hotel ao catálogo de aeroportos
void addAirportToCatalog(AirportsManager *airportsManager, Airport *airport, Flight *flight, unsigned int key);
//ordena o catálogo de aeroportos
void sortAirportCatalog(AirportsManager *airportsManager);

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, unsigned int key, char *id);
Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager);

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager);

#endif