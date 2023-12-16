#ifndef _AIRPORTS_MANAGER_
#define _AIRPORTS_MANAGER_

#include "airport.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct airportsManager AirportsManager;
//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size);
//atualiza o catálogo de aeroportos
void updateAirportCatalog(char *id, char *id_flight, AirportsManager *airportsCatalog);

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, unsigned int key, char *id);
Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager);

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager);

#endif