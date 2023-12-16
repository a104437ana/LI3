#ifndef _PARSER_
#define _PARSER_

#include "utility.h"
#include "dataset_validator.h"

void parse_file(char* file_path, char* error_file_path, Catalogs *catalogs, PassengersCounter* passengers_counter);
void parse_all_files (char* directory, Catalogs *catalogs);

#endif