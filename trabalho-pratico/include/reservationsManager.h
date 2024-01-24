#ifndef _RESERVATIONS_MANAGER_
#define _RESERVATIONS_MANAGER_

#include "results.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct reservationsManager ReservationsManager;

//função que cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size);

//função que adiciona uma reserva ao catálogo de reservas
int addReservToCatalog(unsigned long int id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog);

//gets

//retorna o ano da primeira reserva da lista
int getFirstReservationBeginYear_reservationsCatalog(ReservationsManager *reservationsCatalog);
//retorna o ano da última reserva da lista
int getLastReservationBeginYear_reservationsCatalog(ReservationsManager *reservationsCatalog);
//calcula o preço da reserva entre duas datas limite
int getReservPriceLimits(unsigned long int id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd);
//retorna o tempo de início da reserva
int getReservationBegin_reservationsCatalog(int time, unsigned long int id, ReservationsManager *reservationsCatalog);
//retorna o incício da reserva em string
char *getSReservDate(unsigned long int id, ReservationsManager *reservationsCatalog);
//data de início
int getBeginDayReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getBeginMonthReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getBeginYearReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
//data de fim
int getEndDayReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getEndMonthReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
int getEndYearReservation(unsigned long int id, ReservationsManager *reservationsCatalog);
HashtableInt *getHashtableReservCatalog(ReservationsManager *reservationsManager);

//função que liberta o espaço em memória alocado pelo catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager);

//sort
void radixSortReservDate(OrdList *list, void *lookupTable);
void sortReservationsByBeginDate(ReservationsManager *reservationsCatalog);

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