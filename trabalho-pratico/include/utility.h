#ifndef _UTILITY_
#define _UTILITY_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BEGIN_YEAR 1900
#define END_YEAR 2200
#define N_YEARS (END_YEAR - BEGIN_YEAR + 1)

typedef struct date {
    int year;
    char month;
    char day;
    char hours;
    char minutes;
    char seconds;
} Date;

typedef enum gender {
    MALE,
    FEMALE,
} Gender;
//data com horas
Date *createDate(char day, char month, int year);
Date *createDateHours(char day, char month, int year, char hours, char minutes, char seconds);
Date* string_to_date (char* string);
Date* string_to_date_hours (char* string);

int getDay(void *date);
int getMonth(void *date);
int getYear(void *date);
char getSeconds(Date *date);
char getMinutes(Date *date);
char getHours(Date *date);

char* dateToString(Date *date); //cria memory leaks no output (passada como parametro de funções)
char* dateToStringNoHours(Date *date); //cria memory leaks no output (passada como parametro de funções)
int daysBetweenDates(Date *begin, Date *end);
int compareDates(Date *date1, Date *date2);
int strcollNames(char *name1, char *name2);
int strcoll_names(char *name1, char *name2);
void toUpperS (char *word);

void destroyDate(Date *date);

#endif