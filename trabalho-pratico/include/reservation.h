#ifndef _RESERVATION_
#define _RESERVATION_

#include "utility.h"
#include "hotel.h"
#include "hotelsManager.h"
#include "usersManager.h"
#include "hashtable.h"

typedef struct reservation Reservation;
//cria uma nova reserva
Reservation *createReservation(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, UsersManager *usersCatalog, Hashtable *hotels);

//gets
Reservation *getReservCatalog(Hashtable *reservations, unsigned int key, char *id);
char *getReservId(Reservation *reservation);
char *getReservUserId(Reservation *reservation);
int getReservUserKey(Reservation *reservation);
char *getReservHotelId(Reservation *reservation);
//char *getReservHotelName(Reservation *reservation, Hashtable *hotels);
int getReservCityTax(Reservation *reservation, Hashtable *hotels);
int getReservPricePerNight(Reservation *reservation);
int getReservUserClassification(Reservation *reservation);
//char getReservHotelStars(Reservation *reservation, Hashtable *hotels);
Date *getReservBegin(Reservation *reservation);
Date *getReservEnd(Reservation *reservation);
int getReservBeginDay(void *reservation);
int getReservBeginMonth(void *reservation);
int getReservBeginYear(void *reservation);
int getReservBeginDayId(void *id, Hashtable *lookupTable);
int getReservBeginMonthId(void *id, Hashtable *lookupTable);
int getReservBeginYearId(void *id, Hashtable *lookupTable);
int getReservEndDay(void *reservation);
int getReservEndMonth(void *reservation);
int getReservEndYear(void *reservation);
bool getReservIncludesBreakfast(Reservation *reservation);
int getReservNights(Reservation* reservation);
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