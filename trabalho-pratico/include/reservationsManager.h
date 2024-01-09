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
void addReservToCatalog(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog);

//imprime o catálogo de reservas
void printReservations(ReservationsManager *reservationsManager);

//liberta o espaço em memória do catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager);

char* reservation_catalog_compute_Q1 (char *id, ReservationsManager* reservationsManager, QueryResult* result);

//gets
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager);
int getReservPriceNoTax(char *id, ReservationsManager *reservationsCatalog);
int getReservPriceLimits(char *id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd);
int getBReserv(int time, char *id, ReservationsManager *reservationsCatalog);
char *getSReservDate(char *id, ReservationsManager *reservationsCatalog);
int getBeginDayReservation(char *id, ReservationsManager *reservationsCatalog);
int getBeginMonthReservation(char *id, ReservationsManager *reservationsCatalog);
int getBeginYearReservation(char *id, ReservationsManager *reservationsCatalog);
#endif