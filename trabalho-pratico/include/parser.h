#ifndef _PARSER_
#define _PARSER_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#include "dataset_validator.h"

void parse_users_file (char* directory,UsersManager *usersCatalog);
void parse_reservations_file (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog);
void parse_flights_file (char* directory, UsersManager* usersCatalog, FlightsManager* flightsCatalog,PassengersCounter* passengers_counter);
void parse_passengers_file (char* directory, UsersManager* usersCatalog, FlightsManager* flightsCatalog);
void parse_all_files (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog);

#endif