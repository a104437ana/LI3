#ifndef _UTILITY_
#define _UTILITY_

#include <stdbool.h>
//adicionar validacao
typedef struct hour {
    char hours;
    char minutes;
    char seconds;
} Hour;

typedef struct data {
    int year;
    char month;
    char day;
    bool hasHours;
    Hour hour;
} Date;

typedef struct phoneNumber {
    char indicative[3];
    char number[9];
} PhoneNumber;

typedef enum gender {
    MALE,
    FEMALE,
} Gender;

#endif