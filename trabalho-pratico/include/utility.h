#ifndef _UTILITY_
#define _UTILITY_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BEGIN_YEAR 1950
#define END_YEAR 2050
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
int exist_file (char* file_path);
int valid_directory_dataset (char* directory);
int base_e_expoente (int base, int expoente);
int string_to_int (char* string);
void remove_new_line (char* string);

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
int compareDatesNoHours(Date *date1, Date *date2);
int daysInsideDates(Date *limitBegin, Date *limitEnd, Date *begin, Date *end);
int strcollNames(char *name1, char *name2);
int strcoll_names(char *name1, char *name2);
void toUpperS (char *word);
int strcmpVoid(void* s1, void *s2);
void *strdupVoid(void *s);
int intcmpVoid(void *n1, void *n2);
void *intdupVoid(void *n);
char *flightIdToString(int *id);
char *reservIdToString(int *id);
int *flightIdToInt(char *id);
int *reservIdToInt(char *id);

void destroyDate(Date *date);

#endif