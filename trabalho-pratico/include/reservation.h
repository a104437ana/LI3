#ifndef _RESERVATION_
#define _RESERVATION_

#include "utility.h"
#include "hotel.h"
#include "hashtable.h"

typedef struct reservation Reservation;
//cria uma nova reserva
Reservation *createReservation(char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification);

//gets
Reservation *getReservCatalog(Hashtable *reservations, char *id);
char *getReservId(Reservation *reservation);
char *getReservUserId(Reservation *reservation);
int getReservUserKey(Reservation *reservation);
char *getReservHotelId(Reservation *reservation);
//char *getReservHotelName(Reservation *reservation, Hashtable *hotels);
int getReservCityTax(Reservation *reservation, Hashtable *hotels);
int getReservPricePerNight(Reservation *reservation);
int getReservUserClassification(Reservation *reservation);
//char getReservHotelStars(Reservation *reservation, Hashtable *hotels);
Date * getReservationBeginDate(void *id, void *lookupTable);
Date *getReservBegin(Reservation *reservation);
Date *getReservEnd(Reservation *reservation);
int getReservBeginDay(void *reservation, void* lookup);
int getReservBeginMonth(void *reservation, void* lookup);
int getReservBeginYear(void *reservation, void* lookup);
int getReservBeginDayId(void *id, void *lookupTable);
int getReservBeginMonthId(void *id, void *lookupTable);
int getReservBeginYearId(void *id, void *lookupTable);
int getReservationB(int time, Reservation *reservation);
int getReservEndDay(void *reservation);
int getReservEndMonth(void *reservation);
int getReservEndYear(void *reservation);
bool getReservIncludesBreakfast(Reservation *reservation);
int getReservNights(Reservation* reservation);
int getReservNightsWithLimits(Reservation* reservation, Date *limitBegin, Date *limitEnd);
int getReservUserClassificationId(void *id, void *lookupTable);
char *getReservUserIdId(void *id, void *lookupTable);
Date *getReservBeginId(void *id, void *lookupTable);
Date *getReservEndId(void *id, void *lookupTable);
char *getStringReservDate(Reservation *reservation);
int compareReservDates(Reservation *reservation, Date *date);
int compareReservationsBeginDates(Reservation *r1, Reservation *r2);

//sets
//void setUserId(Hashtable *hashtable, unsigned int key, char *id_user, char *ReservId);
//void setHotelId(Hashtable *hashtable, unsigned int key, char *id_hotel, char *id);
//void setHotelName(Hashtable *hashtable, unsigned int key, char *hotelName, char *id);
//void setHotelStars(Hashtable *hashtable, unsigned int key, char hotelStars, char *id);
//void setCityTax(Hashtable *hashtable, unsigned int key, int cityTax, char *id);
//void setBeginDate(Hashtable *hashtable, unsigned int key, Date *begin, char *id);
//void setEndDate(Hashtable *hashtable, unsigned int key, Date *end, char *id);
//void setPricePerNight(Hashtable *hashtable, unsigned int key, int pricePerNight, char *id);
//void setIncludesBreakfast(Hashtable *hashtable, unsigned int key, bool includesBreakfast, char *id);
//void setUserClassification(Hashtable *hashtable, unsigned int key, char userClassification, char *id);

Date *getBeginDateReservation(void *reservation);
//liberta espaço em memória da reserva
void destroyReservation(void *reservation);

#endif