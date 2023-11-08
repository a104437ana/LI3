#ifndef _FLIGHT_
#define _FLIGHT_

#include "utility.h"
#include "passenger.h"

typedef struct flight {
    int id;
    char *airline;            //q1
    char *airplane;                //q1
    int totalSeats;
    char origin[3];             //q1
    char destination[3];            //q1
    Date scheduleDeparture;           //q1/q2
    Date scheduleArrival;           //q1
    Date realDeparture;
    Date realArrival;
    char *pilot;
    char *copilot;
    char *notes;
    Passenger *passengers;    //q1
} Flight;

#endif