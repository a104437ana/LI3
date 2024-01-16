#ifndef _FLIGHT_
#define _FLIGHT_

#include "utility.h"
#include "passenger.h"
#include "hashtable.h"
#include "orderedList.h"

#define PASSENGER_LIST_INI_SIZE 100

typedef struct flight Flight;
//cria um novo voo
Flight *createFlight(char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival);
//função que adiciona um utilizador à lista de passageiros de um voo
void addPassengerToFlight(Flight *flight, char *id_user);

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
int getFlightScheduleDepartureDay(void *id, void *lookupTable);
int getFlightScheduleDepartureMonth(void *id, void *lookupTable);
int getFlightScheduleDepartureYear(void *id, void *lookupTable);
int getFlightScheduleDepartureSeconds(void *id, void *lookupTable);
int getFlightScheduleDepartureMinutes(void *id, void *lookupTable);
int getFlightScheduleDepartureHours(void *id, void *lookupTable);
int getDepartureDay(void *flight);
int getDepartureMonth(void *flight);
int getDepartureYear(void *flight);

int getFlightSD(int time, Flight *flight);
Date * getFlightDepartureDate(void *id, void *lookupTable);
char *getStringFlightDateNoHours(Flight *flight);
char *getFlightId(Flight *flight);
OrdList * getPassengers(Flight* flight);
int getNumberPassengers(Flight* flight);
int getDelay(Flight* flight);

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