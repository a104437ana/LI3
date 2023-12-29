#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"
#include "airport.h"
#include "airportsManager.h"
#include "orderedList.h"

struct flight {
    char *id;
    char *airline;
    char *airplane;
    char origin[4];
    char destination[4];
    Date *scheduleDeparture;
    Date *scheduleArrival;
    Date *realDeparture;
    Date *realArrival;
    OrdList *passengers; //não necessário apenas número de passageiros
};
//função que cria um novo voo
Flight *createFlight(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival) {
    Flight *flight = malloc(sizeof(Flight));
    flight->id = strdup(id);
    flight->airline = strdup(airline);
    flight->airplane = strdup(airplane);
    memcpy(flight->origin, origin, 4);
    memcpy(flight->destination, destination, 4);
    Date *scheduleDepartureDate = string_to_date_hours(scheduleDeparture);
    Date *scheduleArrivalDate = string_to_date_hours(scheduleArrival);
    Date *realDepartureDate = string_to_date_hours(realDeparture);
    Date *realArrivalDate = string_to_date_hours(realArrival);
    flight->scheduleDeparture = scheduleDepartureDate;
    flight->scheduleArrival = scheduleArrivalDate;
    flight->realDeparture = realDepartureDate;
    flight->realArrival = realArrivalDate;
    flight->passengers = createOrdList(); //cria uma lista de passageiros desse voo

    return flight;
}
//função que adiciona um utilizador à lista de passageiros de um voo
void addUserToFlight(Flight *flight, void *user) {
    addOrdList(flight->passengers, user);
}

//gets
char *getFlightAirline(Flight *flight) {
    return flight->airline; //falta encapsulamento
}

char *getFlightAirplane(Flight *flight) {
    return flight->airplane; //falta encapsulamento
}

char *getFlightOrigin(Flight *flight) {
    char *origin = malloc(sizeof(char) * 4);
    memcpy(origin, flight->origin, 4);
    return origin;
}

char *getFlightDestination(Flight *flight) {
    char *destination = malloc(sizeof(char) * 4);
    memcpy(destination, flight->destination, 4);
    return destination;
}

Date *getFlightScheduleDeparture(Flight *flight) {
    return flight->scheduleDeparture;
}

Date *getFlightScheduleArrival(Flight *flight) {
    return flight->scheduleArrival;
}

Date *getFlightRealDeparture(Flight *flight) {
    return flight->realDeparture;
}

Date *getFlightRealArrival(Flight *flight) {
    return flight->realArrival;
}

int getFlightScheduleDepartureDay(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Flight *flight = getData(lookupTable, key, id);
    return getDay(flight->scheduleDeparture);
}

int getFlightScheduleDepartureMonth(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Flight *flight = getData(lookupTable, key, id);
    return getMonth(flight->scheduleDeparture);
}

int getFlightScheduleDepartureYear(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Flight *flight = getData(lookupTable, key, id);
    return getYear(flight->scheduleDeparture);
}

int getFlightScheduleDepartureSeconds(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Flight *flight = getData(lookupTable, key, id);
    return getSeconds(flight->scheduleDeparture);
}

int getFlightScheduleDepartureMinutes(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Flight *flight = getData(lookupTable, key, id);
    return getMinutes(flight->scheduleDeparture);
}

int getFlightScheduleDepartureHours(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Flight *flight = getData(lookupTable, key, id);
    return getHours(flight->scheduleDeparture);
}
/*
char *getFlightPilot(Flight *flight) {
    return flight->pilot;
}

char *getFlightCopilot(Flight *flight) {
    return flight->copilot;
}

char *getFlightNotes(Flight *flight) {
    return flight->notes;
}
*/
char *getFlightId(Flight *flight) {
    return flight->id;
}

OrdList * getPassengers(Flight* flight){
    return flight->passengers;
}

//retorna o número de passageiros num voo
int getNumberPassengers(Flight* flight){
    OrdList* passengers = getPassengers(flight);
    return(getOrdListSize(passengers));
}

//calcula o atrado de um voo em segundos
int getDelay(Flight* flight){
     Date* scheduleDep = getFlightScheduleDeparture(flight);
     Date* realDep = getFlightRealDeparture(flight);
     int res = ((getDay(realDep)-getDay(scheduleDep))*86400+(getHours(realDep))-(getHours(scheduleDep)))*3600 + ((getMinutes(realDep))-(getMinutes(scheduleDep)))*60 +((getSeconds(realDep))-(getSeconds(scheduleDep)));
     return res;
}

//sets
void setFlightAirline(Flight *flight, char *airline) {
    char *oldAirline = flight->airline;
    flight->airline = strdup(airline);
    free(oldAirline);
}

void setFlightAirplane(Flight *flight, char *airplane) {
    char *oldAirplane = flight->airplane;
    flight->airplane = strdup(airplane);
    free(oldAirplane);
}
/*
void setFlightTotalSeats(Flight *flight, int totalSeats) {
    flight->totalSeats = totalSeats;
}
*/
void setFlightOrigin(Flight *flight, char origin[4]) {
    flight->origin[0] = origin[0];
    flight->origin[1] = origin[1];
    flight->origin[2] = origin[2];
}

void setFlightDestination(Flight *flight, char destination[4]) {
    flight->destination[0] = destination[0];
    flight->destination[1] = destination[1];
    flight->destination[2] = destination[2];
}

void setFlightScheduleDeparture(Flight *flight, Date *scheduleDeparture) {
    flight->scheduleDeparture = scheduleDeparture;
}

void setFlightScheduleArrival(Flight *flight, Date *scheduleArrival) {
    flight->scheduleArrival = scheduleArrival;
}

void setFlightRealDeparture(Flight *flight, Date *realDeparture) {
    flight->realDeparture = realDeparture;
}

void setFlightRealArrival(Flight *flight, Date *realArrival) {
    flight->realArrival = realArrival;
}
/*
void setFlightPilot(Flight *flight, char *pilot) {
    char *oldPilot = flight->pilot;
    flight->pilot = strdup(pilot);
    free(oldPilot);
}

void setFlightCopilot(Flight *flight, char *copilot) {
    char *oldCopilot = flight->copilot;
    flight->copilot = strdup(copilot);
    free(oldCopilot);
}

void setFlightNotes(Flight *flight, char *notes) {
    char *oldNotes = flight->notes;
    flight->notes = strdup(notes);
    free(oldNotes);
}
*/
//funcção que liberta o espaço em memória alocado por um voo
void destroyFlight(void *flight) {
    if (flight == NULL) return; //se o voo não existir
    destroyDate(((Flight *) flight)->scheduleDeparture); //liberta as datas
    destroyDate(((Flight *) flight)->scheduleArrival);
    destroyDate(((Flight *) flight)->realDeparture);
    destroyDate(((Flight *) flight)->realArrival);
    //free(((Flight *) flight)->notes);
    //free(((Flight *) flight)->copilot);
    //free(((Flight *) flight)->pilot);
//    free(((Flight *) flight)->destination);
//    free(((Flight *) flight)->origin);
    free(((Flight *) flight)->airplane); //liberta as strings
    free(((Flight *) flight)->airline);
    free(((Flight *) flight)->id);
    destroyOnlyOrdList(((Flight *) flight)->passengers); //liberta a lista de passageiros
    free(flight);
}
