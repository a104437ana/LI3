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

int getDay(Date *date) {
    return (int) date->day;
}

int getMonth(Date *date) {
    return (int) date->month;
}

int getYear(Date *date) {
    return date->year;
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
    char* res;
    sprintf(res, "%d/%d/%d", date->year, date->month, date->day);
    return res;
}