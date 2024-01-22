#include <stdio.h>
#include <stdlib.h>
#include "airportsManager.h"
#include "hashtable.h"
#include "flight.h"

struct airportsManager {
    Hashtable *airports;
    OrdList* airportsByMedianOfDelays;
    int size_delays;
};

//cria um novo catálogo de aeroportos
AirportsManager *createAirportsCatalog(int size) {
    AirportsManager *airportsManager = malloc(sizeof(AirportsManager));
    airportsManager->airports = createHashtable(size, hashString, strcmpVoid, strdupVoid, destroyAirport);
    airportsManager->airportsByMedianOfDelays = createOrdList();
    airportsManager->size_delays = 0;
    return airportsManager;
}

//atualiza o catálogo de aeroportos
void updateAirportCatalog(int delay, char *id_origin, char *id_destination, int id_flight, AirportsManager *airportsCatalog) {
    int existsAirportOrigin = existsData(airportsCatalog->airports, id_origin); //verifica se o aeroporto já existe no catálogo de aeroportos
    int existsAirportDestination = existsData(airportsCatalog->airports, id_destination); //verifica se o aeroporto já existe no catálogo de aeroportos
    Airport *airport_origin;
    Airport *airport_destination;
    if (existsAirportOrigin == 0) { //caso não exista cria um novo aeroporto
        airport_origin = createAirport(id_origin);
        airportsCatalog->airports = addHashtable(airportsCatalog->airports, airport_origin, id_origin); //adiciona o aeroporto ao catálogo dos aeroportos
        addOrdList(airportsCatalog->airportsByMedianOfDelays,airport_origin);
    } else //caso já exista
        airport_origin = (Airport*) getData(airportsCatalog->airports, id_origin); //obtem apontador para o aeroporto do catálogo dos aeroporotos
    if (existsAirportDestination == 0) { //caso não exista cria um novo aeroporto
        airport_destination = createAirport(id_destination);
        airportsCatalog->airports = addHashtable(airportsCatalog->airports, airport_destination, id_destination); //adiciona o aeroporto ao catálogo dos aeroportos
        addOrdList(airportsCatalog->airportsByMedianOfDelays,airport_destination);
    } else //caso já exista
        airport_destination = (Airport*) getData(airportsCatalog->airports, id_destination); //obtem apontador para o aeroporto do catálogo dos aeroporotos
    addFlightToAirport(airport_origin, id_flight, 1); //adiciona o voo ao aeroporto de origem
    addFlightToAirport(airport_destination, id_flight, 0); //adiciona o voo ao aeroporto de destino
    addDelayToAirport(airport_origin,delay);
}

//gets
Airport *getAirportCatalog(AirportsManager *airportsManager, char *id) {
    Airport *airport = (Airport *) getData(airportsManager->airports, id);
    return airport;
}

Hashtable *getHashtableAirportsCatalog(AirportsManager *airportsManager) {
    return airportsManager->airports;
}
void sortAirports (AirportsManager* airportsCatalog) {
    OrdList *list = airportsCatalog->airportsByMedianOfDelays;
    int n = getOrdListSize(list);
    int delay;
    for (int i = 0; i < n; i++) {
        Airport* airport = getDataOrdList(list,i);
        delay = sortAirportDelays (airport);
        if (delay >= 0) airportsCatalog->size_delays++;
    }
    setOrdListOrd(list, 1);
}

int compareDelays (void *pointer1, void *pointer2, void *lookup) {
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

////ordena voos por data
//void radixSortFlightDate(OrdList *list, void *lookupTable) {
//    radixSort(list, getFlightScheduleDepartureSeconds, lookupTable, 60, 0);
//    radixSort(list, getFlightScheduleDepartureMinutes, lookupTable, 60, 0);
//    radixSort(list, getFlightScheduleDepartureHours, lookupTable, 24, 0);
//    radixSort(list, getFlightScheduleDepartureDay, lookupTable, 31, 0);
//    radixSort(list, getFlightScheduleDepartureMonth, lookupTable, 12, 0);
//    radixSort(list, getFlightScheduleDepartureYear, lookupTable, N_YEARS, BEGIN_YEAR);
//}

void sortAirportFlightsByDepartureDate_airportsCatalog(char *id, AirportsManager *airportsCatalog, void (*sortFunction)(void*,void*), void *lookup) {
    Airport *airport = getData(airportsCatalog->airports, id);
    sortAirportFlightsByDepartureDate_airport(airport, sortFunction, lookup);
}

void airport_catalog_compute_Q5(char* id,Date* begin,Date* end,AirportsManager* airports, QueryResult* result,Hashtable* lookup) {
    toUpperS(id);
    Airport* airport = getData(airports->airports,id);
    if (airport != NULL) {
//        sortAirportFlightsByDepartureDate(airport,lookup);
        OrdList* airportsByDate = getAirportOriginOrdList(airport);
        int size = getOrdListSize(airportsByDate);
        int i = 0;
        int id_flight;
        char *id_flightS;
        Flight* flight;
        while (i < size) {
            id_flight = getValueOrdList(airportsByDate,i);
            flight = getData(lookup,&id_flight);
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
            id_flight = getValueOrdList(airportsByDate,i);
            flight = getData(lookup,&id_flight);
            Date * date = getFlightScheduleDeparture(flight);
            if (compareDates(end,date) <= 0) {
                addResult(result, j);
                setNumberFieldsQ(result,j, 5);
                char* string_date = dateToString(date);
                char* destination = getFlightDestination(flight);
//                toUpperS(destination);
                char* airline = getFlightAirline(flight);
                char* plane_model = getFlightAirplane(flight);
                char* field0 = strdup("id");
                char* field1 = strdup("schedule_departure_date");
                char* field2 = strdup("destination");
                char* field3 = strdup("airline");
                char* field4 = strdup("plane_model");
                i++;
                id_flightS = flightIdToString(id_flight);
                setFieldQ(result,j,0,field0,id_flightS);
                setFieldQ(result,j,1,field1,string_date);
                setFieldQ(result,j,2,field2,destination);
                setFieldQ(result,j,3,field3,airline);
                setFieldQ(result,j,4,field4,plane_model);
                free(field0); free(field1); free(field2); free(field3); free(field4);
                free(string_date); free(destination); free(airline); free(plane_model); free(id_flightS);
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
    if (!isOrdered(airports->airportsByMedianOfDelays))
    sortAirports(airports);
    int w = getOrdListSize(airports->airportsByMedianOfDelays);
    quickSort(airports->airportsByMedianOfDelays,0,w-1,compareDelays,NULL,0);
    w = getNumberMedianAirports(airports);
    if (w<n) setNumberResults (result,w); else setNumberResults (result, n);
    char *field0 = strdup("name");
    char *field1 = strdup("median");
    for(int i = 0; i<n && i<w; i++) {
        Airport* airport = getDataOrdList(airports->airportsByMedianOfDelays,i);
        setNumberFieldsQ(result,i, 2);
        char* name = getAirportId(airport);
        int median = getAirportMedian(airport);
        char * medianS = malloc(sizeof(char)*10);
        sprintf(medianS, "%d", median);

        setFieldQ(result, i, 0, field0, name); 
        setFieldQ(result, i, 1, field1, medianS); 
        
        free(name); free(medianS);
    }
    free(field0); free(field1);
}

//liberta espaço em memória do catálogo de aeroportos
void destroyAirportsCatalog(AirportsManager *airportsManager) {
    if (airportsManager == NULL) return; //se o catálogo não existir
    destroyHashtable(airportsManager->airports); //liberta a hashtable de aeroportos
    destroyOnlyOrdList(airportsManager->airportsByMedianOfDelays);
    free(airportsManager);
}

//gets
int getAirportListSize_airportsCatalog(char *id, AirportsManager *airportsCatalog) {
    Airport *airport = getData(airportsCatalog->airports, id);
    return getAirportListSize(airport);
}

int getAirportPassengersYear_airportsCatalog(int year, char *id, int (*compareFunction)(int,int,void*), int equal, void *lookup, int (*getFunction)(int,void*), AirportsManager *airportsCatalog) {
    Airport *airport = getData(airportsCatalog->airports, id);
    return getAirportPassengersYear(year, airport, compareFunction, equal, lookup, getFunction);
}
char *getNextAirportId(int index, AirportsManager *airportsCatalog) {
    char *nextId = (char *) getDataOrdList(airportsCatalog->airportsByMedianOfDelays, index);
    return strdup(nextId);
}
int getNumberAirports_airportsCatalog(AirportsManager *airportsCatalog) {
    return getOrdListSize(airportsCatalog->airportsByMedianOfDelays);
//    return getHashtableUsed(airportsCatalog->airports);
}
int getNumberMedianAirports(AirportsManager *airportsCatalog) {
    return airportsCatalog->size_delays;
}
