#include "results.h"
struct results {
    int Q1type;
    ResultQ1_user* resultQ1_user;
    ResultQ1_flight* resultQ1_flight;
    ResultQ1_reservation* resultQ1_reservation;
    ResultQ3* resultQ3;
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

Results *createResults() {
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

    return results;
}

void destroyResults (Results* results) {
  free(results->resultQ1_user);
  free(results->resultQ1_flight);
  free(results->resultQ1_reservation);
  free(results->resultQ3);
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