#ifndef _HOTEL_
#define _HOTEL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"
#include "reservation.h"
#include "orderedList.h"

#define HOTEL_RESERVATIONS_INI_SIZE 100

typedef struct hotel Hotel;
//cria um novo hotel
Hotel *createHotel(char *id, char *name, char stars, /*char *address,*/ int cityTax);
//adiciona reserva à lista de reservas de um hotel
void addReservationToHotel(Hotel *hotel, void *reservation);
//ordena as reservas do hotel
void sortHotelReservationsByDate(void *hotel);

//obtem a lista de reservas do hotel
OrdList *getHotelOrdList(Hotel *hotel);
//obtem o id da reserva de um hotel
char *getHotelReservation(Hotel *hotel, unsigned int key);

//gets
char *getHotelId(Hotel *hotel);
char *getHotelName(Hotel *hotel);
char getHotelStars(Hotel *hotel);
double getHotelRatingsSum(Hotel *hotel);
int getHotelNumberRatings(Hotel *hotel);
//char *getHotelAddress(Hotel *hotel);
int getHotelCityTax(Hotel *hotel);
//sets
void setHId(Hotel *hotel, char *id);
void setHName(Hotel *hotel, char *name);
void setHStars(Hotel *hotel, char stars);
//void setHAddress(Hotel *hotel, char *address);
void setHCityTax(Hotel *hotel, int cityTax);
void addToHotelRatingsSum(Hotel *hotel, char rating);
void addToHotelNumberRatings(Hotel *hotel, char rating);

void removeHId(Hotel *hotel);
void removeHName(Hotel *hotel);
//void removeHAddress(Hotel *hotel);

//liberta espaço em memória do hotel
void destroyHotel(void *hotel);

#endif