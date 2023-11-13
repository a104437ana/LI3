#ifndef _RESERVATION_
#define _RESERVATION_

#include "utility.h"
#include "hotel.h"
#include "hashtable.h"

//q1 - n_noites e preco total

typedef struct reservation Reservation;

Reservation *createReservation(char *id, char *id_user, char *id_hotel, char *hotelName, char hotelStars, char *hotelAdderss, int cityTax, Date *begin, Date *end, int pricePerNight, bool includesBreakfast, char *roomDetails, char userClassification, char *userComment, Hashtable *hotels);

//gets libertar espaço dos gets
char *getReservId(Reservation *reservation);
char *getReservUserId(Reservation *reservation);
int getReservUserKey(Reservation *reservation);
char *getReservHotelId(Reservation *reservation);
char *getReservHotelName(Reservation *reservation);
char *getReservHotelAddress(Reservation *reservation);
char *getReservRoomDetails(Reservation *reservation);
char *getReservUserComment(Reservation *reservation);
struct hotel *getReservHotel(Reservation *reservation);
int getReservCityTax(Reservation *reservation);
int getReservPricePerNight(Reservation *reservation);
char getReservUserClassification(Reservation *reservation);
char getReservHotelStars(Reservation *reservation);
Date *getReservBegin(Reservation *reservation);
Date *getReservEnd(Reservation *reservation);
int getReservBeginDay(void *reservation);
int getReservBeginMonth(void *reservation);
int getReservBeginYear(void *reservation);
bool getReservIncludesBreakfast(Reservation *reservation);
//sets
void setUserId(Hashtable *hashtable, unsigned int key, char *id_user);
void setHotelId(Hashtable *hashtable, unsigned int key, char *id_hotel);
void setHotelName(Hashtable *hashtable, unsigned int key, char *hotelName);
void setHotelStars(Hashtable *hashtable, unsigned int key, char hotelStars);
void setCityTax(Hashtable *hashtable, unsigned int key, int cityTax);
void setHotelAdress(Hashtable *hashtable, unsigned int key, char *hotelAddress);
void setBeginDate(Hashtable *hashtable, unsigned int key, Date *begin);
void setEndDate(Hashtable *hashtable, unsigned int key, Date *end);
void setPricePerNight(Hashtable *hashtable, unsigned int key, int pricePerNight);
void setIncludesBreakfast(Hashtable *hashtable, unsigned int key, bool includesBreakfast);
void setRoomDetails(Hashtable *hashtable, unsigned int key, char *roomDetails);
void setUserClassification(Hashtable *hashtable, unsigned int key, char userClassification);
void setUserComment(Hashtable *hashtable, unsigned int key, char *userComment);

Date *getBeginDateReservation(void *reservation);

#endif