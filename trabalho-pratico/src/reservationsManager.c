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
void addReservToCatalog(ReservationsManager *reservationsManager, Reservation *reservation, unsigned int key, HotelsManager *hotelsManager, UsersManager *usersManager) {
    //adiciona reserva ao catalogo de reservas
    addHashtable(reservationsManager->reservations, key, reservation, getReservId(reservation));
    //adiciona reserva à lista de reservas do hotel
    //adiciona reserva à lista de reservas do utilizador
    int userKey = getReservUserKey(reservation);
    User *user = getUserCatalog(usersManager, userKey, getReservUserId(reservation));
    addReservationToUser(user, reservation);
}

//gets
Reservation *getReservCatalog(ReservationsManager *reservationsManager, unsigned int key, char *id) {
    Reservation *reservation = (Reservation *) getData(reservationsManager->reservations, key, id);
    return reservation;
}

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
