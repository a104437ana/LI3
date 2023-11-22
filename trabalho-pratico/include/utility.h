#ifndef _UTILITY_
#define _UTILITY_

#include <stdio.h>
#include <stdlib.h>
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
/*
typedef struct phoneNumber {
    char indicative[3];
    char number[9];
} PhoneNumber;
*/
typedef enum gender {
    MALE,
    FEMALE,
} Gender;
//data com horas
Date *createDate(char day, char month, int year);
Date *createDateHours(char day, char month, int year, char hours, char minutes, char seconds);
Date* string_to_date (char* string);
Date* string_to_date_hours (char* string);
Hour *createHour(char hours, char minutes, char seconds);

int getDay(void *date);
int getMonth(void *date);
int getYear(void *date);
int getDateDay(Date *date);
int getDateMonth(Date *date);
int getDateYear(Date *date);
char getSeconds(Date *date);
char getMinutes(Date *date);
char getHours(Date *date);
void getDayMonthYear(Date *date, int *day, int *month, int *year);

void setDay(Date *date, char day);
void setMonth(Date *date, char month);
void setYear(Date *date, int year);
void setSeconds(Date *date, char seconds);
void setMinutes(Date *date, char minutes);
void setHours(Date *date, char hours);

char* dateToString(Date *date); //cria memory leaks no output (passada como parametro de funções)
char* dateToStringNoHours(Date *date); //cria memory leaks no output (passada como parametro de funções)
int string_to_day(char* string);
int string_to_month(char* string);
int daysBetweenDates(Date *begin, Date *end);
int compareDates(Date *date1, Date *date2);

void destroyDate(Date *date);
//void destroyPhoneNumber(PhoneNumber *phoneNumber);

#endif