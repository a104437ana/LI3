#include <stdio.h>
#include <stdlib.h>
#include "airportsManager.h"
#include "hashtable.h"

struct airportsManager {
    Hashtable *airports;
};

//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size) {
    AirportsManager *airportsManager = malloc(sizeof(AirportsManager));
    airportsManager->airports = createHashtable(size);
    return airportsManager;
}

//atualiza o catálogo de aeroportos
void updateAirportCatalog(char *id, char *id_flight, AirportsManager *airportsCatalog) {
    unsigned int key = hashFunction(id);
    int existsAirport = existsData(airportsCatalog->airports, key, id); //verifica se o aeroporto já existe no catálogo de aeroportos
    Airport *airport;
    if (existsAirport == 0) { //caso não exista cria um novo aeroporto
        airport = createAirport(id);
        addHashtable(airportsCatalog->airports, key, airport, id); //adiciona o aeroporto ao catálogo dos aeroportos
    } else //caso já exista
        airport = (Airport*) getData(airportsCatalog->airports, key, id); //obtem apontador para o aeroporto do catálogo dos aeroporotos
    addFlightToAirport(airport, id_flight); //adiciona o apontador do voo aos voos do aeroporto
}

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, unsigned int key, char *id) {
    Airport *airport = (Airport *) getData(airportsManager->airports, key, id);
    return airport;
}

Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager) {
    return airportsManager->airports;
}

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager) {
    if (airportsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(airportsManager->airports, destroyAirport); //liberta a hashtable de aeroportos
    free(airportsManager);
}
