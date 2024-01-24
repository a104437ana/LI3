#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hotel.h"

struct hotel {
    char *name;
    char stars;
    int cityTax;
    OrdList *reservationsByDate;
    double ratingsSum;
    int numberRatings;
};
//função que cria um novo hotel
Hotel *createHotel(char *id, char *name, char stars, int cityTax) {
    Hotel *hotel = malloc(sizeof(Hotel)); //aloca espaço em memória para o hotel
    hotel->name = strdup(name);
    hotel->stars = stars;
    hotel->cityTax = cityTax;
    hotel->ratingsSum = 0;
    hotel->numberRatings = 0;
    hotel->reservationsByDate = createOrdListInt(); //cria uma lista vazia de reservas do hotel

    return hotel;
}
//função que adiciona uma reserva à lista de reservas de um hotel
void addReservationToHotel(Hotel *hotel, unsigned long int id_reserv, char rating) {
    addOrdListInt(hotel->reservationsByDate, id_reserv);
    if (rating != '\0') {
        hotel->ratingsSum += (double) (rating - '0');
        hotel->numberRatings += 1;
    }
}

//gets
char *getHotelName(Hotel *hotel) {
    return strdup(hotel->name); 
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

int getHotelCityTaxId(char *id, Hashtable *hotels) {
    Hotel *hotel = getData(hotels, id);
    return hotel->cityTax;
}

int getHotelCityTax(Hotel *hotel) {
    return hotel->cityTax;
}

//retorna o id da reserva num certo indíce da lista
unsigned long int getHotelReservId(Hotel *hotel, int index) {
    unsigned long int id = getValueOrdList(hotel->reservationsByDate, index);
    return id;
}

int getHotelNumberOfReservations(Hotel* hotel) {
    return getOrdListSize(hotel->reservationsByDate);
}

OrdList *getHotelOrdList(Hotel *hotel) {
    return hotel->reservationsByDate;
}

//sets
void setHName(Hotel *hotel, char *name) {
    char *oldName = name;
    hotel->name = strdup(name);
    free(oldName);
}

void setHStars(Hotel *hotel, char stars) {
    hotel->stars = stars;
}

void setHCityTax(Hotel *hotel, int cityTax) {
    hotel->cityTax = cityTax;
}

//função que liberta o espaço em memória de um hotel
void destroyHotel(void *hotel) {
    if (hotel == NULL) return; //se o hotel não existir
    free(((Hotel *) hotel)->name); //liberta espaço dos diferentes campos do hotel
    destroyOrdListInt(((Hotel *) hotel)->reservationsByDate);
    free(hotel);
}

//sort
void sortHotelReservationsByDate_hotel(Hotel *hotel, void (*radixsortReservsDate)(void*,void*), void *lookup) {
    OrdList *list = hotel->reservationsByDate; //obtem lista de reservas
    if(!isOrdered(list)) {
        heapsortInt(list, intcmpReverse, NULL, 0);
        radixsortReservsDate(list, lookup);
        setOrdListOrd(list, 1);
    }
}
