#ifndef _RESERVATIONS_MANAGER_
#define _RESERVATIONS_MANAGER_

#include <stdio.h>
#include <stdlib.h>
#include "reservation.h"
#include "hashtable.h"
#include "hotelsManager.h"
#include "usersManager.h"

typedef struct reservationsManager ReservationsManager;
//cria um novo catálogo de reservas
ReservationsManager *createReservsCatalog(int size);
//adiciona uma reserva ao catálogo de reservas
void addReservToCatalog(ReservationsManager *reservationsManager, Reservation *reservation, unsigned int key, HotelsManager *hotelsManager, UsersManager *usersManager);

//gets
Reservation *getReservCatalog(ReservationsManager *reservationsManager, unsigned int key, char *id);
Hashtable *getHashtableReservCatalog(ReservationsManager *reservationsManager);

//imprime o catálogo de reservas
void printReservations(ReservationsManager *reservationsManager);

//liberta o espaço em memória do catálogo de reservas
void destroyreservationsCatalog(ReservationsManager *reservationsManager);

#endif