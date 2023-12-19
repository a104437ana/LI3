#ifndef _CATALOG_MANAGER_
#define _CATALOG_MANAGER_

#include "usersManager.h"
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "flightsManager.h"
#include "airportsManager.h"
#include "results.h"

#define USERS_HASHTABLE_INI_SIZE 100000
#define RESERVATIONS_HASHTABLE_INI_SIZE 40000
#define HOTELS_HASHTABLE_INI_SIZE 100
#define FLIGHTS_HASHTABLE_INI_SIZE 1000
#define AIRPORTS_HASHTABLE_INI_SIZE 100

typedef struct catalogsManager Catalogs;

//cria todos os catálogos
Catalogs *createCatalogs();

//ordena todos os catálogos
void sortCatalogs(Catalogs *catalogs);
void sortUserCatalog(Catalogs *catalogs);
void sortHotelCatalog(Catalogs *catalogs);
void sortAirportCatalog(Catalogs *catalogs);

//funções sobre diferêntes catálogos
//adiciona um utilizador ao catálogo
void addUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, Catalogs *catalogs);
void addReservation(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, Catalogs *catalogs);
void addFlight(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, Catalogs *catalogs);
void addHotel(char *id, char *name, char stars, int cityTax, char userClassification, char *id_reserv, Catalogs *catalogs);
void addAirport(char *id, char *id_flight, Catalogs *catalogs);
void addPassenger(char *flightId, char *userId, Catalogs *catalogs);
int userExists(char *id, Catalogs *catalogs);
int flightExists(char *id, Catalogs *catalogs);
//funções alternativas enquanto encapsulamento não está completo
UsersManager *getUsersCatalog(Catalogs *catalogs);
FlightsManager *getFlightsCatalog(Catalogs *catalogs);
ReservationsManager *getReservationsCatalog(Catalogs *catalogs);
HotelsManager *getHotelsCatalog(Catalogs *catalogs);
AirportsManager *getAirportsCatalog(Catalogs *catalogs);

//liberta o espaço em memória de todos os catálogos
void destroyCatalogs(Catalogs *catalogs);

//queries
void catalogs_compute_Q1_user (char *id, Catalogs* catalogs, Results* results);

void catalogs_compute_Q1_flight (char *id, Catalogs* catalogs, Results* results);

void catalogs_compute_Q1_reservation (char *id, Catalogs* catalogs, Results* results);

void catalogs_compute_Q3(char* id_hotel, Catalogs* catalogs, Results* results);

#endif