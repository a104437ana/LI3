#include <stdio.h>
#include <stdlib.h>
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "usersManager.h"
#include "hashtable.h"

struct reservationsManager {
    Hashtable *reservations;
};
//função que cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size) {
    ReservationsManager *reservationsManager = malloc(sizeof(ReservationsManager));
    reservationsManager->reservations = createHashtable(size);
    return reservationsManager;
}
//função que adiciona uma reserva ao catálogo de reservas
void addReservToCatalog(char *id, char *id_user, char *id_hotel, char *begin, char *end, int pricePerNight, bool includesBreakfast, char userClassification, ReservationsManager *reservationsCatalog, UsersManager *usersCatalog, Hashtable *hotels) {
    //adiciona reserva ao catalogo de reservas
    unsigned int key = hashFunction(id);
    Reservation *reservation = createReservation(id, id_user, id_hotel, begin, end, pricePerNight, includesBreakfast, userClassification, usersCatalog, hotels);
    reservationsCatalog->reservations = addHashtable(reservationsCatalog->reservations, key, reservation, id);
}

//gets
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager) {
    return reservationsManager->reservations;
}

//função que imprime o id de uma reserva, para efeitos de teste
void printFunctionReservation(void *data) {
    char *reservId = getReservId((Reservation *) data);
    printf(" %8s)", reservId);
    free(reservId);
}
//função que imprime o catálogo de reservas, para efeitos de teste
void printReservations(ReservationsManager *reservationsManager) {
    printTable(reservationsManager->reservations, printFunctionReservation);
    printHashtableUsage(reservationsManager->reservations);
}

//função que liberta o espaço em memória alocado pelo catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager) {
    if (reservationsManager == NULL) return;
    destroyHashtable(reservationsManager->reservations, destroyReservation);
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
