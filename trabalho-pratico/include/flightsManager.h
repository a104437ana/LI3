#ifndef _FLIGHTS_MANAGER_
#define _FLIGHTS_MANAGER_

#include "flight.h"
#include "airportsManager.h"
#include "usersManager.h"
#include "hashtable.h"

typedef struct flightsManager FlightsManager;

//função que cria um catálogo de voos
FlightsManager *createFlightsCatalog(int size);

//função que adiciona um voo ao catálogo de voos
int addFlightToCatalog(unsigned long int id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog);
//adiciona o utilizador à lista de passageiros do voo
void addUserToFlight(int id_flight, char *id_user, FlightsManager *flightsCatalog);

//ordena voos por data de partida
void radixSortDeparture(OrdList *list, void *lookupTable);
//ordena uma lista de voos
void sortFlightsByDepartureDate(FlightsManager * flightsCatalog);

//gets

Flight *getFlightCatalog(FlightsManager *flightsManager, unsigned long int id);
int existsFlight (FlightsManager* flightsManager,char* id);
HashtableInt *getHashtableFlightsCatalog(FlightsManager *flightsManager);
OrdList * getFlightsByDeparture(FlightsManager * flights);
int getFlightSD_flightscatalog(int time, unsigned long int id, FlightsManager *flightsCatalog);
int getFirstFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog);
int getLastFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog);
int getSDFlight(int time, unsigned long int id, FlightsManager *flightsCatalog);
char *getSFlightDate(unsigned long int id, FlightsManager *flightsCatalog);
//compara uma data com a data de partida de um voo
int compareDates_flight(void *date, void *flight, void *flightsCatalog);
//compara uma data com a data de partida de um voo, sem considerar o dia
int compareMonths_flight(void *date, void *flight, void *flightsCatalog);
//compara uma data com a data de partida de um voo, só considerando o ano
int compareYears_flight(void *date, void *flight, void *flightsCatalog);
int compareFlightYear_flightsCatalog(unsigned long int year, unsigned long int id, void *flightsCatalog);
int getNumberPassengers_flightsCatalog(unsigned long int id, void *flightsCatalog);


//função que liberta o espaço em memória alocado pelo catálogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager);

//queries

//calcula os dados de um voo para a query 1
void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result);

//calcula dados de uma data para a query 10
OrdList* getFlightsDataQ10(int year, int month, int day, FlightsManager * flightsCatalog,int * flights,int * passengers,int  * unique_passengers);

#endif