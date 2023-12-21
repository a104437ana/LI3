#include "results.h"
struct results {
    int Q1type;
    ResultQ1_user* resultQ1_user;
    ResultQ1_flight* resultQ1_flight;
    ResultQ1_reservation* resultQ1_reservation;
    ResultQ3* resultQ3;
    ResultQ4* resultQ4;
    ResultQ7* resultQ7;
};

struct resultQ1_user {
    char* name;
    Gender gender;
    int age;
    char* country_code;
    char* passport;
    int number_of_flights;
    int number_of_reservations;
    double total_spent;
};

struct resultQ1_flight {
    char* airline;
    char* plane_model;
    char* origin;
    char* destination;
    Date* schedule_departure_date;
    Date* schedule_arrival_date;
    int number_of_passengers;
    double delay;
};

struct resultQ1_reservation {
    char* hotel_id;
    char* hotel_name;
    int hotel_stars;
    Date* begin_date;
    Date* end_date;
    bool includes_breakfast;
    int number_of_nights;
    double total_price;
};

struct resultQ3 {
    double rating;
};

struct resultQ4 {
    int size;
    ResultQ4_reservation ** list;
};

struct resultQ4_reservation {
    char* id;
    Date* begin_date;
    Date* end_date;
    char* user_id;
    int rating;
    double total_price;
};

struct resultQ7_airport {
    char*                                                                                                                                                                                                                                                                                                             name;
    double median;
};

struct resultQ7 {
    int size;
    ResultQ7_airport** list;
};

Results * createResults() {
    Results *results = malloc(sizeof(Results));
    results->resultQ1_user = malloc(sizeof(ResultQ1_user));
    results->resultQ1_user->name = strdup("a");
    results->resultQ1_user->country_code = strdup("a");
    results->resultQ1_user->passport = strdup("a");
    results->resultQ1_flight = malloc(sizeof(ResultQ1_flight));
    results->resultQ1_flight->airline = strdup("a");
    results->resultQ1_flight->plane_model = strdup("a");
    results->resultQ1_flight->origin = strdup("a");
    results->resultQ1_flight->destination = strdup("a");
    results->resultQ1_reservation = malloc(sizeof(ResultQ1_reservation));
    results->resultQ1_reservation->hotel_id = strdup("a");
    results->resultQ1_reservation->hotel_name = strdup("a");
    results->resultQ3 = malloc(sizeof(ResultQ3));
    results->resultQ4 = malloc(sizeof(ResultQ4));
    results->resultQ4->size = 0;
    results->resultQ4->list = NULL;
    results->resultQ7 = malloc(sizeof(ResultQ7));
    results->resultQ7->size = 0;
    results->resultQ7->list = NULL;

    return results;
}

void clearResultQ4 (Results* results){
    int i;
    for (i=0; i<results->resultQ4->size; i++){
     free(results->resultQ4->list[i]->id);
     destroyDate(results->resultQ4->list[i]->begin_date);
     destroyDate(results->resultQ4->list[i]->end_date);
     free(results->resultQ4->list[i]->user_id);
     free(results->resultQ4->list[i]);
    }
    free(results->resultQ4->list);
    results->resultQ4->size = 0;
}

void clearResultQ7 (Results* results){
    int i;
    for (i=0; i<results->resultQ7->size; i++){
     free(results->resultQ7->list[i]->name);
     free(results->resultQ7->list[i]);
    }
    free(results->resultQ7->list);
    results->resultQ7->size = 0;
}

void destroyResults (Results* results) {
  free(results->resultQ1_user->name);
  free(results->resultQ1_user->country_code);
  free(results->resultQ1_user->passport);
  free(results->resultQ1_user);
  free(results->resultQ1_flight->airline);
  free(results->resultQ1_flight->plane_model);
  free(results->resultQ1_flight->origin);
  free(results->resultQ1_flight->destination);
  free(results->resultQ1_flight);
  free(results->resultQ1_reservation->hotel_id);
  free(results->resultQ1_reservation->hotel_name);
  free(results->resultQ1_reservation);
  free(results->resultQ3);
  clearResultQ4(results);
  free(results->resultQ4);
  clearResultQ7(results);
  free(results->resultQ7);
  free(results);
}

//Q1

int getQ1type (Results* results) {
    return results->Q1type;
}

void setQ1type (Results* results, int type) {
    results->Q1type = type;
}

char* getNameQ1 (Results* results) {
    return strdup(results->resultQ1_user->name);
}

void setNameQ1 (Results* results, char* name) {
    free(results->resultQ1_user->name);
    results->resultQ1_user->name = strdup(name);
}

Gender getGenderQ1 (Results* results) {
    return results->resultQ1_user->gender;
}

void setGenderQ1 (Results* results, Gender gender) {
    results->resultQ1_user->gender = gender;
}

int getAgeQ1 (Results* results) {
    return results->resultQ1_user->age;
}

void setAgeQ1 (Results* results, int age) {
    results->resultQ1_user->age = age;
}

char* getCountryCodeQ1 (Results* results) {
    return strdup(results->resultQ1_user->country_code);
}

void setCountryCodeQ1 (Results* results, char* country_code) {
    free(results->resultQ1_user->country_code);
    results->resultQ1_user->country_code = strdup(country_code);
}

char* getPassportQ1 (Results* results) {
    return strdup(results->resultQ1_user->passport);
}

void setPassportQ1 (Results* results, char* passport) {
    free(results->resultQ1_user->passport);
    results->resultQ1_user->passport = strdup(passport);
}

int getNflightsQ1 (Results* results) {
    return results->resultQ1_user->number_of_flights;
}

void setNflightsQ1 (Results* results, int n) {
    results->resultQ1_user->number_of_flights = n;
}

int getNreservsQ1 (Results* results) {
    return results->resultQ1_user->number_of_reservations;
}

void setNreservsQ1 (Results* results, int n) {
    results->resultQ1_user->number_of_reservations = n;
}

double getTotalSpentQ1 (Results* results) {
    return results->resultQ1_user->total_spent;
}

void setTotalSpentQ1 (Results* results, double n) {
    results->resultQ1_user->total_spent = n;
}

char* getAirlineQ1 (Results* results) {
    return strdup(results->resultQ1_flight->airline);
}

void setAirlineQ1 (Results* results, char* name) {
    free(results->resultQ1_flight->airline);
    results->resultQ1_flight->airline = strdup(name);
}

char* getPlaneModelQ1 (Results* results) {
    return strdup(results->resultQ1_flight->plane_model);
}

void setPlaneModelQ1 (Results* results, char* name) {
    free(results->resultQ1_flight->plane_model);
    results->resultQ1_flight->plane_model = strdup(name);
}

char* getOriginlQ1 (Results* results) {
    return strdup(results->resultQ1_flight->origin);
}

void setOriginQ1 (Results* results, char* name) {
    free(results->resultQ1_flight->origin);
    results->resultQ1_flight->origin = strdup(name);
}

char* getDestlQ1 (Results* results) {
    return strdup(results->resultQ1_flight->destination);
}

void setDestQ1 (Results* results, char* name) {
    free(results->resultQ1_flight->destination);
    results->resultQ1_flight->destination = strdup(name);
}

Date* getScheduleDepartureQ1 (Results* results) {
    return results->resultQ1_flight->schedule_departure_date;
}

void setSheduleDepartureQ1 (Results* results, Date* date) {
    results->resultQ1_flight->schedule_departure_date = date;
}

Date* getScheduleArrivalQ1 (Results* results) {
    return results->resultQ1_flight->schedule_arrival_date;
}

void setSheduleArrivalQ1 (Results* results, Date* date) {
    results->resultQ1_flight->schedule_arrival_date = date;
}

int getNpassengersQ1 (Results* results) {
    return results->resultQ1_flight->number_of_passengers;
}

void setNpassengersQ1 (Results* results, int n) {
    results->resultQ1_flight->number_of_passengers = n;
}

double getDelayQ1 (Results* results) {
    return results->resultQ1_flight->delay;
}

void setDelayQ1 (Results* results, double n) {
    results->resultQ1_flight->delay = n;
}

char* getHotelIdQ1 (Results* results) {
    return strdup(results->resultQ1_reservation->hotel_id);
}

void setHotelIdQ1 (Results* results, char* name) {
    free(results->resultQ1_reservation->hotel_id);
    results->resultQ1_reservation->hotel_id = strdup(name);
}

char* getHotelNameQ1 (Results* results) {
    return strdup(results->resultQ1_reservation->hotel_name);
}

void setHotelNameQ1 (Results* results, char* name) {
    free(results->resultQ1_reservation->hotel_name);
    results->resultQ1_reservation->hotel_name = strdup(name);
}

int getHotelStarsQ1 (Results* results) {
    return results->resultQ1_reservation->hotel_stars;
}

void setHotelStarsQ1 (Results* results, int n) {
    results->resultQ1_reservation->hotel_stars = n;
}

//
Date* getBeginDateQ1 (Results* results) {
    return results->resultQ1_reservation->begin_date;
}

void setBeginDateQ1 (Results* results, Date* date) {
    results->resultQ1_reservation->begin_date = date;
}

Date* getEndDateQ1 (Results* results) {
    return results->resultQ1_reservation->end_date;
}

void setEndDateQ1 (Results* results, Date* date) {
    results->resultQ1_reservation->end_date = date;
}

bool getIncludesBreakfastQ1 (Results* results) {
    return results->resultQ1_reservation->includes_breakfast;
}

void setIncludesBreakfastQ1 (Results* results, bool n) {
    results->resultQ1_reservation->includes_breakfast = n;
}

int getNnightsQ1 (Results* results) {
    return results->resultQ1_reservation->number_of_nights;
}

void setNnightsQ1 (Results* results, int n) {
    results->resultQ1_reservation->number_of_nights = n;
}

double getTotalPriceQ1 (Results* results) {
    return results->resultQ1_reservation->total_price;
}

void setTotalPriceQ1 (Results* results, double n) {
    results->resultQ1_reservation->total_price = n;
}

//Q3
double getRating (Results* results) {
  return results->resultQ3->rating;
}

void setRating (Results* results, double newRating) {
  results->resultQ3->rating = newRating;
}

//Q4
void setResultQ4Size (Results* results, int size){
    results->resultQ4->size = size;
    results->resultQ4->list = malloc(sizeof(ResultQ4_reservation*)*size);
}

void setResultQ4DataInd (Results* results, char* id, Date* begin_date, Date* end_date, char* user_id, int rating, double total_price , int ind){
    results->resultQ4->list[ind] = malloc(sizeof(ResultQ4_reservation));
    results->resultQ4->list[ind]->id = strdup(id);
    results->resultQ4->list[ind]->begin_date = malloc(sizeof(Date));
    results->resultQ4->list[ind]->begin_date->day = begin_date->day;
    results->resultQ4->list[ind]->begin_date->month = begin_date->month;
    results->resultQ4->list[ind]->begin_date->year = begin_date->year;
    results->resultQ4->list[ind]->end_date = malloc(sizeof(Date));
    results->resultQ4->list[ind]->end_date->day = end_date->day;
    results->resultQ4->list[ind]->end_date->month = end_date->month;
    results->resultQ4->list[ind]->end_date->year = end_date->year;
    results->resultQ4->list[ind]->user_id = strdup(user_id);
    results->resultQ4->list[ind]->rating = rating;
    results->resultQ4->list[ind]->total_price = total_price;
}

int getResultQ4Size (Results* results){
    return results->resultQ4->size;
}

char * getResultQ4IdInd (Results* results, int ind){
    char* res = strdup(results->resultQ4->list[ind]->id);
    return res;
}

Date * getResultQ4BeginInd (Results* results, int ind){
    Date* res = malloc(sizeof(Date));
    res->day = results->resultQ4->list[ind]->begin_date->day;
    res->month = results->resultQ4->list[ind]->begin_date->month;
    res->year = results->resultQ4->list[ind]->begin_date->year;
    return res;
}

Date * getResultQ4EndInd (Results* results, int ind){
    Date* res = malloc(sizeof(Date));
    res->day = results->resultQ4->list[ind]->end_date->day;
    res->month = results->resultQ4->list[ind]->end_date->month;
    res->year = results->resultQ4->list[ind]->end_date->year;
    return res;
}
char * getResultQ4UserIdInd (Results* results, int ind){
    char* res = strdup(results->resultQ4->list[ind]->user_id);
    return res;
}
int getResultQ4RatingInd (Results* results, int ind){
    return (results->resultQ4->list[ind]->rating);
}
double getResultQ4TotalPriceInd (Results* results, int ind){
    return (results->resultQ4->list[ind]->total_price);
}

//Q7

char* getNameQ7 (Results* results, int i) {
    return (strdup(results->resultQ7->list[i]->name));
}

double getMedianQ7 (Results* results, int i) {
    return (results->resultQ7->list[i]->median);
}

int getSizeQ7 (Results* results) {
    return results->resultQ7->size;
}

void setResultQ7 (Results* results,int size) {
    results->resultQ7->list = malloc(sizeof(ResultQ7_airport*)*size);
}

void setNameMedianQ7 (Results* results, int i, char* name, double median) {
    results->resultQ7->list[i]= malloc(sizeof(ResultQ7_airport));
    results->resultQ7->list[i]->name = strdup(name);
    results->resultQ7->list[i]->median = median;
    results->resultQ7->size++;
}