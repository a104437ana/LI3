#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"
#include "hotel.h"
#include "hotelsManager.h"
#include "hashtable.h"

struct reservation {
//    char *id;
    char *id_user;
    char *id_hotel;
    Date *begin;
    Date *end;
    int pricePerNight;
    bool includesBreakfast;
    char userClassification;
};
//função que cria uma nova reserva dados os dados da mesma
Reservation *createReservation(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification) {
    Reservation *reservation = malloc(sizeof(Reservation)); //aloca espaço em memória para a reserva
//    reservation->id = strdup(id); //aloca espaço para os diferentes campos da reserva
    reservation->id_user = strdup(id_user);
    reservation->id_hotel = strdup(id_hotel);
    Date *beginDate = string_to_date(begin);
    reservation->begin = beginDate;
    Date *endDate = string_to_date(end);
    reservation->end = endDate;
    reservation->pricePerNight = pricePerNight;
    reservation->includesBreakfast = includesBreakfast;
    reservation->userClassification = userClassification;

    return reservation; //retorna o apontador para a nova reserva
}

//gets dos campos da reserva
Reservation *getReservCatalog(Hashtable *reservations, char *id) {
    Reservation *reservation = (Reservation *) getData(reservations, id);
    return reservation;
}

//char *getReservId(Reservation *reservation) {
//    return strdup(reservation->id); //falta encapsulamento
//}

char *getReservUserId(Reservation *reservation) {
    return strdup(reservation->id_user); //encapsulamento
}

char *getReservHotelId(Reservation *reservation) {
    return strdup(reservation->id_hotel);
}

int getReservUserKey(Reservation *reservation) {
    return hashFunction(reservation->id_user);
}
/*
char *getReservHotelName(Reservation *reservation, Hashtable *hotels) {
    return getHotelName(reservation->id_hotel, hotels);
}
*/
int getReservCityTax(Reservation *reservation, Hashtable *hotels) {
    return getHotelCityTax2(reservation->id_hotel, hotels);
}

int getReservPricePerNight(Reservation *reservation) {
    return reservation->pricePerNight;
}

int getReservUserClassification(Reservation *reservation) {
    return (reservation->userClassification-'0');
}
/*
char getReservHotelStars(Reservation *reservation, Hashtable *hotels) {
    return getHotelStars(reservation->id_hotel, hotels);
}*/

Date * getReservationBeginDate(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    return (reservation->begin);
}

Date *getReservBegin(Reservation *reservation) {
    Date * res = malloc(sizeof(Date));
    res->day = reservation->begin->day;
    res->month = reservation->begin->month;
    res->year = reservation->begin->year;
    res->hours = 0;
    res->minutes = 0;
    res->seconds = 0;
    return res;
}

Date *getReservEnd(Reservation *reservation) {
    Date * res = malloc(sizeof(Date));
    res->day = reservation->end->day;
    res->month = reservation->end->month;
    res->year = reservation->end->year;
    res->hours = 0;
    res->minutes = 0;
    res->seconds = 0;
    return res;
}

int getReservBeginDayId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    return reservation->begin->day;
}

int getReservBeginMonthId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    return reservation->begin->month;
}

int getReservBeginYearId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    return reservation->begin->year;
}

int getReservUserClassificationId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    return (reservation->userClassification-'0');
}

char *getReservUserIdId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    char * res = strdup(reservation->id_user);
    return res;
}

Date *getReservBeginId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    Date * res = malloc(sizeof(Date));
    res->day = reservation->begin->day;
    res->month = reservation->begin->month;
    res->year = reservation->begin->year;
    return res;
}

Date *getReservEndId(void *id, void *lookupTable) {
    Reservation *reservation = getData((Hashtable *) lookupTable, id);
    Date * res = malloc(sizeof(Date));
    res->day = reservation->end->day;
    res->month = reservation->end->month;
    res->year = reservation->end->year;
    return res;
}

int getReservBeginDay(void *reservation) {
    return ((Reservation*)reservation)->begin->day;
}

int getReservBeginMonth(void *reservation) {
    return ((Reservation*)reservation)->begin->month;
}

int getReservBeginYear(void *reservation) {
    return ((Reservation*)reservation)->begin->year;
}

int getReservEndDay(void *reservation) {
    return ((Reservation*)reservation)->end->day;
}

int getReservEndMonth(void *reservation) {
    return ((Reservation*)reservation)->end->month;
}

int getReservEndYear(void *reservation) {
    return ((Reservation*)reservation)->end->year;
}

int getReservationB(int time, Reservation *reservation) {
    int res;
    switch (time) {
        case 0:
            res = getDay(reservation->begin);
            break;
        case 1:
            res = getMonth(reservation->begin);
            break;
        case 2:
            res = getYear(reservation->begin);
            break;
        default:
            res = 0;
    }
    return res;
}

bool getReservIncludesBreakfast(Reservation *reservation) {
    return reservation->includesBreakfast;
}

//calcula o número de noites de uma reserva
int getReservNights(Reservation* reservation){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = (end->day) - (begin->day);
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
    return dateToStringNoHours(reservation->begin);
}

int compareReservDates(Reservation *reservation, Date *date) {
    Date *reservDate = reservation->end;
    return compareDates(reservDate, date);
}

//sets dos campos da reserva
//void setUserId(Hashtable *hashtable, unsigned int key, char *id_user, char *reservId) {
//    Reservation *data = getData(hashtable, key, reservId);
//    char *oldUserId = data->id_user;
//    data->id_user = strdup(id_user);
//    free(oldUserId);
//}

//void setHotelId(Hashtable *hashtable, unsigned int key, char *id_hotel, char* id) {
//    Reservation *data = getData(hashtable, key, id);
//    removeHId(data->hotel);
//    setHId(data->hotel, id_hotel);
//}

//void setHotelName(Hashtable *hashtable, unsigned int key, char *hotelName, char* id) {
//    Reservation *data = getData(hashtable, key, id);
//    removeHName(data->hotel);
//    setHName(data->hotel, hotelName);
//}

//void setHotelStars(Hashtable *hashtable, unsigned int key, char hotelStars, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    setHStars(data->hotel, hotelStars);
//}

//void setCityTax(Hashtable *hashtable, unsigned int key, int cityTax, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    setHCityTax(data->hotel, cityTax);
//}

//void setBeginDate(Hashtable *hashtable, unsigned int key, Date *begin, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    data->begin = begin;
//}

//void setEndDate(Hashtable *hashtable, unsigned int key, Date *end, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    data->end = end;
//}

//void setPricePerNight(Hashtable *hashtable, unsigned int key, int pricePerNight, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    data->pricePerNight = pricePerNight;
//}

//void setIncludesBreakfast(Hashtable *hashtable, unsigned int key, bool includesBreakfast, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    data->includesBreakfast = includesBreakfast;
//}

//void setUserClassification(Hashtable *hashtable, unsigned int key, char userClassification, char *id) {
//    Reservation *data = getData(hashtable, key, id);
//    data->userClassification = userClassification;
//}

Date *getBeginDateReservation(void *reservation) {
    return ((Reservation*)reservation)->begin;
}
//função que liberta o espaço em memória alocado pela reserva
void destroyReservation(void *reservation) {
    if (reservation == NULL) return; //se a reserva não existir
//    free(((Reservation *) reservation)->hotel);
//    destroyHotel(((Reservation *) reservation)->hotel);
    destroyDate(((Reservation *) reservation)->begin); //liberta espaço em memória dos diferentes campos
    destroyDate(((Reservation *) reservation)->end);
    //free(((Reservation *) reservation)->userComment);
    //free(((Reservation *) reservation)->roomDetails);
    free(((Reservation *) reservation)->id_hotel);
    free(((Reservation *) reservation)->id_user);
//    free(((Reservation *) reservation)->id);
    free(reservation);
}
