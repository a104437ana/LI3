#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"
#include "hotel.h"
#include "hotelsManager.h"
#include "hashtable.h"

struct reservation {
    char *id_user;
    char *id_hotel;
    Date begin;
    Date end;
    int pricePerNight;
    bool includesBreakfast;
    char userClassification;
};
//função que cria uma nova reserva dados os dados da mesma
Reservation *createReservation(char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification) {
    Reservation *reservation = malloc(sizeof(Reservation)); //aloca espaço em memória para a reserva
    reservation->id_user = strdup(id_user);
    reservation->id_hotel = strdup(id_hotel);
    stringToDate(&(reservation->begin), begin);
    stringToDate(&(reservation->end), end);
    reservation->pricePerNight = pricePerNight;
    reservation->includesBreakfast = includesBreakfast;
    reservation->userClassification = userClassification;

    return reservation; //retorna o apontador para a nova reserva
}

//gets dos campos da reserva
char *getReservUserId(Reservation *reservation) {
    return strdup(reservation->id_user);
}

char *getReservHotelId(Reservation *reservation) {
    return strdup(reservation->id_hotel);
}

int getReservCityTax(Reservation *reservation, Hashtable *hotels) {
    return getHotelCityTaxId(reservation->id_hotel, hotels);
}

int getReservPricePerNight(Reservation *reservation) {
    return reservation->pricePerNight;
}

int getReservUserClassification(Reservation *reservation) {
    return (reservation->userClassification-'0');
}

Date *getReservBegin(Reservation *reservation) {
    Date *date = dupDate(&(reservation->begin));
    return date;
}

Date *getReservEnd(Reservation *reservation) {
    Date *date = dupDate(&(reservation->end));
    return date;
}

int getReservBeginDay(void *reservation, void *lookup) {
    int res = getDay(&(((Reservation*)reservation)->begin));
    return res;
}

int getReservBeginMonth(void *reservation, void *lookup) {
    int res = getMonth(&(((Reservation*)reservation)->begin));
    return res;
}

int getReservBeginYear(void *reservation, void *lookup) {
    int res = getYear(&(((Reservation*)reservation)->begin));
    return res;
}

int getReservationBegin_reservation(int time, Reservation *reservation) {
    int res;
    switch (time) {
        case 0:
            res = getDay(&(reservation->begin));
            break;
        case 1:
            res = getMonth(&(reservation->begin));
            break;
        case 2:
            res = getYear(&(reservation->begin));
            break;
        default:
            res = 0;
    }
    return res;
}

int getReservEndDay(void *reservation) {
    int res = getDay(&(((Reservation*)reservation)->end));
    return res;
}

int getReservEndMonth(void *reservation) {
    int res = getMonth(&(((Reservation*)reservation)->end));
    return res;
}

int getReservEndYear(void *reservation) {
    int res = getYear(&(((Reservation*)reservation)->end));
    return res;
}

bool getReservIncludesBreakfast(Reservation *reservation) {
    return reservation->includesBreakfast;
}

//calcula o número de noites de uma reserva
int getReservNights(Reservation* reservation){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = getDay(end) - getDay(begin);
     free(end);
     free(begin);
     return res;
}
//calcula o número de noites de uma reserva com datas limites
int getReservNightsWithLimits(Reservation* reservation, Date *limitBegin, Date *limitEnd){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = daysInsideDates(limitBegin, limitEnd, begin, end);
     destroyDate(begin);
     destroyDate(end);
     return res;
}

char *getStringReservDate(Reservation *reservation) {
    char *date = dateToStringNoHours(&(reservation->begin));
    return date;
}

//função que liberta o espaço em memória alocado pela reserva
void destroyReservation(void *reservation) {
    if (reservation == NULL) return; //se a reserva não existir
    free(((Reservation *) reservation)->id_hotel);
    free(((Reservation *) reservation)->id_user);
    free(reservation);
}

//sort
int compareReservDates(Reservation *reservation, Date *date) {
    Date *reservDate = &(reservation->end);
    return compareDates(reservDate, date);
}
