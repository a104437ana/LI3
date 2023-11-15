#ifndef _HOTEL_
#define _HOTEL_

#include "utility.h"
#include "reservation.h"
#include "orderedList.h"

#define HOTEL_RESERVATIONS_INI_SIZE 100

//queries de estatistica receita total entre duas datas

typedef struct hotel Hotel;
//create apontador para address desaparece
Hotel *createHotel(char *id, char *name, char stars, char *address, int cityTax);
void addReservationToHotel(Hotel *hotel, void *reservation);
void setReservationOnList(void *list, void *reservation);
void sortHotelReservationsByDate(void *hotel);

OrdList *getHotelOrdList(Hotel *hotel);
char *getHotelReservation(Hotel *hotel, unsigned int key);
//gets
char *getHotelId(Hotel *hotel);
char *getHotelName(Hotel *hotel);
char getHotelStars(Hotel *hotel);
char *getHotelAddress(Hotel *hotel);
int getHotelCityTax(Hotel *hotel);
//sets falta libertar espaço em memória
void setHId(Hotel *hotel, char *id);
void setHName(Hotel *hotel, char *name);
void setHStars(Hotel *hotel, char stars);
void setHAddress(Hotel *hotel, char *address);
void setHCityTax(Hotel *hotel, int cityTax);
void addToHotelStarsSum(Hotel *hotel, int stars);

void removeHId(Hotel *hotel);
void removeHName(Hotel *hotel);
void removeHAddress(Hotel *hotel);

void destroyHotel(void *hotel);

#endif