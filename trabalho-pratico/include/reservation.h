#ifndef _RESERVATION_
#define _RESERVATION_

#include "utility.h"
#include "hotel.h"
#include "hashtable.h"

//q1 - n_noites e preco total

typedef struct reservation Reservation;

Reservation *createReservation(char *id, char *id_user, char *id_hotel, char *hotelName, char hotelStars, char *hotelAdderss, int cityTax, Date *begin, Date *end, int pricePerNight, bool includesBreakfast, /*char *roomDetails,*/ char userClassification, /*char *userComment,*/ Hashtable *hotels);

//gets libertar espaço dos gets
char *getReservId(Reservation *reservation);
char *getReservUserId(Reservation *reservation);
int getReservUserKey(Reservation *reservation);
char *getReservHotelId(Reservation *reservation);
char *getReservHotelName(Reservation *reservation);
char *getReservHotelAddress(Reservation *reservation);
//char *getReservRoomDetails(Reservation *reservation);
//char *getReservUserComment(Reservation *reservation);
struct hotel *getReservHotel(Reservation *reservation);
int getReservCityTax(Reservation *reservation);
int getReservPricePerNight(Reservation *reservation);
int getReservUserClassification(Reservation *reservation);
char getReservHotelStars(Reservation *reservation);
Date *getReservBegin(Reservation *reservation);
Date *getReservEnd(Reservation *reservation);
int getReservBeginDay(void *reservation);
int getReservBeginMonth(void *reservation);
int getReservBeginYear(void *reservation);
int getReservEndDay(void *reservation);
int getReservEndMonth(void *reservation);
int getReservEndYear(void *reservation);
bool getReservIncludesBreakfast(Reservation *reservation);
//sets
void setUserId(Hashtable *hashtable, unsigned int key, char *id_user, char *ReservId);
void setHotelId(Hashtable *hashtable, unsigned int key, char *id_hotel, char *id);
void setHotelName(Hashtable *hashtable, unsigned int key, char *hotelName, char *id);
void setHotelStars(Hashtable *hashtable, unsigned int key, char hotelStars, char *id);
void setCityTax(Hashtable *hashtable, unsigned int key, int cityTax, char *id);
void setHotelAdress(Hashtable *hashtable, unsigned int key, char *hotelAddress, char *id);
void setBeginDate(Hashtable *hashtable, unsigned int key, Date *begin, char *id);
void setEndDate(Hashtable *hashtable, unsigned int key, Date *end, char *id);
void setPricePerNight(Hashtable *hashtable, unsigned int key, int pricePerNight, char *id);
void setIncludesBreakfast(Hashtable *hashtable, unsigned int key, bool includesBreakfast, char *id);
//void setRoomDetails(Hashtable *hashtable, unsigned int key, char *roomDetails, char *id);
void setUserClassification(Hashtable *hashtable, unsigned int key, char userClassification, char *id);
//void setUserComment(Hashtable *hashtable, unsigned int key, char *userComment, char *id);

Date *getBeginDateReservation(void *reservation);

void destroyReservation(void *reservation);

#endif