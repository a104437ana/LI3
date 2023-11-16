#ifndef _PARSER_
#define _PARSER_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"

#include "usersManager.h"
#include "reservationsManager.h"
#include "dataset_validator.h"

int exist_file (char* file_path);
void add_invalid_line_to_error_file (char* file_path, char* string_line);
int base_e_expoente (int base, int expoente);
int string_to_int (char* string);
Date* string_to_date (char* string);
void remove_new_line (char* string);
void parse_users_file (char* directory,UsersManager *usersCatalog,OrdList* user_id_name);
void parse_reservations_file (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog);
void parse_flights_file (char* directory, UsersManager* usersCatalog, FlightsManager* flightsCatalog,Hashtable* passengers_per_flight);
void parse_passengers_file (char* directory, UsersManager* usersCatalog, FlightsManager* flightsCatalog);
void parse_all_files (char* directory, UsersManager* usersCatalog, ReservationsManager* reservationsCatalog, HotelsManager* hotelsCatalog, FlightsManager* flightsCatalog,OrdList* user_id_name);

#endif