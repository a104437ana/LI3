#include <stdio.h>
#include <stdlib.h>
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "usersManager.h"
#include "hashtable.h"

struct reservationsManager {
    Hashtable *reservations;
};

ReservationsManager *createReservsCatalog(int size) {
    ReservationsManager *reservationsManager = malloc(sizeof(ReservationsManager));
    reservationsManager->reservations = createHashtable(size);
    return reservationsManager;
}

void addReservToCatalog(ReservationsManager *reservationsManager, Reservation *reservation, unsigned int key, HotelsManager *hotelsManager, UsersManager *usersManager) {
    //adiciona reserva ao catalogo de reservas
    addHashtable(reservationsManager->reservations, key, reservation);
    //adiciona reserva à lista de reservas do hotel
    Hotel *hotel = getReservHotel(reservation);
    addReservationToHotel(hotel, reservation);
    //adiciona reserva à lista de reservas do utilizador
    if (usersManager != NULL) {
        int userKey = getReservUserKey(reservation);
        User *user = getUserCatalog(usersManager, userKey);
        addReservationToUser(user, reservation);
    }
}

Reservation *getReservCatalog(ReservationsManager *reservationsManager, unsigned int key) {
    Reservation *reservation = (Reservation *) getData(reservationsManager->reservations, key);
    return reservation;
}

Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager) {
    return reservationsManager->reservations;
}
