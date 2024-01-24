#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "flight.h"
#include "passenger.h"
#include "hashtable.h"

struct flight {
    char *airline;
    char *airplane;
    char origin[4];
    char destination[4];
    Date *scheduleDeparture;
    Date *scheduleArrival;
    Date *realDeparture;
    Date *realArrival;
    OrdList *passengers;
};
//função que cria um novo voo
Flight *createFlight(char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival) {
    Flight *flight = malloc(sizeof(Flight));
    flight->airline = strdup(airline);
    flight->airplane = strdup(airplane);
    memcpy(flight->origin, origin, 4);
    memcpy(flight->destination, destination, 4);
    flight->scheduleDeparture = string_to_date_hours(scheduleDeparture);
    flight->scheduleArrival = string_to_date_hours(scheduleArrival);
    flight->realDeparture = string_to_date_hours(realDeparture);
    flight->realArrival = string_to_date_hours(realArrival);
//    stringToDateHours(&(flight->scheduleDeparture), scheduleDeparture);
//    stringToDateHours(&(flight->scheduleArrival), scheduleArrival);
//    stringToDateHours(&(flight->realDeparture), realDeparture);
//    stringToDateHours(&(flight->realArrival), realArrival);
    flight->passengers = createOrdList(); //cria uma lista de passageiros desse voo

    return flight;
}
//função que adiciona um utilizador à lista de passageiros de um voo
void addPassengerToFlight(Flight *flight, char *id_user) {
    char* user = strdup(id_user);
    addOrdList(flight->passengers, user);
}

//gets
//strings
char *getFlightAirline(Flight *flight) {
    char * res = strdup(flight->airline);
    return res;
}

char *getFlightAirplane(Flight *flight) {
    char * res = strdup(flight->airplane);
    return res;
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

//datas do voo
Date *getFlightScheduleDeparture(Flight *flight) {
    return dupDate(flight->scheduleDeparture);
}

Date *getFlightScheduleArrival(Flight *flight) {
    return dupDate(flight->scheduleArrival);
}

Date *getFlightRealDeparture(Flight *flight) {
    return dupDate(flight->realDeparture);
}

Date *getFlightRealArrival(Flight *flight) {
    return dupDate(flight->realArrival);
}

int getDepartureDay(void *flight, void *lookup) {
    return getDay((((Flight*)flight)->scheduleDeparture));
}

int getDepartureMonth(void *flight, void *lookup) {
    return getMonth(((Flight*)flight)->scheduleDeparture);
}

int getDepartureYear(void *flight, void *lookup) {
    return getYear(((Flight*)flight)->scheduleDeparture);
}

int getFlightSD(int time, Flight *flight) {
    int res;
    switch (time) {
        case TIME_DAY:
            res = getDay((flight->scheduleDeparture));
            break;
        case TIME_MONTH:
            res = getMonth((flight->scheduleDeparture));
            break;
        case TIME_YEAR:
            res = getYear((flight->scheduleDeparture));
            break;
        case TIME_SECONDS:
            res = getSeconds((flight->scheduleDeparture));
            break;
        case TIME_MINUTES:
            res = getMinutes((flight->scheduleDeparture));
            break;
        case TIME_HOURS:
            res = getHours((flight->scheduleDeparture));
            break;
        default:
            res = 0;
    }
    return res;
}

char *getStringFlightDateNoHours(Flight *flight) {
    return dateToStringNoHours((flight->scheduleDeparture));
}

//passageiros do voo
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
     free(scheduleDep);
     free(realDep);
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

//funcção que liberta o espaço em memória alocado por um voo
void destroyFlight(void *flight) {
    if (flight == NULL) return; //se o voo não existir
    free(((Flight *) flight)->airplane); //liberta as strings
    free(((Flight *) flight)->airline);
    destroyDate(((Flight *)flight)->scheduleDeparture);
    destroyDate(((Flight *)flight)->scheduleArrival);
    destroyDate(((Flight *)flight)->realDeparture);
    destroyDate(((Flight *)flight)->realArrival);
    destroyOrdList(((Flight *) flight)->passengers,free); //liberta a lista de passageiros
    free(flight); //liberta o voo
}
