#ifndef _UTILITY_
#define _UTILITY_

#include <stdbool.h>

#define BEGIN_YEAR 1900
#define END_YEAR 2200
#define N_YEARS (END_YEAR - BEGIN_YEAR + 1)

typedef struct hour {
    char hours;
    char minutes;
    char seconds;
} Hour;

typedef struct date {
    int year;
    char month;
    char day;
    bool hasHours;
    Hour *hour;
} Date;

typedef struct phoneNumber {
    char indicative[3];
    char number[9];
} PhoneNumber;

typedef enum gender {
    MALE,
    FEMALE,
} Gender;
//data com horas
Date *createDate(char day, char month, int year);
Date* string_to_date (char* string);

int getDay(void *date);
int getMonth(void *date);
int getYear(void *date);
char getSeconds(Date *date);
char getMinutes(Date *date);
char getHours(Date *date);

void setDay(Date *date, char day);
void setMonth(Date *date, char month);
void setYear(Date *date, int year);
void setSeconds(Date *date, char seconds);
void setMinutes(Date *date, char minutes);
void setHours(Date *date, char hours);

char* dateToString(Date *date);
int string_to_day(char* string);
int string_to_month(char* string);

void destroyDate(Date *date);
void destroyPhoneNumber(PhoneNumber *phoneNumber);

#endif