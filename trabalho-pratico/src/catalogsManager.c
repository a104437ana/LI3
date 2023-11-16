#include <stdio.h>
#include "catalogsManager.h"
#include "hotelsManager.h"
#include "usersManager.h"

struct catalogsManager {
    UsersManager *usersManager;
    FlightsManager *flightsManager;
    ReservationsManager *reservationsManager;
//    HotelsManager *hotelsManager;
//    AirportsManager *airportsManager;
};

void sortCatalogs(UsersManager *usersManager, HotelsManager *hotelsManager) {
    sortHotelCatalog(hotelsManager);
    sortUserCatalog(usersManager);
}

void destroyCatalogs(UsersManager *usersManager, ReservationsManager *reservationsManager, HotelsManager *hotelsManager, FlightsManager *flightsManager) {
    destroyUsersCatalog(usersManager);
    destroyreservationsCatalog(reservationsManager);
    destroyHotelsCatalog(hotelsManager);
    destroyFlightsCatalog(flightsManager);
}
