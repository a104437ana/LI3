#ifndef _PARSER_
#define _PARSER_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#include "usersManager.h"
#include "reservationsManager.h"
#include "dataset_validator.h"

/*enum Type_file {
    users,
    flights,
    passengers,
    reservations
};*/

enum Type_file;

int exist_file (char* path_file);
Date* string_to_date (char* string);
void parse_file (char* path_directory, enum Type_file type_file, UsersManager* user_catalog, ReservationsManager * reservation_catalog, HotelsManager *hotel_catalog);
void parse_all_files (char* path_directory, UsersManager* user_catalog, ReservationsManager * reservation_catalog, HotelsManager *hotel_catalog);

#endif