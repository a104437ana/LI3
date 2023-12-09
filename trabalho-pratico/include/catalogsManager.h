#ifndef _CATALOG_MANAGER_
#define _CATALOG_MANAGER_

#include "usersManager.h"
#include "reservationsManager.h"
#include "hotelsManager.h"
#include "flightsManager.h"
#include "airportsManager.h"

typedef struct catalogs Catalogs;
//funções não implementadas

//ordena todos os catálogos
void sortCatalogs(UsersManager *usersManager, HotelsManager *hotelsManager);

//liberta o espaço em memória de todos os catálogos
void destroyCatalogs(UsersManager *usersManager, ReservationsManager *reservationsManager, HotelsManager *hotelsManager, FlightsManager *flightsManager);

#endif