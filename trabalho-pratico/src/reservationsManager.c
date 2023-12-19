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
char* reservation_catalog_compute_Q1 (char *id, ReservationsManager* reservationsManager, Results* results) {
    Reservation* reservation = getData(reservationsManager->reservations,hashFunction(id),id);
    char* hotel_id;
    if (reservation == NULL) {
        setQ1type(results,0);
        hotel_id = NULL;
    }
    else {
        setQ1type(results,3);
        hotel_id = getReservHotelId(reservation);
        Date* begin_date = getReservBegin(reservation);
        Date* end_date = getReservEnd(reservation);
        int includes_breakfast = getReservIncludesBreakfast(reservation);
        int number_of_nights = getReservNights(reservation);
        int pricePerNight = getReservPricePerNight(reservation);
        setHotelIdQ1(results,hotel_id);
        setBeginDateQ1(results,begin_date);
        setEndDateQ1(results,end_date);
        setIncludesBreakfastQ1(results,includes_breakfast);
        setNnightsQ1(results,number_of_nights);
        setTotalPriceQ1(results,pricePerNight);
    }
    return hotel_id;
}
