#include <stdio.h>
#include <stdlib.h>
#include "airportsManager.h"
#include "hashtable.h"
#include "flight.h"

struct airportsManager {
    Hashtable *airports;
    OrdList* airportsByMedianOfDelays;
};

//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size) {
    AirportsManager *airportsManager = malloc(sizeof(AirportsManager));
    airportsManager->airports = createHashtable(size);
    airportsManager->airportsByMedianOfDelays = createOrdList();
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
    addFlightToAirport(airport, id_flight); //adiciona o voo aos voos do aeroporto
    addDelayToAirport(airport,delay);
}

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, char *id) {
    int key = hashFunction(id);
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
        result = strcmp(name1,name2);
        free(name1);
        free(name2);
    }
    return result;
}

//ordena voos por data
void radixSortFlightDate(OrdList *list, void *lookupTable) {
    radixSort(list, getFlightScheduleDepartureSeconds, lookupTable, 60, 0);
    radixSort(list, getFlightScheduleDepartureMinutes, lookupTable, 60, 0);
    radixSort(list, getFlightScheduleDepartureHours, lookupTable, 24, 0);
    radixSort(list, getFlightScheduleDepartureDay, lookupTable, 31, 0);
    radixSort(list, getFlightScheduleDepartureMonth, lookupTable, 12, 0);
    radixSort(list, getFlightScheduleDepartureYear, lookupTable, N_YEARS, BEGIN_YEAR);
}
//função que compara os ids de dois voos
int compareFlightsIds(void *id1, void *id2) {
    return strcoll(id1, id2);
}
//ordena os voos do aeroporto
void sortAirportFlightsByDepartureDate(Airport *airport, Hashtable *airports) {
    OrdList *list = getAirportOrdList(airport);
    if (!isOrdered(list)) {
        quickSort(list, 0, getOrdListSize(list)-1, compareFlightsIds, 0); //ordena por ids
        reverseOrdList(list);
        radixSortFlightDate(list, airports); //ordena por datas
        setOrdListOrd(list, 1);
    }
}
void sortAirportFlightsByDepartureDate_airportsCatalog(char *id, AirportsManager *airportsCatalog, Hashtable *lookup) {
    int key = hashFunction(id);
    Airport *airport = getData(airportsCatalog->airports, key, id);
    sortAirportFlightsByDepartureDate(airport, lookup);
}

void airport_catalog_compute_Q5(char* id,Date* begin,Date* end,AirportsManager* airports, QueryResult* result,Hashtable* lookup) {
    Airport* airport = getData(airports->airports,hashFunction(id),id);
    if (airport != NULL) {   
        sortAirportFlightsByDepartureDate(airport,lookup);
        OrdList* airportsByDate = getAirportOrdList(airport);
        int size = getOrdListSize(airportsByDate);
        int i = 0;
        char* id_flight;
        Flight* flight;
        while (i < size) {
            id_flight = getDataOrdList(airportsByDate,i);
            flight = getData(lookup,hashFunction(id_flight),id_flight);
            Date * date = getFlightScheduleDeparture(flight);
            if (compareDates(begin,date) >= 0) {
                destroyDate(date);
                break;
            }
            else {
                i++;
                destroyDate(date);
            }
        }
        int j = 0;
        while (i < size) {
            id_flight = getDataOrdList(airportsByDate,i);
            flight = getData(lookup,hashFunction(id_flight),id_flight);
            Date * date = getFlightScheduleDeparture(flight);
            if (compareDates(end,date) <= 0) {
                addResult(result, j);
                setNumberFieldsQ(result,j, 5);
                char* string_date = dateToString(date);
                char* destination = getFlightDestination(flight);
                toUpperS(destination);
                char* airline = getFlightAirline(flight);
                char* plane_model = getFlightAirplane(flight);
                char* field0 = strdup("id");
                char* field1 = strdup("schedule_departure_date");
                char* field2 = strdup("destination");
                char* field3 = strdup("airline");
                char* field4 = strdup("plane_model");
                i++;
                setFieldQ(result,j,0,field0,id_flight);
                setFieldQ(result,j,1,field1,string_date);
                setFieldQ(result,j,2,field2,destination);
                setFieldQ(result,j,3,field3,airline);
                setFieldQ(result,j,4,field4,plane_model);
                free(field0); free(field1); free(field2); free(field3); free(field4);
                free(string_date); free(destination); free(airline); free(plane_model);
                j++;
                destroyDate(date);
            }
            else {
                destroyDate(date);
                break;
            }
        }
        reverseResults(result);
    }
}

void airport_calalog_compute_Q7 (int n, AirportsManager *airports, QueryResult* result) {
    sortAirports(airports);
    int w = getOrdListSize(airports->airportsByMedianOfDelays);
    if (w<n) setNumberResults (result,w); else setNumberResults (result, n);
    quickSort(airports->airportsByMedianOfDelays,0,w-1,compareDelays,0);
    for(int i = 0; i<n && i<w; i++) {
        Airport* airport = getDataOrdList(airports->airportsByMedianOfDelays,i);
        setNumberFieldsQ(result,i, 2);
        char* name = getAirportId(airport); char * field0 = strdup("name");
        int median = getAirportMedian(airport);
        char * medianS = malloc(sizeof(char)*10);
        sprintf(medianS, "%d", median); char * field1 = strdup("median");

        setFieldQ(result, i, 0, field0, name); 
        setFieldQ(result, i, 1, field1, medianS); 
        
        free(name); free(medianS);
        free(field0); free(field1);
    }
}

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager) {
    if (airportsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(airportsManager->airports, destroyAirport); //liberta a hashtable de aeroportos
    destroyOnlyOrdList(airportsManager->airportsByMedianOfDelays);
    free(airportsManager);
}

//gets
int getAirportListSize_airportsCatalog(char *id, AirportsManager *airportsCatalog) {
    int key = hashFunction(id);
    Airport *airport = getData(airportsCatalog->airports, key, id);
    return getAirportListSize(airport);
}

int getAirportPassengersYear_airportsCatalog(int year, char *id, int (*compareFunction)(void*,void*,void*), int equal, void *lookup, int (*getFunction)(void*,void*), AirportsManager *airportsCatalog) {
    int key = hashFunction(id);
    Airport *airport = getData(airportsCatalog->airports, key, id);
    return getAirportPassengersYear(year, airport, compareFunction, equal, lookup, getFunction);
}
char *getNextAirportId(char *id, AirportsManager *airportsCatalog) {
    int key = hashFunction(id);
    char *nextId = (char *) getNextData(airportsCatalog->airports, key, id);
    return strdup(nextId);
}
int getNumberAirports_airportsCatalog(AirportsManager *airportsCatalog) {
    return getHashtableUsed(airportsCatalog->airports);
}

