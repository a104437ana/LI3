#ifndef _RESULTS_
#define _RESULTS_

#include <stdlib.h>
#include <string.h>
#include "utility.h"

typedef struct results Results;

typedef struct resultQ1_user ResultQ1_user;

typedef struct resultQ1_flight ResultQ1_flight;

typedef struct resultQ1_reservation ResultQ1_reservation;

typedef struct resultQ3 ResultQ3;

typedef struct resultQ4 ResultQ4;

typedef struct resultQ4_reservation ResultQ4_reservation;

Results *createResults();

void destroyResults (Results* results);
void clearResultQ4 (Results* results);

int getQ1type (Results* results);
void setQ1type (Results* results, int type);
char* getNameQ1 (Results* results);
void setNameQ1 (Results* results, char* name);
Gender getGenderQ1 (Results* results);
void setGenderQ1 (Results* results, Gender gender);
int getAgeQ1 (Results* results);
void setAgeQ1 (Results* results, int age);
char* getCountryCodeQ1 (Results* results);
void setCountryCodeQ1 (Results* results, char* country_code);
char* getPassportQ1 (Results* results);
void setPassportQ1 (Results* results, char* passport);
int getNflightsQ1 (Results* results);
void setNflightsQ1 (Results* results, int n);
int getNreservsQ1 (Results* results);
void setNreservsQ1 (Results* results, int n);
double getTotalSpentQ1 (Results* results);
void setTotalSpentQ1 (Results* results, double n);
char* getAirlineQ1 (Results* results);
void setAirlineQ1 (Results* results, char* name);
char* getPlaneModelQ1 (Results* results);
void setPlaneModelQ1 (Results* results, char* name);
char* getOriginlQ1 (Results* results);
void setOriginQ1 (Results* results, char* name);
char* getDestlQ1 (Results* results);
void setDestQ1 (Results* results, char* name);
Date* getScheduleDepartureQ1 (Results* results);
void setSheduleDepartureQ1 (Results* results, Date* date);
Date* getScheduleArrivalQ1 (Results* results);
void setSheduleArrivalQ1 (Results* results, Date* date);
int getNpassengersQ1 (Results* results);
void setNpassengersQ1 (Results* results, int n);
double getDelayQ1 (Results* results);
void setDelayQ1 (Results* results, double n);
char* getHotelIdQ1 (Results* results);
void setHotelIdQ1 (Results* results, char* name);
char* getHotelNameQ1 (Results* results);
void setHotelNameQ1 (Results* results, char* name);
int getHotelStarsQ1 (Results* results);
void setHotelStarsQ1 (Results* results, int n);
Date* getBeginDateQ1 (Results* results);
void setBeginDateQ1 (Results* results, Date* date);
Date* getEndDateQ1 (Results* results);
void setEndDateQ1 (Results* results, Date* date);
bool getIncludesBreakfastQ1 (Results* results);
void setIncludesBreakfastQ1 (Results* results, bool n);
int getNnightsQ1 (Results* results);
void setNnightsQ1 (Results* results, int n);
double getTotalPriceQ1 (Results* results);
void setTotalPriceQ1 (Results* results, double n);

double getRating (Results* results);

void setRating (Results* results, double newRating);

void setResultQ4Size (Results* results, int size);
void setResultQ4DataInd (Results* results, char* id, Date* begin_date, Date* end_date, char* user_id, int rating, double total_price , int ind);
int getResultQ4Size (Results* results);
char * getResultQ4IdInd (Results* results, int ind);
Date * getResultQ4BeginInd (Results* results, int ind);
Date * getResultQ4EndInd (Results* results, int ind);
char * getResultQ4UserIdInd (Results* results, int ind);
int getResultQ4RatingInd (Results* results, int ind);
double getResultQ4TotalPriceInd (Results* results, int ind);

#endif