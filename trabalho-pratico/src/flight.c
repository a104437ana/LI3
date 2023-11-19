#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "flight.h"
#include "user.h"
#include "orderedList.h"

struct flight {
    char *id;
    char *airline;            //q1
    char *airplane;                //q1
    //int totalSeats;
    char origin[4];             //q1
    char destination[4];            //q1
    Date *scheduleDeparture;           //q1/q2
    Date *scheduleArrival;           //q1
    Date *realDeparture;
    Date *realArrival;
    //char *pilot;
    //char *copilot;
    //char *notes;
    OrdList *passengers;    //q1
};

Flight *createFlight(char *id, char *airline, char *airplane, /*int totalSeats,*/ char origin[4], char destination[4], Date *scheduleDeparture, Date *scheduleArrival, Date *realDeparture, Date *realArrival/*, char *pilot, char *copilot, char *notes*/) {
    Flight *flight = malloc(sizeof(Flight));
    flight->id = strdup(id);
    flight->airline = strdup(airline);
    flight->airplane = strdup(airplane);
    //flight->totalSeats = totalSeats;
    //usar strncopy(destination, origin, size(characters))
    flight->origin[0] = origin[0];
    flight->origin[1] = origin[1];
    flight->origin[2] = origin[2];
    flight->origin[3] = origin[3];
    flight->destination[0] = destination[0];
    flight->destination[1] = destination[1];
    flight->destination[2] = destination[2];
    flight->destination[3] = origin[3];
    flight->scheduleDeparture = scheduleDeparture;
    flight->scheduleArrival = scheduleArrival;
    flight->realDeparture = realDeparture;
    flight->realArrival = realArrival;
    //flight->pilot = strdup(pilot);
    //flight->copilot = strdup(copilot);
    //flight->notes = strdup(notes);
    flight->passengers = createOrdList(PASSENGER_LIST_INI_SIZE);

    return flight;
}
//talvez nao seja preciso
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
/*
int getFlightTotalSeats(Flight *flight) {
    return flight->totalSeats;
}
*/
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

int getFlightScheduleDepartureDay(void *flight) {
    return ((Flight *) flight)->scheduleDeparture->day;
}

int getFlightScheduleDepartureMonth(void *flight) {
    return ((Flight *) flight)->scheduleDeparture->month;
}

int getFlightScheduleDepartureYear(void *flight) {
    return ((Flight *) flight)->scheduleDeparture->year;
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
void destroyFlight(void *flight) {
    if (flight == NULL) return;
//    free(((Flight *) flight)->passengers);
//    destroyOrdList(((Flight *) flight)->passengers, destroyUser);
    destroyDate(((Flight *) flight)->scheduleDeparture);
    destroyDate(((Flight *) flight)->scheduleArrival);
    destroyDate(((Flight *) flight)->realDeparture);
    destroyDate(((Flight *) flight)->realArrival);
    //free(((Flight *) flight)->notes);
    //free(((Flight *) flight)->copilot);
    //free(((Flight *) flight)->pilot);
//    free(((Flight *) flight)->destination);
//    free(((Flight *) flight)->origin);
    free(((Flight *) flight)->airplane);
    free(((Flight *) flight)->airline);
    free(((Flight *) flight)->id);
    free(flight);
}
