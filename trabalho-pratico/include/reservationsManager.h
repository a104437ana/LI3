#ifndef _RESERVATIONS_MANAGER_
#define _RESERVATIONS_MANAGER_

#include "reservation.h"
#include "hotelsManager.h"
#include "usersManager.h"
#include "hashtable.h"

typedef struct reservationsManager ReservationsManager;
//cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size);
//adiciona uma reserva ao catálogo de reservas
int addReservToCatalog(int *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog);

//imprime o catálogo de reservas
void printReservations(ReservationsManager *reservationsManager);

//liberta o espaço em memória do catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager);

char* reservation_catalog_compute_Q1 (char *id, int* price_per_night, int* nights, ReservationsManager* reservationsManager, QueryResult* result);

int compareDates_reservation(void *date, void *id, void *reservationsCatalog);
int compareMonths_reservation(void *date, void *id, void *reservationsCatalog);
int compareYears_reservation(void *date, void *id, void *reservationsCatalog);
int getReservationsQ10(int year, int month, int day, ReservationsManager * reservations);

//gets
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager);
OrdList * getReservByBeginDate (ReservationsManager *reservations);
int getReservPriceNoTax(int *id, ReservationsManager *reservationsCatalog);
int getReservPriceLimits(int *id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd);
int getBReserv(int time, int *id, ReservationsManager *reservationsCatalog);
char *getSReservDate(int *id, ReservationsManager *reservationsCatalog);
int getBeginDayReservation(int *id, ReservationsManager *reservationsCatalog);
int getBeginMonthReservation(int *id, ReservationsManager *reservationsCatalog);
int getBeginYearReservation(int *id, ReservationsManager *reservationsCatalog);
int getEndDayReservation(int *id, ReservationsManager *reservationsCatalog);
int getEndMonthReservation(int *id, ReservationsManager *reservationsCatalog);
int getEndYearReservation(int *id, ReservationsManager *reservationsCatalog);
int compareReservDates_reservationsCatalog(Date *date, int *id, ReservationsManager *reservationsCatalog);
#endif