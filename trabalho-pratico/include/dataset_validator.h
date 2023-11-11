#ifndef _DATASET_VALIDATOR_
#define _DATASET_VALIDATOR_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum Type_file {
    users,
    fligths,
    passengers,
    reservations
};

int length_bigger_than_zero (char* string);
int valid_email (char* email);
int valid_country_code (char* country_code);
int valid_account_status (char* account_status);
int is_digit (char* n);
int valid_date_ymd (char* date);
int valid_date_ymd_hms (char* date);
int valid_user (char *id, char* name, char* email, char* phone_number, char* birth_date, char* sex, char* passport, char* country_code, char* address, char* account_creation, char* pay_method, char* account_status);
void add_invalid_line_to_error_file (enum Type_file type_file, char* string_line);

#endif