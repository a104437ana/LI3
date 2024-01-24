#ifndef _FLIGHT_
#define _FLIGHT_

#include "utility.h"
#include "orderedList.h"

typedef struct flight Flight;
//cria um novo voo
Flight *createFlight(char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival);
//função que adiciona um utilizador à lista de passageiros de um voo
void addPassengerToFlight(Flight *flight, char *id_user);

//gets
//strings
char *getFlightAirline(Flight *flight);
char *getFlightAirplane(Flight *flight);
char *getFlightOrigin(Flight *flight);
char *getFlightDestination(Flight *flight);
//datas do voo
Date *getFlightScheduleDeparture(Flight *flight);
Date *getFlightScheduleArrival(Flight *flight);
Date *getFlightRealDeparture(Flight *flight);
Date *getFlightRealArrival(Flight *flight);
int getDepartureDay(void *flight, void *lookup);
int getDepartureMonth(void *flight, void *lookup);
int getDepartureYear(void *flight, void *lookup);
int getFlightSD(int time, Flight *flight);
char *getStringFlightDateNoHours(Flight *flight);
//passageiros
OrdList * getPassengers(Flight* flight);
//numero de passageiros
int getNumberPassengers(Flight* flight);
//atraso do voo
int getDelay(Flight* flight);

//sets
void setFlightAirline(Flight *flight, char *airline);
void setFlightAirplane(Flight *flight, char *airplane);
void setFlightOrigin(Flight *flight, char origin[4]);
void setFlightDestination(Flight *flight, char destination[4]);

//liberta espaço em memória de um voo
void destroyFlight(void *flight);

#endif