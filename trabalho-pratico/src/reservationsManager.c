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
    reservationsManager->reservations = createHashtable(size, hashFunction, strcmpVoid, strdupVoid, destroyReservation);
    reservationsManager->reservationsByBeginDate = createOrdList();
    return reservationsManager;
}
//função que adiciona uma reserva ao catálogo de reservas
void addReservToCatalog(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog) {
    //adiciona reserva ao catalogo de reservas
    Reservation *reservation = createReservation(id, id_user, id_hotel, begin, end, pricePerNight, includesBreakfast, userClassification);
    reservationsCatalog->reservations = addHashtable(reservationsCatalog->reservations, reservation, id);
    addOrdList(reservationsCatalog->reservationsByBeginDate, strdup(id));
}

OrdList * getReservByBeginDate (ReservationsManager *reservations){
    return (reservations->reservationsByBeginDate);
}

//função que liberta o espaço em memória alocado pelo catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager) {
    if (reservationsManager == NULL) return;
    destroyHashtable(reservationsManager->reservations);
    destroyOnlyOrdList(reservationsManager->reservationsByBeginDate);
    free(reservationsManager);
}

//queries
char * reservation_catalog_compute_Q1 (char *id, int* price_per_night, int* nights, ReservationsManager* reservationsManager, QueryResult* result) {
    Reservation* reservation = getData(reservationsManager->reservations,id);
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

        *price_per_night = getReservPricePerNight(reservation);
        *nights = number_of_nights;
        }
    }
    return hotel_id;
}

int compareDates_reservation(void *date, void *id, void *reservationsCatalog) {
    Date * d = (Date *) date;
    Hashtable *reservations = ((ReservationsManager *) reservationsCatalog)->reservations;
    Date * reservDate = getReservationBeginDate(id, (void *) reservations);
    int day1 = getDay(d), month1 = getMonth(d), year1 = getYear(d);
    int day2 = getDay(reservDate), month2 = getMonth(reservDate), year2 = getYear(reservDate);
    if (year1 > year2) return 1;
    else if (year2 > year1) return -1;
    else if (month1 > month2) return 1;
    else if (month2 > month1) return -1;
    else if (day1 > day2) return 1;
    else if (day2 > day1) return -1;
    else return 0;
}

int compareMonths_reservation(void *date, void *id, void *reservationsCatalog) {
    Date * d = (Date *) date;
    Hashtable *reservations = ((ReservationsManager *) reservationsCatalog)->reservations;
    Date * reservDate = getReservationBeginDate(id, (void *) reservations);
    int month1 = getMonth(d), year1 = getYear(d);
    int month2 = getMonth(reservDate), year2 = getYear(reservDate);
    if (year1 > year2) return 1;
    else if (year2 > year1) return -1;
    else if (month1 > month2) return 1;
    else if (month2 > month1) return -1;
    else return 0;
}

int compareYears_reservation(void *date, void *id, void *reservationsCatalog) {
    Date * d = (Date *) date;
    Hashtable *reservations = ((ReservationsManager *) reservationsCatalog)->reservations;
    Date * reservDate = getReservationBeginDate(id, (void *) reservations);
    int year1 = getYear(d);
    int year2 = getYear(reservDate);
    if (year1 > year2) return 1;
    else if (year2 > year1) return -1;
    else return 0;
}


int getReservationsQ10(int year, int month, int day, ReservationsManager * reservations){
    int res = 0;
    OrdList * list = reservations->reservationsByBeginDate;
    Date * date = malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    if (day!=-1){
        int i = searchDataOrdList(list, date, compareDates_reservation, reservations, 0, compareDates_reservation, 0);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            char * id;
            while (i < size && !exit) {
                id = strdup (getDataOrdList(list, i));
                if (compareDates_reservation(date, id, reservations) != 0) exit = 1;
                else {
                    i++;
                    res++;
                }
            }
            free(id);
        }
    }
    else if (month!=-1){
        int i = searchDataOrdList(list, date, compareMonths_reservation, reservations, 0, compareMonths_reservation, 0);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            char * id;
            while (i < size && !exit) {
                id = strdup (getDataOrdList(list, i));
                if (compareMonths_reservation(date, id, reservations) != 0) exit = 1;
                else {
                    i++;
                    res++;
                }
            }
            free(id);
        }
    }
    else if (year!=-1){
        int i = searchDataOrdList(list, date, compareYears_reservation, reservations, 0, compareYears_reservation, 0);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            char * id;
            while (i < size && !exit) {
                id = strdup (getDataOrdList(list, i));
                if (compareYears_reservation(date, id, reservations) != 0) exit = 1;
                else {
                    i++;
                    res++;
                }
            }
            free(id);
        }
    }
    destroyDate(date);
    return res;
}

//gets
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager) {
    return reservationsManager->reservations;
}

int getReservPriceNoTax(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    int ppn = getReservPricePerNight(reservation);
    int nights = getReservNights(reservation);
    return ppn * nights;
}
int getReservPriceLimits(char *id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    int ppn = getReservPricePerNight(reservation);
    int nights = getReservNightsWithLimits(reservation, limitBegin, limitEnd);
    if (nights < 0) return nights;
    return ppn * nights;
}
int getBReserv(int time, char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservationB(time, reservation);
}
char *getSReservDate(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getStringReservDate(reservation);
}
int getBeginDayReservation(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservBeginDay(reservation);
}
int getBeginMonthReservation(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservBeginMonth(reservation);
}
int getBeginYearReservation(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservBeginYear(reservation);
}
int getEndDayReservation(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservEndDay(reservation);
}
int getEndMonthReservation(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservEndMonth(reservation);
}
int getEndYearReservation(char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return getReservEndYear(reservation);
}
int compareReservDates_reservationsCatalog(Date *date, char *id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getData(reservationsCatalog->reservations, id);
    return compareReservDates(reservation, date);
}
