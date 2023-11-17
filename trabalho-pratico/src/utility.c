#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

Date *createDate(char day, char month, int year) {
    Date *date = malloc(sizeof(Date));
    date->day = day;
    date->month = month;
    date->year = year;
    date->hasHours = 0;
    date->hour = NULL;

    return date;
}

//Transforma uma string num tipo Date
Date* string_to_date (char* string) {
    int year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    Date* date = createDate(day,month,year);
    /*Date* date;
    date.year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    date.month = (string[5] - '0') * 10 + (string[6] - '0');
    date.day = (string[8] - '0') * 10 + (string[9] - '0');
    int hasHours = 0;
    if (strlen(string) == 19) {
        hasHours = 1;
        date.hour->hours = (string[11] -'0') * 10 + (string[12] - '0');
        date.hour->minutes = (string[14] - '0') * 10 + (string[15] - '0');
        date.hour->seconds = (string[17] - '0') * 10 + (string[18] - '0');
    }
    date.hasHours = hasHours;*/
    return date;
}

int getDay(void *date) {
    return (int) ((Date *) date)->day;
}

int getMonth(void *date) {
    return (int) ((Date *) date)->month;
}

int getYear(void *date) {
    return ((Date *) date)->year;
}

char getSeconds(Date *date) {
    return date->hour->seconds;
}

char getMinutes(Date *date) {
    return date->hour->minutes;
}

char getHours(Date *date) {
    return date->hour->hours;
}

void setDay(Date *date, char day) {
    date->day = day;
}

void setMonth(Date *date, char month) {
    date->month = month;
}

void setYear(Date *date, int year) {
    date->year = year;
}

void setSeconds(Date *date, char seconds) {
    date->hour->seconds = seconds;
}

void setMinutes(Date *date, char minutes) {
    date->hour->minutes = minutes;
}

void setHours(Date *date, char hours) {
    date->hour->hours = hours;
}

char* dateToString(Date *date){
    char* res = 0;
    sprintf(res, "%d/%d/%d", date->year, date->month, date->day);
    return res;
}

void destroyDate(Date *date) {
    if (date == NULL) return;
    if (date->hour != NULL) free(date->hour);
    free(date);
}

void destroyPhoneNumber(PhoneNumber *phoneNumber) {
    if (phoneNumber == NULL) return;
    free(phoneNumber);
}
