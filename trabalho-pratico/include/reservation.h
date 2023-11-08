#ifndef _RESERVATION_
#define _RESERVATION_

#include "utility.h"

//q1 - n_noites e preco total

typedef struct reservation {
    char *id;                       //q2
    char *id_user;
    char *id_hotel;                 //q1
    char *hotelName;               //q1
    char hotelStars;            //q1
    int cityTax;
    char *hotelAddress;
    Date begin;                    //q1/q2/q4
    Date end;                       //q1
    int pricePerNight;
    bool includesBreakfast;     //q1
    char *roomDetails;
    char userClassification;
    char *userComment;
} Reserva;

Reserva *criaReserva(char *id, char *id_user, char *id_hotel, char *hotelName, char hotelStars, int cityTax, char *hotelAdderss, Date begin, Date end, int pricePerNight, bool includesBreakfast, char *roomDetails, char userClassification, char *userComment);
//adicionar validacao
//gets e sets fazer get multiplo e set multiplo
//gets
char *getUserId(Hashtable *hashtable, unsigned int key);
char *getHotelId(Hashtable *hashtable, unsigned int key);
char *getHotelName(Hashtable *hashtable, unsigned int key);
char getHotelStars(Hashtable *hashtable, unsigned int key);
int getCityTax(Hashtable *hashtable, unsigned int key);
char *getHotelAdress(Hashtable *hashtable, unsigned int key);
char *getBeginDate(Hashtable *hashtable, unsigned int key);
char *getEndDate(Hashtable *hashtable, unsigned int key);
int getPricePerNight(Hashtable *hashtable, unsigned int key);
bool getIncludesBreakfast(Hashtable *hashtable, unsigned int key);
char *getRoomDetails(Hashtable *hashtable, unsigned int key);
char getUserClassification(Hashtable *hashtable, unsigned int key);
char *getUserComment(Hashtable *hashtable, unsigned int key);
//sets
void setUserId(Hashtable *hashtable, unsigned int key, char *id_user);
void setHotelId(Hashtable *hashtable, unsigned int key, char *id_hotel);
void setHotelName(Hashtable *hashtable, unsigned int key, char *hotelName);
void setHotelStars(Hashtable *hashtable, unsigned int key, char hotelStars);
void setCityTax(Hashtable *hashtable, unsigned int key, int cityTax);
void setHotelAdress(Hashtable *hashtable, unsigned int key, char *hotelAddress);
void setBeginDate(Hashtable *hashtable, unsigned int key, Date begin);
void setEndDate(Hashtable *hashtable, unsigned int key, Date end);
void setPricePerNight(Hashtable *hashtable, unsigned int key, int pricePerNight);
void setIncludesBreakfast(Hashtable *hashtable, unsigned int key, bool includesBreakfast);
void setRoomDetails(Hashtable *hashtable, unsigned int key, char *roomDetails);
void setUserClassification(Hashtable *hashtable, unsigned int key, char userClassification);
void setUserComment(Hashtable *hashtable, unsigned int key, char *userComment);

#endif