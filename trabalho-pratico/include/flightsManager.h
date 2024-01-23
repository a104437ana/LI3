#ifndef _FLIGHTS_MANAGER_
#define _FLIGHTS_MANAGER_

#include "flight.h"
#include "airportsManager.h"
#include "usersManager.h"
#include "hashtable.h"

typedef struct flightsManager FlightsManager;
//cria um catalogo de voos
FlightsManager *createFlightsCatalog(int size);
//adiciona um voo ao catalogo de voos
int addFlightToCatalog(int id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog);
//adiciona o utilizador à lista de passageiros do voo
void addUserToFlight(int id_flight, char *id_user, FlightsManager *flightsCatalog);
void sortFlightsByDepartureDate(FlightsManager * flightsCatalog);

OrdList * getFlightsByDeparture(FlightsManager * flights);
int getFlightSD_flightscatalog(int time, int id, FlightsManager *flightsCatalog);
int getDepartureDayFlight(int id, FlightsManager *flightsCatalog);
int getDepartureMonthFlight(int id, FlightsManager *flightsCatalog);
int getDepartureYearFlight(int id, FlightsManager *flightsCatalog);
int getFirstFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog);
int getLastFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog);

//liberta espaço em memória do catalogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager);

void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result);

int compareDates_flight(void *date, void *id, void *flightsCatalog);
int compareMonths_flight(void *date, void *id, void *flightsCatalog);
int compareYears_flight(void *date, void *id, void *flightsCatalog);
OrdList* getFlightsDataQ10(int year, int month, int day, FlightsManager * flightsCatalog,int * flights,int * passengers,int  * unique_passengers);

//gets
Flight *getFlightCatalog(FlightsManager *flightsManager, int id);
int existsFlight (FlightsManager* flightsManager,char* id);
HashtableInt *getHashtableFlightsCatalog(FlightsManager *flightsManager);
int getSDFlight(int time, int id, FlightsManager *flightsCatalog);
char *getSFlightDate(int id, FlightsManager *flightsCatalog);
int compareFlightYear_flightsCatalog(int year, int id, void *flightsCatalog);
int getNumberPassengers_flightsCatalog(int id, void *flightsCatalog);

#endif