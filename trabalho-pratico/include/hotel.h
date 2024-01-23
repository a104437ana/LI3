#ifndef _HOTEL_
#define _HOTEL_

#include "utility.h"
#include "hashtable.h"
#include "orderedList.h"

#define HOTEL_RESERVATIONS_INI_SIZE 100

typedef struct hotel Hotel;
//cria um novo hotel
Hotel *createHotel(char *id, char *name, char stars, int cityTax);
//adiciona reserva à lista de reservas de um hotel
void addReservationToHotel(Hotel *hotel, unsigned long int id_reserv, char rating);
void sortHotelReservationsByDate_hotel(Hotel *hotel, void (*radixsortReservsDate)(void*,void*), void *lookup);

int getHotelNumberOfReservations(Hotel* hotel);
//obtem a lista de reservas do hotel
OrdList *getHotelOrdList(Hotel *hotel);
OrdList *getHotelEndOrdList(Hotel *hotel);
unsigned long int getHotelReservId(Hotel *hotel, int index);
int searchHotelDates(Date *date, int (*compareDate)(void*,void*,void*), void *lookup, Hotel *hotel);

//gets
char *getHotelId(Hotel *hotel);
char *getHotelName(Hotel *hotel);
char getHotelStars(Hotel *hotel);
double getHotelRatingsSum(Hotel *hotel);
int getHotelNumberRatings(Hotel *hotel);
int getHotelCityTax2(char *id, Hashtable *hotels);
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