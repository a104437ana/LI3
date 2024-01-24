#ifndef _RESERVATION_
#define _RESERVATION_

#include "utility.h"
#include "hotel.h"
#include "hashtable.h"

typedef struct reservation Reservation;
//cria uma nova reserva
Reservation *createReservation(char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification);

//gets
char *getReservUserId(Reservation *reservation);
char *getReservHotelId(Reservation *reservation);
int getReservCityTax(Reservation *reservation, Hashtable *hotels);
int getReservPricePerNight(Reservation *reservation);
int getReservUserClassification(Reservation *reservation);
Date *getReservBegin(Reservation *reservation);
Date *getReservEnd(Reservation *reservation);

int getReservBeginDay(void *reservation, void* lookup);
int getReservBeginMonth(void *reservation, void* lookup);
int getReservBeginYear(void *reservation, void* lookup);
int getReservationBegin_reservation(int time, Reservation *reservation);
int getReservEndDay(void *reservation);
int getReservEndMonth(void *reservation);
int getReservEndYear(void *reservation);
bool getReservIncludesBreakfast(Reservation *reservation);
int getReservNights(Reservation* reservation);
int getReservNightsWithLimits(Reservation* reservation, Date *limitBegin, Date *limitEnd);
char *getStringReservDate(Reservation *reservation);

//liberta espaço em memória da reserva
void destroyReservation(void *reservation);

//sort
int compareReservDates(Reservation *reservation, Date *date);

#endif