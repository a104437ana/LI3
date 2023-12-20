#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "reservation.h"
#include "hotel.h"
#include "hotelsManager.h"
#include "hashtable.h"

struct reservation {
    char *id;
    char *id_user;
    char *id_hotel;
    Date *begin;
    Date *end;
    int pricePerNight;
    bool includesBreakfast;
    char userClassification;
};
//função que cria uma nova reserva dados os dados da mesma
Reservation *createReservation(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, UsersManager *usersCatalog, Hashtable *hotels) {
    Reservation *reservation = malloc(sizeof(Reservation)); //aloca espaço em memória para a reserva
    reservation->id = strdup(id); //aloca espaço para os diferentes campos da reserva
    reservation->id_user = strdup(id_user);
    reservation->id_hotel = strdup(id_hotel);
    Date *beginDate = string_to_date(begin);
    reservation->begin = beginDate;
    Date *endDate = string_to_date(end);
    reservation->end = endDate;
    reservation->pricePerNight = pricePerNight;
    reservation->includesBreakfast = includesBreakfast;
    reservation->userClassification = userClassification;
    int userKey = hashFunction(id_user);
    User *user = getUserCatalog(usersCatalog, userKey, id_user);
    addReservationToUser(user, reservation, hotels);

    return reservation; //retorna o apontador para a nova reserva
}

//gets dos campos da reserva
Reservation *getReservCatalog(Hashtable *reservations, unsigned int key, char *id) {
    Reservation *reservation = (Reservation *) getData(reservations, key, id);
    return reservation;
}

char *getReservId(Reservation *reservation) {
    return reservation->id; //falta encapsulamento
}

char *getReservUserId(Reservation *reservation) {
    return reservation->id_user; //encapsulamento
}

char *getReservHotelId(Reservation *reservation) {
    return reservation->id_hotel;
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

Date *getReservBegin(Reservation *reservation) {
    return reservation->begin;
}

Date *getReservEnd(Reservation *reservation) {
    return reservation->end;
}

int getReservBeginDayId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return reservation->begin->day;
}

int getReservBeginMonthId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return reservation->begin->month;
}

int getReservBeginYearId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return reservation->begin->year;
}

int getReservUserClassificationId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return (reservation->userClassification-'0');
}

char *getReservUserIdId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return reservation->id_user;
}

Date *getReservBeginId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return reservation->begin;
}

Date *getReservEndId(void *id, Hashtable *lookupTable) {
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
    return reservation->end;
}

double getReservPriceId(void *id, Hashtable *lookupTable, Hashtable *hotels){
    unsigned int key = hashFunction(id);
    Reservation *reservation = getData(lookupTable, key, id);
     int ppn = getReservPricePerNight(reservation); //preço por noite
     int nnights = getReservNights(reservation); //número de noites
     int cityTax = getReservCityTax(reservation, hotels); //taxa turística
     double res = (ppn*nnights)+(((float)(ppn*nnights)/100)*cityTax);
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

bool getReservIncludesBreakfast(Reservation *reservation) {
    return reservation->includesBreakfast;
}

//calcula o número de noites de uma reserva
int getReservNights(Reservation* reservation){
     Date* begin = getReservBegin(reservation);
     Date* end = getReservEnd(reservation);
     int res = (end->day) - (begin->day);
     return res;
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
    free(((Reservation *) reservation)->id);
    free(reservation);
}
