#include <stdio.h>
#include "catalogsManager.h"

struct catalogsManager {
    UsersManager *usersManager;
    FlightsManager *flightsManager;
    ReservationsManager *reservationsManager;
//    HotelsManager *hotelsManager;
//    AirportsManager *airportsManager;
};

void destroyCatalogs(UsersManager *usersManager, ReservationsManager *reservationsManager, HotelsManager *hotelsManager, FlightsManager *flightsManager) {
    destroyUsersCatalog(usersManager);
    destroyreservationsCatalog(reservationsManager);
    destroyHotelsCatalog(hotelsManager);
    destroyFlightsCatalog(flightsManager);
}
