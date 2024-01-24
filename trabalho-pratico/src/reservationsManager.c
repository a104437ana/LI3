#include <stdio.h>
#include <stdlib.h>
#include "reservationsManager.h"
#include "reservation.h"

struct reservationsManager {
    HashtableInt *reservations;
    OrdList * reservationsByBeginDate;
};
//função que cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size) {
    ReservationsManager *reservationsManager = malloc(sizeof(ReservationsManager));
    reservationsManager->reservations = createHashtableInt(size, destroyReservation);
    reservationsManager->reservationsByBeginDate = createOrdList();
    return reservationsManager;
}
//função que adiciona uma reserva ao catálogo de reservas
int addReservToCatalog(unsigned long int id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog) {
    //adiciona reserva ao catalogo de reservas
    Reservation *reservation = createReservation(id_user, id_hotel, begin, end, pricePerNight, includesBreakfast, userClassification);
    reservationsCatalog->reservations = addHashtableInt(reservationsCatalog->reservations, reservation, id);
    addOrdList(reservationsCatalog->reservationsByBeginDate, reservation);
    int ppn = getReservPricePerNight(reservation);
    int nights = getReservNights(reservation);
    return ppn * nights;
}

//gets
//retorna o ano da primeira reserva da lista
int getFirstReservationBeginYear_reservationsCatalog(ReservationsManager *reservationsCatalog) {
    Reservation *reserv = getDataOrdList(reservationsCatalog->reservationsByBeginDate, 0);
    return getReservBeginYear(reserv, NULL);
}

//retorna o ano da última reserva da lista
int getLastReservationBeginYear_reservationsCatalog(ReservationsManager *reservationsCatalog) {
    OrdList *list = reservationsCatalog->reservationsByBeginDate;
    Reservation *reserv = getDataOrdList(list, getOrdListSize(list)-1);
    return getReservBeginYear(reserv, NULL);
}

//calcula o preço da reserva entre duas datas limite
int getReservPriceLimits(unsigned long int id, ReservationsManager *reservationsCatalog, Date *limitBegin, Date *limitEnd) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    int ppn = getReservPricePerNight(reservation);
    int nights = getReservNightsWithLimits(reservation, limitBegin, limitEnd);
    if (nights < 0) return nights;
    return ppn * nights;
}
//retorna o tempo de início da reserva
int getReservationBegin_reservationsCatalog(int time, unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservationBegin_reservation(time, reservation);
}
//retorna o incício da reserva em string
char *getSReservDate(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getStringReservDate(reservation);
}
//data de início
int getBeginDayReservation(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservBeginDay(reservation, NULL);
}
int getBeginMonthReservation(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservBeginMonth(reservation, NULL);
}
int getBeginYearReservation(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservBeginYear(reservation, NULL);
}
//data de fim
int getEndDayReservation(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservEndDay(reservation);
}
int getEndMonthReservation(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservEndMonth(reservation);
}
int getEndYearReservation(unsigned long int id, ReservationsManager *reservationsCatalog) {
    Reservation *reservation = getDataInt(reservationsCatalog->reservations, id);
    return getReservEndYear(reservation);
}

HashtableInt *getHashtableReservCatalog(ReservationsManager *reservationsManager) {
    return reservationsManager->reservations;
}

//função que liberta o espaço em memória alocado pelo catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager) {
    if (reservationsManager == NULL) return;
    destroyHashtableInt(reservationsManager->reservations);
    destroyOnlyOrdList(reservationsManager->reservationsByBeginDate);
    free(reservationsManager);
}

//sort
void radixSortReservDate(OrdList *list, void *lookupTable) {
    radixSort(list, getReservBeginDay, lookupTable, 31, 0);
    radixSort(list, getReservBeginMonth, lookupTable, 12, 0);
    radixSort(list, getReservBeginYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

void sortReservationsByBeginDate(ReservationsManager *reservationsCatalog) {
    OrdList * list = reservationsCatalog->reservationsByBeginDate;
    if(!isOrdered(list)) {
        radixSortReservDate(list, NULL); //ordena as reservas por data
        setOrdListOrd(list, 1);
    }
}

//compara uma data com o início de uma reserva
int compareDates_reservation(void *date, void *reserv, void *reservationsCatalog) {
    Date * d = (Date *) date;
    Date * reservDate = getReservBegin((Reservation *) reserv);
    int res = compareDates(reservDate, d);
    destroyDate(reservDate);
    return res;
}
//compara uma data com o início de uma reserva, sem considerar o dia
int compareMonths_reservation(void *date, void *reserv, void *reservationsCatalog) {
    Date * d = (Date *) date;
    Date * reservDate = getReservBegin((Reservation *) reserv);
    int month1 = getMonth(d), year1 = getYear(d);
    int month2 = getMonth(reservDate), year2 = getYear(reservDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    else if (month1 > month2) res = 1;
    else if (month2 > month1) res = -1;
    destroyDate(reservDate);
    return res;
}
//compara uma data com o início de uma reserva, só considerando o ano
int compareYears_reservation(void *date, void *reserv, void *reservationsCatalog) {
    Date * d = (Date *) date;
    Date * reservDate = getReservBegin((Reservation *) reserv);
    int year1 = getYear(d);
    int year2 = getYear(reservDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    destroyDate(reservDate);
    return res;
}

//queries

//calcula as informações de uma reserva para a query 1
char * reservation_catalog_compute_Q1 (char *id, int* price_per_night, int* nights, ReservationsManager* reservationsManager, QueryResult* result) {
    unsigned long int key = reservIdToInt(id);
    Reservation* reservation = getDataInt(reservationsManager->reservations,key);
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

//calcula o número de reservas com início numa data para a query 10
int getReservationsQ10(int year, int month, int day, ReservationsManager * reservations){
    int res = 0;
    OrdList * list = reservations->reservationsByBeginDate;
    Date * date = malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    if (day!=-1){ //se a data tiver dia
        int i = searchDataOrdList(list, date, compareDates_reservation, reservations, 0, compareDates_reservation); //primeira reserva nessa data
        if (i>=0){ //se existir alguma reserva nessa data
            int size = getOrdListSize(list);
            int exit = 0;
            Reservation * reserv;
            while (i < size && !exit) {
                reserv = getDataOrdList(list, i);
                if (compareDates_reservation(date, reserv, reservations) != 0) exit = 1; //se a data da reserva for maior que a pedida
                else {
                    i++;
                    res++; //incrementa o número de reservas
                }
            }
        }
    }
    else if (month!=-1){ //se não for considerado o dia
        int i = searchDataOrdList(list, date, compareMonths_reservation, reservations, 0, compareMonths_reservation); //primeira reserva nessa data
        if (i>=0){ //se existir alguma reserva nessa data
            int size = getOrdListSize(list);
            int exit = 0;
            Reservation * reserv;
            while (i < size && !exit) {
                reserv = getDataOrdList(list, i);
                if (compareMonths_reservation(date, reserv, reservations) != 0) exit = 1; //se a data da reserva for maior que a pedida
                else {
                    i++;
                    res++; //incrementa o número de reservas
                }
            }
        }
    }
    else if (year!=-1){ //se só for considerado o ano
        int i = searchDataOrdList(list, date, compareYears_reservation, reservations, 0, compareYears_reservation); //primeira reserva nessa data
        if (i>=0){ //se existir alguma reserva nessa data
            int size = getOrdListSize(list);
            int exit = 0;
            Reservation * reserv;
            while (i < size && !exit) {
                reserv = getDataOrdList(list, i);
                if (compareYears_reservation(date, reserv, reservations) != 0) exit = 1; //se a data da reserva for maior que a pedida
                else {
                    i++;
                    res++; //incrementa o número de reservas
                }
            }
        }
    }
    destroyDate(date);
    return res;
}