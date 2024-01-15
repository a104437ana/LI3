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
void sortUserCatalog(char *id, Catalogs *catalogs);
void sortHotelCatalog(Catalogs *catalogs);
void sortAirportCatalog(Catalogs *catalogs);
//ordena a lista de voos e reservas de um utilizador
void sortUserList(char *id, Catalogs *catalogs);
//ordena as reservas do hotel
void sortHotelReservationsByDate(char *id, Catalogs *catalogs);

void sortReservationsByBeginDate(Catalogs *catalogs);
void sortFlightsByDepartureDate(Catalogs * catalogs);
void radixSortDeparture(OrdList *list, void *lookupTable);
void sortUsersByAccountCreation(Catalogs *catalogs);
void radixSortAccountCreation(OrdList *list, void *lookupTable);

//ordena os voos do aeroporto
//void sortAirportFlightsByDepartureDate(char *id, Catalogs *catalogs);
void sortAirportFlightsByDepartureDate_catalog(char *id, Catalogs* catalogs);

//funções sobre diferêntes catálogos
//adiciona um utilizador ao catálogo
void addUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, Catalogs *catalogs);
void addReservation(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, Catalogs *catalogs);
int addFlight(char *id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, Catalogs *catalogs);
void addHotel(char *id, char *name, char stars, int cityTax, char userClassification, char *id_reserv, Catalogs *catalogs);
void addAirport(int delay, char *id_origin, char *id_destination, char *id_flight, Catalogs *catalogs);
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
void catalogs_compute_Q1_user (char *id, Catalogs* catalogs, QueryResult* result);

void catalogs_compute_Q1_flight (char *id, Catalogs* catalogs, QueryResult* result);

void catalogs_compute_Q1_reservation (char *id, Catalogs* catalogs, QueryResult* result);

void catalogs_compute_Q3(char* id_hotel, Catalogs* catalogs, QueryResult* result);

void catalogs_compute_Q4(char* id, Catalogs* catalogs, QueryResult* result);

void catalogs_compute_Q5(char* airport,Date* begin,Date* end,Catalogs* catalogs,QueryResult* result);

void catalogs_compute_Q7(int n, Catalogs* catalogs, QueryResult* result);

Result * catalogs_compute_Q10(int year, int month, int day, Catalogs* catalogs);

//gets
//user
int getAccountStatus(char *id, Catalogs *catalogs);
int getUserListSize(int type, char *id, Catalogs *catalogs);
char *getUserListId(int *type, char *id_user, int index, Catalogs *catalogs);
int getFlightScheduleDepartureTime(int time, char *id, Catalogs *catalogs);
int getUsersByNameSize_catalog(Catalogs *catalogs);
int searchPrefix_catalog(char *prefix, Catalogs *catalogs);
int isPrefix_catalog(int *firstLetterCheck, char *prefix, int index, Catalogs *catalogs);
char *getIdUsersByName_catalog(int index, Catalogs *catalogs);
char *getNameUsersByName_catalog(int index, Catalogs *catalogs);
//flights
int getFlightScheduleDepartureTime(int time, char *id, Catalogs *catalogs);
char *getStringFlightDate(char *id, Catalogs *catalogs);
//reservations
double getReservationPrice(char *id_reserv, char *id_hotel, Catalogs *catalogs);
int getReservationBegin(int time, char *id, Catalogs *catalog);
char *getStringReservationDate(char *id, Catalogs *catalogs);
//hotels
int getHotelReservationsSize(char *id, Catalogs *catalogs);
int doesHotelExist(char *id, Catalogs *catalogs);
int getHotelReservPriceBetweenDates(char *id, int index, int *price, Date *begin, Date *end, Catalogs *catalogs);
int getReservationBeginDay(void *id, void *catalogs);
int getReservationBeginMonth(void *id, void *catalogs);
int getReservationBeginYear(void *id, void *catalogs);
//airports
int getAirportPassengersYear_catalog(int year, char *id, Catalogs *catalogs);
char *getNextAirportId_catalog(int index, Catalogs *catalogs);
int getNumberAirports_catalog(Catalogs *catalogs);

int getFlightDepartureDay(void *id, void *catalogs);
int getFlightDepartureMonth(void *id, void *catalogs);
int getFlightDepartureYear(void *id, void *catalogs);
int getUserAccountCreationDay(void *id, void *catalogs);
int getUserAccountCreationMonth(void *id, void *catalogs);
int getUserAccountCreationYear(void *id, void *catalogs);

void getAllHashtables(Hashtable *u, Hashtable *f, Hashtable *r, Hashtable *h, Hashtable *a, Catalogs *catalogs);
Hashtable *getUsers_catalog(Catalogs *catalogs);
Hashtable *getFlights_catalog(Catalogs *catalogs);
Hashtable *getReservations_catalog(Catalogs *catalogs);
Hashtable *getHotels_catalog(Catalogs *catalogs);
Hashtable *getAirports_catalog(Catalogs *catalogs);

#endif