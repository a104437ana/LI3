#ifndef _FLIGHT_
#define _FLIGHT_

#include "utility.h"
#include "passenger.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct flight Flight;

Flight *createFlight(char *id, char *airline, char *airplane, int totalSeats, char origin[3], char destination[3], Date *scheduleDeparture, Date *scheduleArrival, Date *realDeparture, Date *realArrival, char *pilot, char *copilot, char *notes);
void addUserToFlight(Flight *flight, void *user);

//gets
char *getFlightAirline(Flight *flight);
char *getFlightAirplane(Flight *flight);
int getFlightTotalSeats(Flight *flight);
char *getFlightOrigin(Flight *flight);
char *getFlightDestination(Flight *flight);
Date *getFlightScheduleDeparture(Flight *flight);
Date *getFlightScheduleArrival(Flight *flight);
Date *getFlightRealDeparture(Flight *flight);
Date *getFlightRealArrival(Flight *flight);
char *getFlightPilot(Flight *flight);
char *getFlightCopilot(Flight *flight);
char *getFlightNotes(Flight *flight);
char *getFlightId(Flight *flight);
OrdList * getPassengers(Flight* flight);

//sets
void setFlightAirline(Flight *flight, char *airline);
void setFlightAirplane(Flight *flight, char *airplane);
void setFlightTotalSeats(Flight *flight, int totalSeats);
void setFlightOrigin(Flight *flight, char origin[3]);
void setFlightDestination(Flight *flight, char destination[3]);
void setFlightScheduleDeparture(Flight *flight, Date *scheduleDeparture);
void setFlightScheduleArrival(Flight *flight, Date *scheduleArrival);
void setFlightRealDeparture(Flight *flight, Date *realDeparture);
void setFlightRealArrival(Flight *flight, Date *realArrival);
void setFlightPilot(Flight *flight, char *pilot);
void setFlightCopilot(Flight *flight, char *copilot);
void setFlightNotes(Flight *flight, char *notes);

#endif