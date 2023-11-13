#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "flight.h"

struct flight {
    char *id;
    char *airline;            //q1
    char *airplane;                //q1
    int totalSeats;
    char origin[3];             //q1
    char destination[3];            //q1
    Date *scheduleDeparture;           //q1/q2
    Date *scheduleArrival;           //q1
    Date *realDeparture;
    Date *realArrival;
    char *pilot;
    char *copilot;
    char *notes;
//    Passenger *passengers;    //q1
};

Flight *createFlight(char *id, char *airline, char *airplane, int totalSeats, char origin[3], char destination[3], Date *scheduleDeparture, Date *scheduleArrival, Date *realDeparture, Date *realArrival, char *pilot, char *copilot, char *notes) {
    Flight *flight = malloc(sizeof(Flight));
    flight->id = strdup(id);
    flight->airline = strdup(airline);
    flight->airplane = strdup(airplane);
    flight->totalSeats = totalSeats;
    //usar strncopy(destination, origin, size(characters))
    flight->origin[0] = origin[0];
    flight->origin[1] = origin[1];
    flight->origin[2] = origin[2];
    flight->destination[0] = destination[0];
    flight->destination[1] = destination[1];
    flight->destination[2] = destination[2];
    flight->scheduleDeparture = scheduleDeparture;
    flight->scheduleArrival = scheduleArrival;
    flight->realDeparture = realDeparture;
    flight->realArrival = realArrival;
    flight->pilot = strdup(pilot);
    flight->copilot = strdup(copilot);
    flight->notes = strdup(notes);

    return flight;
}

//gets
char *getFlightAirline(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return strdup(data->airline);
}

char *getFlightAirplane(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return strdup(data->airplane);
}

int getFlightTotalSeats(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return data->totalSeats;
}

char *getFlightOrigin(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    char origin[3];
    origin[0] = data->origin[0];
    origin[1] = data->origin[1];
    origin[2] = data->origin[2];
    return origin;
}

char *getFlightDestination(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    char destination[3];
    destination[0] = data->destination[0];
    destination[1] = data->destination[1];
    destination[2] = data->destination[2];
    return destination;
}

Date getFlightScheduleDeparture(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return data->scheduleDeparture;
}

Date getFlightScheduleArrival(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return data->scheduleArrival;
}

Date getFlightRealDeparture(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return data->realDeparture;
}

Date getFlightRealArrival(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return data->realArrival;
}

char *getFlightPilot(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return strdup(data->pilot);
}

char *getFlightCopilot(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return strdup(data->copilot);
}

char *getFlightNotes(Hashtable *hashtable, unsigned int key) {
    Flight *data = getData(hashtable, key);
    return strdup(data->notes);
}

//sets
void setFlightAirline(Hashtable *hashtable, unsigned int key, char *airline) {
    Flight *data = getData(hashtable, key);
    char *oldAirline = data->airline;
    data->airline = strdup(airline);
    free(oldAirline);
}

void setFlightAirplane(Hashtable *hashtable, unsigned int key, char *airplane) {
    Flight *data = getData(hashtable, key);
    char *oldAirplane = data->airplane;
    data->airplane = strdup(airplane);
    free(oldAirplane);
}

void setFlightTotalSeats(Hashtable *hashtable, unsigned int key, int totalSeats) {
    Flight *data = getData(hashtable, key);
    data->totalSeats = totalSeats;
}

void setFlightOrigin(Hashtable *hashtable, unsigned int key, char origin[3]) {
    Flight *data = getData(hashtable, key);
    data->origin[0] = origin[0];
    data->origin[1] = origin[1];
    data->origin[2] = origin[2];
}

void setFlightDestination(Hashtable *hashtable, unsigned int key, char destination[3]) {
    Flight *data = getData(hashtable, key);
    data->destination[0] = destination[0];
    data->destination[1] = destination[1];
    data->destination[2] = destination[2];
}

void setFlightScheduleDeparture(Hashtable *hashtable, unsigned int key, Date scheduleDeparture) {
    Flight *data = getData(hashtable, key);
    data->scheduleDeparture = scheduleDeparture;
}

void setFlightScheduleArrival(Hashtable *hashtable, unsigned int key, Date scheduleArrival) {
    Flight *data = getData(hashtable, key);
    data->scheduleArrival = scheduleArrival;
}

void setFlightRealDeparture(Hashtable *hashtable, unsigned int key, Date realDeparture) {
    Flight *data = getData(hashtable, key);
    data->realDeparture = realDeparture;
}

void setFlightRealArrival(Hashtable *hashtable, unsigned int key, Date realArrival) {
    Flight *data = getData(hashtable, key);
    data->realArrival = realArrival;
}

void setFlightPilot(Hashtable *hashtable, unsigned int key, char *pilot) {
    Flight *data = getData(hashtable, key);
    char *oldPilot = data->pilot;
    data->pilot = strdup(pilot);
    free(oldPilot);
}

void setFlightCopilot(Hashtable *hashtable, unsigned int key, char *copilot) {
    Flight *data = getData(hashtable, key);
    char *oldCopilot = data->copilot;
    data->copilot = strdup(copilot);
    free(oldCopilot);
}

void setFlightNotes(Hashtable *hashtable, unsigned int key, char *notes) {
    Flight *data = getData(hashtable, key);
    char *oldNotes = data->notes;
    data->notes = strdup(notes);
    free(oldNotes);
}
