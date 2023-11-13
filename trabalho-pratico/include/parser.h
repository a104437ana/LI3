#ifndef _PARSER_
#define _PARSER_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utility.h"
#include "dataset_validator.h"

enum Type_file {
    users,
    flights,
    passengers,
    reservations
};

int exist_file (char* path_file);
Date string_to_date (char* string);
void parse_file (char* path_directory, enum Type_file type_file);
void parse_all_files (char* path_directory);

#endif