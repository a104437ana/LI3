#include <stdio.h>
#include "catalogsManager.h"

struct catalogsManager {
    UsersManager *usersManager;
    FlightsManager *flightsManager;
    ReservationsManager *reservationsManager;
//    HotelsManager *hotelsManager;
//    AirportsManager *airportsManager;
};
