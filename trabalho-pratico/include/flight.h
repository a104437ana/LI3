#ifndef _FLIGHT_
#define _FLIGHT_

#include "utility.h"
#include "passenger.h"
#include "hashtable.h"
#include "orderedList.h"

#define PASSENGER_LIST_INI_SIZE 100

typedef struct flight Flight;
//cria um novo voo
Flight *createFlight(char *id, char *airline, char *airplane, /*int totalSeats,*/ char origin[4], char destination[4], Date *scheduleDeparture, Date *scheduleArrival, Date *realDeparture, Date *realArrival/*, char *pilot, char *copilot, char *notes*/, Hashtable *airports);
//adiciona um utilizador a um voo
void addUserToFlight(Flight *flight, void *user);

//gets
char *getFlightAirline(Flight *flight);
char *getFlightAirplane(Flight *flight);
//int getFlightTotalSeats(Flight *flight);
char *getFlightOrigin(Flight *flight);
char *getFlightDestination(Flight *flight);
Date *getFlightScheduleDeparture(Flight *flight);
Date *getFlightScheduleArrival(Flight *flight);
Date *getFlightRealDeparture(Flight *flight);
Date *getFlightRealArrival(Flight *flight);
int getFlightScheduleDepartureDay(void *flight);
int getFlightScheduleDepartureMonth(void *flight);
int getFlightScheduleDepartureYear(void *flight);
int getFlightScheduleDepartureSeconds(void *flight);
int getFlightScheduleDepartureMinutes(void *flight);
int getFlightScheduleDepartureHours(void *flight);
//char *getFlightPilot(Flight *flight);
//char *getFlightCopilot(Flight *flight);
//char *getFlightNotes(Flight *flight);
char *getFlightId(Flight *flight);
OrdList * getPassengers(Flight* flight);

//sets
void setFlightAirline(Flight *flight, char *airline);
void setFlightAirplane(Flight *flight, char *airplane);
//void setFlightTotalSeats(Flight *flight, int totalSeats);
void setFlightOrigin(Flight *flight, char origin[4]);
void setFlightDestination(Flight *flight, char destination[4]);
void setFlightScheduleDeparture(Flight *flight, Date *scheduleDeparture);
void setFlightScheduleArrival(Flight *flight, Date *scheduleArrival);
void setFlightRealDeparture(Flight *flight, Date *realDeparture);
void setFlightRealArrival(Flight *flight, Date *realArrival);
//void setFlightPilot(Flight *flight, char *pilot);
//void setFlightCopilot(Flight *flight, char *copilot);
//void setFlightNotes(Flight *flight, char *notes);

//liberta espaço em memória de um voo
void destroyFlight(void *flight);

#endif