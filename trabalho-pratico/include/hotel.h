#ifndef _HOTEL_
#define _HOTEL_

#include "hashtable.h"
#include "orderedList.h"
#include "utility.h"

typedef struct hotel Hotel;
//cria um novo hotel
Hotel *createHotel(char *id, char *name, char stars, int cityTax);
//adiciona reserva à lista de reservas de um hotel
void addReservationToHotel(Hotel *hotel, unsigned long int id_reserv, char rating);

int searchHotelDates(Date *date, int (*compareDate)(void*,void*,void*), void *lookup, Hotel *hotel);

//gets
char *getHotelName(Hotel *hotel);
char getHotelStars(Hotel *hotel);
double getHotelRatingsSum(Hotel *hotel);
int getHotelNumberRatings(Hotel *hotel);
int getHotelCityTax(Hotel *hotel);
int getHotelCityTaxId(char *id, Hashtable *hotels);
//retorna o id da reserva num certo indíce da lista
unsigned long int getHotelReservId(Hotel *hotel, int index);
int getHotelNumberOfReservations(Hotel* hotel);
OrdList *getHotelOrdList(Hotel *hotel);

//sets
void setHName(Hotel *hotel, char *name);
void setHStars(Hotel *hotel, char stars);
void setHCityTax(Hotel *hotel, int cityTax);

//liberta espaço em memória do hotel
void destroyHotel(void *hotel);

//sort
void sortHotelReservationsByDate_hotel(Hotel *hotel, void (*radixsortReservsDate)(void*,void*), void *lookup);

#endif