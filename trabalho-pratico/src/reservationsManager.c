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
    addHashtable(reservationsCatalog->reservations, key, reservation, id);
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
