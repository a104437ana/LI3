#ifndef _FLIGHTS_MANAGER_
#define _FLIGHTS_MANAGER_

#include "results.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct flightsManager FlightsManager;

//função que cria um catálogo de voos
FlightsManager *createFlightsCatalog(int size);

//função que adiciona um voo ao catálogo de voos
int addFlightToCatalog(unsigned long int id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, FlightsManager *flightsCatalog);
//adiciona o utilizador à lista de passageiros do voo
void addUserToFlight(int id_flight, char *id_user, FlightsManager *flightsCatalog);
//ordena os voos na lista de voos do catálogo
void sortFlightsByDepartureDate(FlightsManager * flightsCatalog);

//gets
//verifica se um voo existe no catálogo
int existsFlight (FlightsManager* flightsManager,char* id);
//retorna um campo do tempo de partida estimado
int getFlightSD_flightscatalog(int time, unsigned long int id, FlightsManager *flightsCatalog);
//retorna o tempo de partida estimado em formato de string
char *getSFlightDate(unsigned long int id, FlightsManager *flightsCatalog);
//retorna o ano do primeiro voo
int getFirstFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog);
//retorna o ano do último voo
int getLastFlightDepartureYear_flightsCatalog(FlightsManager *flightsCatalog);
//retorn o número de passageiros de um voo
int getNumberPassengers_flightsCatalog(unsigned long int id, void *flightsCatalog);
HashtableInt *getHashtableFlightsCatalog(FlightsManager *flightsManager);
//compara o ano de um voo
int compareFlightYear_flightsCatalog(unsigned long int year, unsigned long int id, void *flightsCatalog);

//liberta espaço em memória do catalogo de voos
void destroyFlightsCatalog(FlightsManager *flightsManager);

//compara datas de um voo
int compareDates_flight(void *date, void *id, void *flightsCatalog);
int compareMonths_flight(void *date, void *id, void *flightsCatalog);
int compareYears_flight(void *date, void *id, void *flightsCatalog);

//queries
void flight_catalog_compute_Q1 (char *id, FlightsManager* flightsManager, QueryResult* result);
OrdList* getFlightsDataQ10(int year, int month, int day, FlightsManager * flightsCatalog,int * flights,int * passengers,int  * unique_passengers);

#endif