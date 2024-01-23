#ifndef _RESERVATIONS_MANAGER_
#define _RESERVATIONS_MANAGER_

#include "reservation.h"
#include "hotelsManager.h"
#include "usersManager.h"
#include "hashtable.h"

typedef struct reservationsManager ReservationsManager;

//função que cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size);

//função que adiciona uma reserva ao catálogo de reservas
int addReservToCatalog(unsigned long int id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog);

void radixSortReservDate(OrdList *list, void *lookupTable);
void sortReservationsByBeginDate(ReservationsManager *reservationsCatalog);

//função que liberta o espaço em memória alocado pelo catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager);

//gets

HashtableInt *getHashtableReservCatalog(ReservationsManager *reservationsManager);
OrdList * getReservByBeginDate (ReservationsManager *reservations);
int getFirstReservationBeginYear_reservationsCatalog(ReservationsManager *reservationsCatalog);
int getLastReservationBeginYear_reservationsCatalog(ReservationsManager *reservationsCatalog);
int getReservPriceLimits(unsigned long int id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd);
int getReservationBegin_reservationsCatalog(int time, unsigned long int id, ReservationsManager *reservationsCatalog);
char *getSReservDate(unsigned long int id, ReservationsManager *reservationsCatalog);
int getBeginDayReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getBeginMonthReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getBeginYearReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getEndDayReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getEndMonthReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getEndYearReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int compareReservDates_reservationsCatalog(Date *date, unsigned long int id, ReservationsManager *reservationsCatalog);
//compara uma data com o início de uma reserva
int compareDates_reservation(void *date, void *reserv, void *reservationsCatalog);
//compara uma data com o início de uma reserva, sem considerar o dia
int compareMonths_reservation(void *date, void *reserv, void *reservationsCatalog);
//compara uma data com o início de uma reserva, só considerando o ano
int compareYears_reservation(void *date, void *reserv, void *reservationsCatalog);

//queries

//calcula as informações de uma reserva para a query 1
char * reservation_catalog_compute_Q1 (char *id, int* price_per_night, int* nights, ReservationsManager* reservationsManager, QueryResult* result);

//calcula o número de reservas com início numa data para a query 10
int getReservationsQ10(int year, int month, int day, ReservationsManager * reservations);

#endif