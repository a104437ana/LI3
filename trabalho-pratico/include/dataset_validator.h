#ifndef _DATASET_VALIDATOR_
#define _DATASET_VALIDATOR_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

enum Type_file;

int length_bigger_than_zero (char* string);
int valid_email (char* email);
int valid_country_code (char* country_code);
int valid_account_status (char* account_status);
int is_digit (char n);
int valid_date_ymd (char* date);
int valid_date_ymd_hms (char* date);
int the_bigger_date (char* date1, char* date2);
int valid_par_of_dates (char* date1, char* date2);
int valid_user (char *id_user, char* name, char* email, char* phone_number, char* birth_date, char* sex, char* passport, char* country_code, char* address, char* account_creation, char* pay_method, char* account_status);

int valid_id_user (char* id_user);

int valid_hotel_stars (char *hotel_stars);
int valid_city_tax (char* city_tax);
int valid_price_per_night (char* price_per_night);
int valid_includes_breakfast (char* includes_breakfast);
int valid_rating (char* rating);
int valid_reservation (char* id_reservation, char* id_user, char* id_hotel, char* hotel_name, char* hotel_stars, char* city_tax, char* address, char* begin_date, char* end_date, char* price_per_night, char* includes_breakfast, char* rating);

int valid_total_seats (char* total_seats);

int valid_origin_or_destination (char* local);
int valid_par_of_origin_and_destination (char* origin, char* destination);
int valid_flight (char* id_flight, char* airline, char* plane_model, char* total_seats, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, char* real_departure_date, char* real_arrival_date, char* pilot, char* copilot);

void add_invalid_line_to_error_file (enum Type_file type_file, char* string_line);

#endif