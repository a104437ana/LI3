#include <stdio.h>
#include <stdlib.h>
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "usersManager.h"
#include "hashtable.h"

struct reservationsManager {
    Hashtable *reservations;
    OrdList * reservationsByBeginDate;
};
//função que cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size) {
    ReservationsManager *reservationsManager = malloc(sizeof(ReservationsManager));
    reservationsManager->reservations = createHashtable(size);
    reservationsManager->reservationsByBeginDate = createOrdList();
    return reservationsManager;
}
//função que adiciona uma reserva ao catálogo de reservas
void addReservToCatalog(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog) {
    //adiciona reserva ao catalogo de reservas
    unsigned int key = hashFunction(id);
    Reservation *reservation = createReservation(id, id_user, id_hotel, begin, end, pricePerNight, includesBreakfast, userClassification);
    reservationsCatalog->reservations = addHashtable(reservationsCatalog->reservations, key, reservation, id);
    addOrdList(reservationsCatalog->reservationsByBeginDate, strdup(id));
}

OrdList * getReservByBeginDate (ReservationsManager *reservations){
    return (reservations->reservationsByBeginDate);
}

//função que liberta o espaço em memória alocado pelo catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager) {
    if (reservationsManager == NULL) return;
    destroyHashtable(reservationsManager->reservations, destroyReservation);
    destroyOnlyOrdList(reservationsManager->reservationsByBeginDate);
    free(reservationsManager);
}

//queries
char * reservation_catalog_compute_Q1 (char *id, ReservationsManager* reservationsManager, QueryResult* result) {
    Reservation* reservation = getData(reservationsManager->reservations,hashFunction(id),id);
    char * hotel_id;
    if (reservation == NULL) {
        hotel_id = NULL;
    }
    else {
        hotel_id = getReservHotelId(reservation); 
        if (hotel_id != NULL){
        setNumberResults(result,1);
        setNumberFieldsQ(result, 0, 8);
        char * field0 = strdup("hotel_id");
        Date* begin_date = getReservBegin(reservation);
        Date* end_date = getReservEnd(reservation);
        char * begin = dateToStringNoHours(begin_date); char * field3 = strdup("begin_date");
        char * end = dateToStringNoHours(end_date); char * field4 = strdup("end_date");
        int includes_breakfast = getReservIncludesBreakfast(reservation);
        char * breakfast;
        if (includes_breakfast==0) breakfast = strdup("False"); else breakfast = strdup("True"); char * field5 = strdup("includes_breakfast");
        int number_of_nights = getReservNights(reservation);
        char * nNightsS = malloc(sizeof(char)*4);
        sprintf(nNightsS, "%d", number_of_nights); char * field6 = strdup("nights");

        setFieldQ(result, 0, 0, field0, hotel_id);
        setFieldQ(result, 0, 3, field3, begin); 
        setFieldQ(result, 0, 4, field4, end); 
        setFieldQ(result, 0, 5, field5, breakfast);
        setFieldQ(result, 0, 6, field6, nNightsS); 
        //os outros campos são preenchidos pela hotel_catalog_compute_Q1 e catalogs_compute_Q1_reservation

        destroyDate(begin_date); destroyDate(end_date); free(begin); free(end); free(breakfast); free(nNightsS);
        free(field0); free(field3); free(field4); free(field5); free(field6);
        }
    }
    return hotel_id;
}

int getReservationsQ10(int year, int month, int day, ReservationsManager * reservations){
    int i; int res = 0; char * id;
    int size = getOrdListSize(reservations->reservationsByBeginDate);
    OrdList * list = reservations->reservationsByBeginDate;
    if (day!=-1){
        for (i=0; i<size; i++){
            id = strdup(getDataOrdList(list, i));
            Reservation* reservation = getData(getHashtableReservCatalog(reservations),hashFunction(id),id);
            if (getReservBeginYear(reservation)==year){
                if (getReservBeginMonth(reservation)==month){
                    if (getReservBeginDay(reservation)==day) res++;
                    else if (getReservBeginDay(reservation)>day) break;
                }
                else if (getReservBeginMonth(reservation)>month) break;
            }
            else if (getReservBeginYear(reservation)>year) break;
        }
    }
    else if (month!=-1){
        for (i=0; i<size; i++){
            id = strdup(getDataOrdList(list, i));
            Reservation* reservation = getData(getHashtableReservCatalog(reservations),hashFunction(id),id);
            if (getReservBeginYear(reservation)==year){
                if (getReservBeginMonth(reservation)==month) res++;
                else if (getReservBeginMonth(reservation)>month) break;
            }
            else if (getReservBeginYear(reservation)>year) break;
        }
    }
    else{
        for (i=0; i<size; i++){
            id = strdup(getDataOrdList(list, i));
            Reservation* reservation = getData(getHashtableReservCatalog(reservations),hashFunction(id),id);
            if (getReservBeginYear(reservation)==year) res++;
            else if (getReservBeginYear(reservation)>year) break;
        }
    }
    free(id);
    return res;
}

//gets
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager) {
    return reservationsManager->reservations;
}

int getReservPriceNoTax(char *id, ReservationsManager *reservationsCatalog) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    int ppn = getReservPricePerNight(reservation);
    int nights = getReservNights(reservation);
    return ppn * nights;
}
int getReservPriceLimits(char *id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    int ppn = getReservPricePerNight(reservation);
    int nights = getReservNightsWithLimits(reservation, limitBegin, limitEnd);
    if (nights < 0) return nights;
    return ppn * nights;
}
int getBReserv(int time, char *id, ReservationsManager *reservationsCatalog) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    return getReservationB(time, reservation);
}
char *getSReservDate(char *id, ReservationsManager *reservationsCatalog) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    return getStringReservDate(reservation);
}
int getBeginDayReservation(char *id, ReservationsManager *reservationsCatalog) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    return getReservBeginDay(reservation);
}
int getBeginMonthReservation(char *id, ReservationsManager *reservationsCatalog) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    return getReservBeginMonth(reservation);
}
int getBeginYearReservation(char *id, ReservationsManager *reservationsCatalog) {
    int key = hashFunction(id);
    Reservation *reservation = getData(reservationsCatalog->reservations, key, id);
    return getReservBeginYear(reservation);
}
