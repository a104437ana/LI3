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
int addFlightToCatalog(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog) {
    int key = hashFunction(id);
    Flight *flight = createFlight(id, airline, airplane, origin, destination, scheduleDeparture, scheduleArrival, realDeparture, realArrival);
    flightsCatalog->flights = addHashtable(flightsCatalog->flights, key, flight, id);
    return getDelay(flight);
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
void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result) {
    Flight* flight = getData(flightsManager->flights,hashFunction(id),id);
    if (flight == NULL) {
        return;
    }
    else {
        setNumberResults(result,1);
        setNumberFieldsQ(result, 0, 8);
        char* airline = getFlightAirline(flight); char * field0 = strdup("airline");
        char* plane_model = getFlightAirplane(flight); char * field1 = strdup("plane_model");
        char* origin = getFlightOrigin(flight); char * field2 = strdup("origin");
        char* destination = getFlightDestination(flight); char * field3 = strdup("destination");
        Date* schedule_departure_date = getFlightScheduleDeparture(flight);
        Date* schedule_arrival_date = getFlightScheduleArrival(flight);
        char * dep = dateToStringNoHours(schedule_departure_date); char * field4 = strdup("schedule_departure_date");
        char * arr = dateToStringNoHours(schedule_arrival_date); char * field5 = strdup("schedule_arrival_date");
        int number_of_passengers = getNumberPassengers(flight);
        char * nPassengersS= malloc(sizeof(char)*5);;
        sprintf(nPassengersS, "%d", number_of_passengers); char * field6 = strdup("passengers");
        double delay = getDelay(flight);
        char * delayS = malloc(sizeof(char)*15);
        sprintf(delayS, "%.3f", delay); char * field7 = strdup("delay");

        setFieldQ(result, 0, 0, field0, airline);
        setFieldQ(result, 0, 1, field1, plane_model); 
        setFieldQ(result, 0, 2, field2, origin); 
        setFieldQ(result, 0, 3, field3, destination);
        setFieldQ(result, 0, 4, field4, dep); 
        setFieldQ(result, 0, 5, field5, arr); 
        setFieldQ(result, 0, 6, field6, nPassengersS); 
        setFieldQ(result, 0, 7, field7, delayS); 
        
        free(airline); free(plane_model); free(origin); free(destination); destroyDate(schedule_departure_date); destroyDate(schedule_arrival_date); free(dep); free(arr); free(nPassengersS); free(delayS);
        free(field0); free(field1); free(field2); free(field3); free(field4); free(field5); free(field6); free(field7);
    }
}
