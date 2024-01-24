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

//funções de ordenação dos catálogos

//função que ordena todos os catálogos
void sortCatalogs(Catalogs *catalogs);

//ordena os voos e reservas de um utilizador por data
void radixSortUserList(OrdList *list, void *lookupTable);
//função que compara os ids de dois voos ou reservas
int compareFlightReservsIds(void *data1, void *data2, void *lookup);
//função que ordena a lista de voos e reservas de um utilizador
void sortUserList(char *id, Catalogs *catalogs);

//ordena reservas de um hotel por data de início
void radixSortHotelReservByDate(void *list, void *lookupTable);
//função que ordena a lista de reservas de um hotel
void sortHotelReservationsByDate(char *id, Catalogs *catalogs);

//ordena voos de um aeroporto por data de partida
void radixSortAirportFlightByDate(void *list, void *lookupTable);
//função que ordena a lista de voos de um aeroporto
void sortAirportFlightsByDepartureDate(char *id, Catalogs* catalogs);

//funções sobre diferentes catálogos

//adiciona um utilizador ao catálogo
void addUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice, Catalogs *catalogs);
//adiciona uma reserva ao catálogo
void addReservation(int id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, int cityTax, Catalogs *catalogs);
//adiciona um voo ao catálogo
int addFlight(int id, char *airline, char *airplane, char *origin, char *destination, char *scheduleDeparture, char *scheduleArrival, char *realDeparture, char *realArrival, Catalogs *catalogs);
//adiciona uma reserva ao catálogo
void addHotel(char *id, char *name, char stars, int cityTax, char userClassification, int id_reserv, Catalogs *catalogs);
//adiciona uma reserva ao catálogo
void addAirport(int delay, char *id_origin, char *id_destination, int id_flight, Catalogs *catalogs);
//cria a lista de passageiros
void createListPassengers_UsersManager (Catalogs* catalogs, int size);
//adiciona um passageiro ao catálogo
void addPassenger(int flightId, char *userId, Catalogs *catalogs);
//verifica se um utilizador existe no catálogo
int userExists(char *id, Catalogs *catalogs);
//verifica se um voo existe no catálogo
int flightExists(char *id, Catalogs *catalogs);

//função que liberta o espaço em memória alocado por todos os catálogos
void destroyCatalogs(Catalogs *catalogs);

//queries

//calcula a informação de um utilizador para a query 1
void catalogs_compute_Q1_user (char *id, Catalogs* catalogs, QueryResult* result);
//calcula a informação de um voo para a query 1
void catalogs_compute_Q1_flight (char *id, Catalogs* catalogs, QueryResult* result);
//calcula a informação de uma reserva para a query 1
void catalogs_compute_Q1_reservation (char *id, Catalogs* catalogs, QueryResult* result);

//calcula a informação de um hotel para a query 3
void catalogs_compute_Q3(char* id_hotel, Catalogs* catalogs, QueryResult* result);

//calcula a informação para a query 4
void catalogs_compute_Q4(char* id, Catalogs* catalogs, QueryResult* result);

//calcula a informação de um aeroporto para a query 5
void catalogs_compute_Q5(char* airport,Date* begin,Date* end,Catalogs* catalogs,QueryResult* result);

//calcula a informação dos aeroportos para a query 7
void catalogs_compute_Q7(int n, Catalogs* catalogs, QueryResult* result);

void catalogs_compute_Q9 (char *prefix, Catalogs* catalogs, QueryResult* result);

//calcula a informação de uma data para a query 10
Result * catalogs_compute_Q10(int year, int month, int day, Catalogs* catalogs);

//gets

//vários catálogos

//calcula o primeiro ano em que existem registos de criação de conta, voo, ou reserva
int getYearFirstResults(Catalogs * catalogs);
//calcula o último ano em que existem registos de criação de conta, voo, ou reserva
int getYearLastResults(Catalogs * catalogs);

//users

int getAccountStatus(char *id, Catalogs *catalogs);
int getUserListSize(int type, char *id, Catalogs *catalogs);
unsigned long int getUserListId(int *type, char *id_user, int index, Catalogs *catalogs);
//int getUsersByNameSize_catalog(Catalogs *catalogs);
//int searchPrefix_catalog(char *prefix, Catalogs *catalogs);
int isPrefix_catalog(int *firstLetterCheck, char *prefix, int index, Catalogs *catalogs);
char *getIdUsersByName_catalog(int index, Catalogs *catalogs);
char *getNameUsersByName_catalog(int index, Catalogs *catalogs);
void getIdNameUsersByName_catalog(int index, char **id, char **name, Catalogs *catalogs);

//flights

int getFlightScheduleDepartureTime(int time, unsigned long int id, Catalogs *catalogs);
char *getStringFlightDate(unsigned long int id, Catalogs *catalogs);
int getFlightDepartureDay(unsigned long int id, void *catalogs);
int getFlightDepartureMonth(unsigned long int id, void *catalogs);
int getFlightDepartureYear(unsigned long int id, void *catalogs);
int getFlightDepartureSeconds(unsigned long int id, void *catalogs);
int getFlightDepartureMinutes(unsigned long int id, void *catalogs);
int getFlightDepartureHours(unsigned long int id, void *catalogs);

//reservations

int getReservationBegin(int time, int id, Catalogs *catalogs);
char *getStringReservationDate(int id, Catalogs *catalogs);
int getReservationBeginDay(unsigned long int id, void *catalogs);
int getReservationBeginMonth(unsigned long int id, void *catalogs);
int getReservationBeginYear(unsigned long int id, void *catalogs);

//hotels

int getHotelReservationsSize(char *id, Catalogs *catalogs);
int doesHotelExist(char *id, Catalogs *catalogs);
int getHotelReservPriceBetweenDates(char *id_hotel, int index, int *price, Date *begin, Date *end, Catalogs *catalogs);

//airports

int getAirportPassengersYear_catalog(int year, char *id, Catalogs *catalogs);
char *getNextAirportId_catalog(int index, Catalogs *catalogs);
int getNumberAirports_catalog(Catalogs *catalogs);

#endif