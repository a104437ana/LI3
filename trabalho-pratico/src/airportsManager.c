#include <stdio.h>
#include <stdlib.h>
#include "airportsManager.h"
#include "hashtable.h"

struct airportsManager {
    Hashtable *airports;
    OrdList* airportsByMedianOfDelays;
};

//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size) {
    AirportsManager *airportsManager = malloc(sizeof(AirportsManager));
    airportsManager->airports = createHashtable(size);
    airportsManager->airportsByMedianOfDelays = createOrdList(30);
    return airportsManager;
}

//atualiza o catálogo de aeroportos
void updateAirportCatalog(int delay, char *id, char *id_flight, AirportsManager *airportsCatalog) {
    unsigned int key = hashFunction(id);
    int existsAirport = existsData(airportsCatalog->airports, key, id); //verifica se o aeroporto já existe no catálogo de aeroportos
    Airport *airport;
    if (existsAirport == 0) { //caso não exista cria um novo aeroporto
        airport = createAirport(id);
        airportsCatalog->airports = addHashtable(airportsCatalog->airports, key, airport, id); //adiciona o aeroporto ao catálogo dos aeroportos
        addOrdList(airportsCatalog->airportsByMedianOfDelays,airport);
    } else //caso já exista
        airport = (Airport*) getData(airportsCatalog->airports, key, id); //obtem apontador para o aeroporto do catálogo dos aeroporotos
    addFlightToAirport(airport, id_flight); //adiciona o apontador do voo aos voos do aeroporto
    addDelayToAirport(airport,delay);
}

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, unsigned int key, char *id) {
    Airport *airport = (Airport *) getData(airportsManager->airports, key, id);
    return airport;
}

Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager) {
    return airportsManager->airports;
}
void sortAirports (AirportsManager* airportsManager) {
    int n = getOrdListSize(airportsManager->airportsByMedianOfDelays);
    for (int i = 0; i < n; i++) {
        Airport* airport = getDataOrdList(airportsManager->airportsByMedianOfDelays,i);
        sortAirportDelays (airport);
    }
}

int compareDelays (void *pointer1, void *pointer2) {
    int result;
    Airport* airport1 = (Airport*) pointer1;
    Airport* airport2 = (Airport*) pointer2;
    double median1 = getAirportMedian(airport1);
    double median2 = getAirportMedian(airport2);
    if (median1 > median2) result = -1;
    if (median1 < median2) result = 1;
    if (median1 == median2) {
        char* name1 = getAirportId(airport1);
        char* name2 = getAirportId(airport2);
        result = strcoll(name1,name2);
        free(name1);
        free(name2);
    }
    return result;
}

void airport_calalog_compute_Q7 (int n, AirportsManager *airports, Results* results) {
    clearResultQ7(results);
    setResultQ7 (results,n);
    sortAirports(airports);
    int w = getOrdListSize(airports->airportsByMedianOfDelays);
    quickSort(airports->airportsByMedianOfDelays,0,w-1,compareDelays,0.1);
    for(int i = 0; i<n && i<w; i++) {
        Airport* airport = getDataOrdList(airports->airportsByMedianOfDelays,i);
        char* name = getAirportId(airport);
        double median = getAirportMedian(airport);
        setNameMedianQ7(results,i,name,median);
        free(name);
    }
}

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager) {
    if (airportsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(airportsManager->airports, destroyAirport); //liberta a hashtable de aeroportos
    destroyOnlyOrdList(airportsManager->airportsByMedianOfDelays);
    free(airportsManager);
}

