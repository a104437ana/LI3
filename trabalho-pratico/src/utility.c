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

Date *createDateHours(char day, char month, int year, char hours, char minutes, char seconds) {
    Date *date = malloc(sizeof(Date));
    date->day = day;
    date->month = month;
    date->year = year;
    date->hasHours = 1;
    date->hour = createHour(hours, minutes, seconds);

    return date;
}

Hour *createHour(char hours, char minutes, char seconds) {
    Hour *hour = malloc(sizeof(Hour));
    hour->hours = hours;
    hour->minutes = minutes;
    hour->seconds = seconds;

    return hour;
}

//Transforma uma string num tipo Date
Date* string_to_date (char* string) {
    int year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    Date* date = createDate(day,month,year);

    return date;
}

Date* string_to_date_hours (char* string) {
    int year = (string[0] - '0') * 1000 + (string[1] - '0') * 100 + (string[2] -'0') * 10 + (string[3] - '0');
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    int hours = (string[11] - '0') * 10 + (string[12] - '0');
    int minutes = (string[14] - '0') * 10 + (string[15] - '0');
    int seconds = (string[17] - '0') * 10 + (string[18] - '0');
    Date* date = createDateHours(day,month,year,hours,minutes,seconds);

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
    if (date->hasHours == 0) {
        res = malloc(11);
        sprintf(res, "%04d/%02d/%02d", date->year, date->month, date->day);
    }
    else {
        res = malloc(20);
        sprintf(res, "%04d/%02d/%02d %02d:%02d:%02d", date->year, date->month, date->day, date->hour->hours, date->hour->minutes, date->hour->seconds);
    }
    return res;
}

int string_to_day(char* string) {
    int day = (string[8] - '0') * 10 + (string[9] - '0');
    return day;
}

int string_to_month(char* string) {
    int month = (string[5] - '0') * 10 + (string[6] - '0');
    return month;
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
