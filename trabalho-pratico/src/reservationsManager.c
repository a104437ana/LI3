#include <stdio.h>
#include <stdlib.h>
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "hashtable.h"

struct reservationsManager {
    Hashtable *reservations;
};

ReservationsManager *createReservsCatalog(int size) {
    ReservationsManager *reservationsManager = malloc(sizeof(ReservationsManager));
    reservationsManager->reservations = createHashtable(size);
    return reservationsManager;
}
//acabar
void addReservToCatalog(ReservationsManager *reservationsManager, Reservation *reservation, unsigned int key, HotelsManager *hotelsManager, UsersManager *usersManager) {
    addHashtable(reservationsManager->reservations, key, reservation);
    Hotel *hotel = getReservHotel(reservation);
    addReservationToHotel(hotel, reservation);
    int userKey = getReservsUserKey(reservation);
    User *user = getUserCatalog(usersManager, userKey);
    addReservationToUser(user, reservation)
}

Reservation *getReservCatalog(ReservationsManager *reservationsManager, unsigned int key) {
    Reservation *reservation = (Reservation *) getData(reservationsManager->reservations, key);
    return reservation;
}

Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager) {
    return reservationsManager->reservations;
}
