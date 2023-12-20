#include <stdio.h>
#include <stdlib.h>
#include "flightsManager.h"
#include "airportsManager.h"
#include "hashtable.h"

struct flightsManager {
    Hashtable *flights;
};
//função que cria um catálogo de voos
FlightsManager *createFlightsCatalog(int size) {
    FlightsManager *flightsManager = malloc(sizeof(FlightsManager)); //aloca espaço para o catálogo
    flightsManager->flights = createHashtable(size); //cria uma hashtable para o catálogo
    return flightsManager;
}
//função que adiciona um voo ao catálogo de voos
void addFlightToCatalog(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog) {
    int key = hashFunction(id);
    Flight *flight = createFlight(id, airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival);
    flightsCatalog->flights = addHashtable(flightsCatalog->flights, key, flight, id);
}
//função que adiciona um utilizador à lista de passageiros de um certo voo no catálogo
//e adiciona esse voo à lista de voos do utilizador
void addPassengerToCatalog(FlightsManager *flightsManager, int flightKey, UsersManager *usersManager, int userKey, char *flightId, char *userId) {
    Flight *flight = getFlightCatalog(flightsManager, flightKey, flightId);
    User *user = getUserCatalog(usersManager, userKey, userId);
    addUserToFlight(flight, user); //adiciona o utilizador à lista de passageiros do voo
    addFlightToUser(user, flight); //adiciona o voo à lista de voos do utilizador
}

//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned int key, char *id) {
    Flight *flight = (Flight*) getData(flightsManager->flights, key, id);
    return flight;
}

int existsFlight (FlightsManager* flightsManager,char* id) {
    int key = hashFunction(id);
    HashtableNode *flight = searchHashtable(flightsManager->flights, key, id);
    if (flight == NULL) return 0;
    return 1;
}

Hashtable *getHashtableFlightsCatalog(FlightsManager *flightsManager) {
    return flightsManager->flights;
}

//função que imprime um voo, para efeitos de teste
void printFunctionFlight(void *data) {
//    int passengers = getOrdListSize(getPassengers((Flight *) data));
    char *date = dateToString(getFlightScheduleDeparture((Flight *) data));
//    char *flightId = getFlightId((Flight *) data);
    printf(" %20s)", date);
    free(date);
//    free(flightId);
}
//função que imprime todos os voos do catálogo, para efeitos de teste
void printFlights(FlightsManager *flightsManager) {
    printTable(flightsManager->flights, printFunctionFlight);
    printHashtableUsage(flightsManager->flights);
}

//função que liberta o espaço em memória alocado pelo catálogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager) {
    if (flightsManager == NULL) return; //se não exitir o catálogo
    destroyHashtable(flightsManager->flights, destroyFlight); //liberta a hashtable
    free(flightsManager);
}

//queries
void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, Results* results) {
    Flight* flight = getData(flightsManager->flights,hashFunction(id),id);
    if (flight == NULL) {
        setQ1type(results,0);
    }
    else {
        setQ1type(results,2);
        char* airline = getFlightAirline(flight);
        char* plane_model = getFlightAirplane(flight);
        char* origin = getFlightOrigin(flight);
        char* destination = getFlightDestination(flight);
        Date* schedule_departure_date = getFlightScheduleDeparture(flight);
        Date* schedule_arrival_date = getFlightScheduleArrival(flight);
        int number_of_passengers = getNumberPassengers(flight);
        double delay = getDelay(flight);
        setAirlineQ1(results,airline);
        setPlaneModelQ1(results,plane_model);
        setOriginQ1(results,origin);
        setDestQ1(results,destination);
        setSheduleDepartureQ1(results,schedule_departure_date);
        setSheduleArrivalQ1(results,schedule_arrival_date);
        setNpassengersQ1(results,number_of_passengers);
        setDelayQ1(results,delay);
        free(origin);
        free(destination);
    }
}
