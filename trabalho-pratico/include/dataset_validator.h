#ifndef _DATASET_VALIDATOR_
#define _DATASET_VALIDATOR_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "catalogsManager.h"

#define PASSENGERS_PER_FLIGHT_HASHTABLE_INI_SIZE 10000

int exist_file (char* file_path);
int base_e_expoente (int base, int expoente);
int string_to_int (char* string);
void remove_new_line (char* string);

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

int valid_hotel_stars (char *hotel_stars);
int is_non_negative_integer (char* city_tax);
int is_positive_integer (char* price_per_night);
int valid_includes_breakfast (char* includes_breakfast);
int valid_rating (char* rating);
int valid_reservation (char* id_reservation, char* id_user, char* id_hotel, char* hotel_name, char* hotel_stars, char* city_tax, char* address, char* begin_date, char* end_date, char* price_per_night, char* includes_breakfast, char* rating,UsersManager* usersCatalog);

int valid_origin_or_destination (char* local);
int valid_par_of_origin_and_destination (char* origin, char* destination);

typedef struct passengers_per_flight PassengersPerFlight;
PassengersPerFlight *createPassengersPerFlight ();
void destroyPassengersPerFlight (void* passengers_per_flight);

typedef struct passengers_counter PassengersCounter;
PassengersCounter *createPassengersCounter (int size);
void addPassengersPerFlight_ToPassengersCounter (PassengersCounter* passengers_counter, PassengersPerFlight* passengers_per_flight, unsigned int key, char* id_flight);
int existsPassengersPerFlight (PassengersCounter* passengers_counter, char* id_flight);
void addPassenger_ToPassengersPerFlight (PassengersCounter* passengers_counter, unsigned int key, char *id);
int getPassengersNumber (PassengersCounter* passengers_counter, unsigned int key, char *id);
void destroyPassengersCounter (PassengersCounter* passengers_counter);

void count_passengers (char* directory, UsersManager* usersCatalog, PassengersCounter* passengers_counter);
int valid_total_seats (char* total_seats,PassengersCounter* passengers_counter, char* id_flight);

int valid_flight (char* id_flight, char* airline, char* plane_model, char* total_seats, char* origin, char* destination, char* schedule_departure_date, char* schedule_arrival_date, char* real_departure_date, char* real_arrival_date, char* pilot, char* copilot, PassengersCounter* passengers_counter);
int valid_passenger (char* id_flight, char* id_user, UsersManager* usersCatalog, FlightsManager* flightsCatalog);

void add_invalid_line_to_error_file (char* file_path, char* string_line);

#endif