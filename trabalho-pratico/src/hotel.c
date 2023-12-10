#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"
#include "reservation.h"
#include "orderedList.h"
#include "utility.h"

struct hotel {
    char *id;
    char *name;
    char stars;
    //char *address;
    int cityTax;
    OrdList *reservationsByDate;
    double ratingsSum;
    int numberRatings;
};
//função que cria um novo hotel
Hotel *createHotel(char *id, char *name, char stars, /*char *address,*/ int cityTax) {
    Hotel *hotel = malloc(sizeof(Hotel)); //aloca espaço em memória para o hotel
    //hotel->address = strdup(address); //address desaparece
    hotel->id = strdup(id);
    hotel->name = strdup(name);
    hotel->stars = stars;
    hotel->cityTax = cityTax;
    hotel->ratingsSum = 0;
    hotel->numberRatings = 0;
    hotel->reservationsByDate = createOrdList(HOTEL_RESERVATIONS_INI_SIZE); //cria uma lista vazia de reservas do hotel

    return hotel;
}
//função que adiciona uma reserva à lista de reservas de um hotel
void addReservationToHotel(Hotel *hotel, void *reservation) {
    addOrdList(hotel->reservationsByDate, reservation);
}

//função que compara os ids de duas reservas
int compareReservsIds(void *reserv1, void *reserv2) {
    char *id1 = getReservId((Reservation *) reserv1), *id2 = getReservId((Reservation *) reserv2);
    return strcoll(id1, id2);
}
//função que ordena a lista de reservas de um hotel
void sortHotelReservationsByDate(void *hotel) {
    OrdList *reservationsByDate = ((Hotel *) hotel)->reservationsByDate; //obtem lista de reservas
    //ordena as reservas por ids
    quickSort(reservationsByDate, 0, getOrdListSize(reservationsByDate)-1, compareReservsIds, 0);
    reverseOrdList(reservationsByDate); //inverte a lista
    radixSortReservDate(reservationsByDate); //ordena as reservas por data
    setOrdListOrd(reservationsByDate, 1);
}
//função que retorn a lista de reservas de um hotel
OrdList *getHotelOrdList(Hotel *hotel) {
    return hotel->reservationsByDate;
}
//função que retorna o id de uma reserva do hotel
char *getHotelReservation(Hotel *hotel, unsigned int key) {
    void *data = getDataOrdList(hotel->reservationsByDate, 0);
    return getReservId((Reservation*) data);
}

//gets dos campos do hotel
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
//sets dos campos do hotel
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
//função que incrementa a soma de classificações de um hotel
void addToHotelRatingsSum(Hotel *hotel, char rating) {
    if (rating != '\0') {
        hotel->ratingsSum += (double) (rating - '0');
    }
}
//função que incrementa o número de classificações de um hotel
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
//função que liberta o espaço em memória de um hotel
void destroyHotel(void *hotel) {
    if (hotel == NULL) return; //se o hotel não existir
//    free(((Hotel *) hotel)->reservationsByDate);
//    destroyOrdList(((Hotel *) hotel)->reservationsByDate, destroyReservation);
    //free(((Hotel *) hotel)->address);
    free(((Hotel *) hotel)->name); //liberta espaço dos diferentes campos do hotel
    free(((Hotel *) hotel)->id);
    destroyOnlyOrdList(((Hotel *) hotel)->reservationsByDate);
    free(hotel);
}
