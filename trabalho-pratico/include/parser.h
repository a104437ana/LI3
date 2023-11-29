#ifndef _PARSER_
#define _PARSER_

#include "utility.h"
#include "dataset_validator.h"

void parse_file(char* file_path, char* error_file_path, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog, PassengersCounter* passengers_counter);
void parse_all_files (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog);

#endif