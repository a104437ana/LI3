#ifndef _FLIGHT_
#define _FLIGHT_

#include "utility.h"
#include "passenger.h"
#include "hashtable.h"

typedef struct flight Flight;

Flight *createFlight(char *id, char *airline, char *airplane, int totalSeats, char origin[3], char destination[3], Date *scheduleDeparture, Date *scheduleArrival, Date *realDeparture, Date *realArrival, char *pilot, char *copilot, char *notes);
void addUserToFlight(Flight *flight, void *user);

//gets
char *getFlightAirline(Hashtable *hashtable, unsigned int key);
char *getFlightAirplane(Hashtable *hashtable, unsigned int key);
int getFlightTotalSeats(Hashtable *hashtable, unsigned int key);
char *getFlightOrigin(Hashtable *hashtable, unsigned int key);
char *getFlightDestination(Hashtable *hashtable, unsigned int key);
Date *getFlightScheduleDeparture(Hashtable *hashtable, unsigned int key);
Date *getFlightScheduleArrival(Hashtable *hashtable, unsigned int key);
Date *getFlightRealDeparture(Hashtable *hashtable, unsigned int key);
Date *getFlightRealArrival(Hashtable *hashtable, unsigned int key);
char *getFlightPilot(Hashtable *hashtable, unsigned int key);
char *getFlightCopilot(Hashtable *hashtable, unsigned int key);
char *getFlightNotes(Hashtable *hashtable, unsigned int key);

//sets
void setFlightAirline(Hashtable *hashtable, unsigned int key, char *airline);
void setFlightAirplane(Hashtable *hashtable, unsigned int key, char *airplane);
void setFlightTotalSeats(Hashtable *hashtable, unsigned int key, int totalSeats);
void setFlightOrigin(Hashtable *hashtable, unsigned int key, char origin[3]);
void setFlightDestination(Hashtable *hashtable, unsigned int key, char destination[3]);
void setFlightScheduleDeparture(Hashtable *hashtable, unsigned int key, Date scheduleDeparture);
void setFlightScheduleArrival(Hashtable *hashtable, unsigned int key, Date scheduleArrival);
void setFlightRealDeparture(Hashtable *hashtable, unsigned int key, Date realDeparture);
void setFlightRealArrival(Hashtable *hashtable, unsigned int key, Date realArrival);
void setFlightPilot(Hashtable *hashtable, unsigned int key, char *pilot);
void setFlightCopilot(Hashtable *hashtable, unsigned int key, char *copilot);
void setFlightNotes(Hashtable *hashtable, unsigned int key, char *notes);

#endif