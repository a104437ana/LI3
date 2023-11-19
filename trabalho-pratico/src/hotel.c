#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "reservation.h"
#include "orderedList.h"
#include "utility.h"

struct hotel {
    char *id;           //q1
    char *name;         //q1
    char stars;          //q3/q1
    //char *address;
    int cityTax;
    OrdList *reservationsByDate;        //q4
    double ratingsSum;
    int numberRatings;
};

Hotel *createHotel(char *id, char *name, char stars, /*char *address,*/ int cityTax) {
    Hotel *hotel = malloc(sizeof(Hotel));
    //hotel->address = strdup(address); //address desaparece
    hotel->id = strdup(id);
    hotel->name = strdup(name);
    hotel->stars = stars;
    hotel->cityTax = cityTax;
    hotel->ratingsSum = 0;
    hotel->numberRatings = 0;
    hotel->reservationsByDate = createOrdList(HOTEL_RESERVATIONS_INI_SIZE);

    return hotel;
}

void addReservationToHotel(Hotel *hotel, void *reservation) {
    addOrdList(hotel->reservationsByDate, reservation);
//    hotel->starsSum += (int) getReservHotelStars((Reservation *) reservation);
}

void setHotelOnList(void *list, void *reservation) {
    list = reservation;
}

int compareReservsIds(void *reserv1, void *reserv2) {
    char *id1 = getReservId((Reservation *) reserv1), *id2 = getReservId((Reservation *) reserv2);
    return strcoll(id1, id2);
}

void sortHotelReservationsByDate(void *hotel) {
    OrdList *reservationsByDate = ((Hotel *) hotel)->reservationsByDate;
    quickSort(reservationsByDate, 0, getOrdListSize(reservationsByDate)-1, compareReservsIds, 0);
    reverseOrdList(reservationsByDate);
    radixSortReservDate(reservationsByDate);
}

OrdList *getHotelOrdList(Hotel *hotel) {
    return hotel->reservationsByDate;
}

char *getHotelReservation(Hotel *hotel, unsigned int key) {
    void *data = getDataOrdList(hotel->reservationsByDate, 0);
    return getReservId((Reservation*) data);
}

//gets
char *getHotelId(Hotel *hotel) {
    return hotel->id; //falta encapsulamento
}

char *getHotelName(Hotel *hotel) {
    return hotel->name; //falta encapsulamento
}

char getHotelStars(Hotel *hotel) {
    return hotel->stars;
}

double getHotelRatingsSum(Hotel *hotel) {
    return hotel->ratingsSum;
}

int getHotelNumberRatings(Hotel *hotel) {
    return hotel->numberRatings;
}
/*
char *getHotelAddress(Hotel *hotel) {
    return hotel->address; //falta encapsulamento
}
*/
int getHotelCityTax(Hotel *hotel) {
    return hotel->cityTax;
}
//sets falta libertar espaço em memória
void setHId(Hotel *hotel, char *id) {
    char *oldHotelId = hotel->id;
    hotel->id = strdup(id);
    free(oldHotelId);
}

void setHName(Hotel *hotel, char *name) {
    char *oldName = name;
    hotel->name = strdup(name);
    free(oldName);
}

void setHStars(Hotel *hotel, char stars) {
    hotel->stars = stars;
}
/*
void setHAddress(Hotel *hotel, char *address) {
    char *oldAddress = address;
    hotel->address = strdup(address);
    free(oldAddress);
}
*/
void setHCityTax(Hotel *hotel, int cityTax) {
    hotel->cityTax = cityTax;
}

void addToHotelRatingsSum(Hotel *hotel, char rating) {
    if (rating != '\0') {
        hotel->ratingsSum += (double) (rating - '0');
    }
}

void addToHotelNumberRatings(Hotel *hotel, char rating) {
    if (rating != '\0') {
        hotel->numberRatings += 1;
    }
}

void removeHId(Hotel *hotel) {
//    char *oldHotelId = hotel->id;
    hotel->id = NULL;
//    free(oldHotelId);
}

void removeHName(Hotel *hotel) {
//    char *oldHotelName = hotel->name;
    hotel->name = NULL;
//    free(oldHotelName);
}
/*
void removeHAddress(Hotel *hotel) {
//    char *oldHotelAddress = hotel->address;
    hotel->address = NULL;
//    free(oldHotelAddress);
}
*/
void destroyHotel(void *hotel) {
    if (hotel == NULL) return;
//    free(((Hotel *) hotel)->reservationsByDate);
//    destroyOrdList(((Hotel *) hotel)->reservationsByDate, destroyReservation);
    //free(((Hotel *) hotel)->address);
    free(((Hotel *) hotel)->name);
    free(((Hotel *) hotel)->id);
    free(hotel);
}
