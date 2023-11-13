#ifndef _RESERVATIONS_MANAGER_
#define _RESERVATIONS_MANAGER_

#include "reservation.h"
#include "hashtable.h"
#include "hotelsManager.h"

typedef struct reservationsManager ReservationsManager;

ReservationsManager *createReservsCatalog(int size);
void addReservToCatalog(ReservationsManager *reservationsManager, Reservation *reservation, unsigned int key, HotelsManager *hotelsManager, UsersManager *usersManager);
//gets
Reservation *getReservCatalog(ReservationsManager *reservationsManager, unsigned int key);
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager);

#endif