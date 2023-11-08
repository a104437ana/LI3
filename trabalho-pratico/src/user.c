#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

struct user {
    char *id;
    char *name;             //q1
    Gender gender;          //q1
    char country[2];
    char *address;
    char *passport;       //q1
    Date birth;        //q1
    char *email;
    PhoneNumber phoneNumber;
    Date accountCreation;
    int *id_flight;            //q1/q2
    int *id_reservation;        //q1/q2     //? Book<id>
    double totalSpent;     //q1        //?
};

// gets e sets em vez de criar user completo por causa do apontador para a struct ?
User *createUser(char *id, char *name, Gender gender, char country[2], char *address, char *passport, Date birth, char *email, PhoneNumber phoneNumber, Date accountCreation) {
    User *user = malloc(sizeof(User));
    user->id = strdup(id);
    user->name = strdup(name);
    user->gender = gender;
    user->country[0] = country[0];
    user->country[1] = country[1];
    user->address = strdup(address);
    user->passport = strdup(passport);
    user->birth = birth;
    user->email = strdup(email);
    user->phoneNumber = phoneNumber;
    user->accountCreation = accountCreation;

    return user;
}

void addUserFlight(char *id, int id_flight) {
}

void addUserReservation(char *id, int id_reservation) {
}

//gets
char *getName(Hashtable *hashtable, unsigned int key) {
    char *name;
    User *data = getDate(hashtable, key);
    name = strdup(data->name);

    return name;
}

Gender getGender(Hashtable *hashtable, unsigned int key) {
    Gender gender;
    User *data = getDate(hashtable, key);
    gender = data->gender;

    return gender;
}

char *getCountry(Hashtable *hashtable, unsigned int key) {
    char country[2];
    User *data = getDate(hashtable, key);
    country[0] = data->country[0];
    country[1] = data->country[1];

    return country;
}

char *getAdress(Hashtable *hashtable, unsigned int key) {
    char *address;
    User *data = getDate(hashtable, key);
    address = strdup(data->address);

    return address;
}

char *getPassport(Hashtable *hashtable, unsigned int key) {
    char *passport;
    User *data = getDate(hashtable, key);
    passport = strdup(data->passport);

    return passport;
}

Date getBirth(Hashtable *hashtable, unsigned int key) {
    Date birth;
    User *data = getDate(hashtable, key);
    birth = data->birth;

    return birth;
}

char *getEmail(Hashtable *hashtable, unsigned int key) {
    char *email;
    User *data = getDate(hashtable, key);
    email = strdup(data->email);

    return email;
}

PhoneNumber getPhoneNumber(Hashtable *hashtable, unsigned int key) {
    PhoneNumber number;
    User *data = getDate(hashtable, key);
    number = data->phoneNumber;

    return number;
}

Date getAccountCreation(Hashtable *hashtable, unsigned int key) {
    Date accountCreation;
    User *data = getDate(hashtable, key);
    accountCreation = data->accountCreation;

    return accountCreation;
}

//sets
void setName(Hashtable *hashtable, unsigned int key, char *name) {
    User *data = getDate(hashtable, key);
    char *oldName = data->name;
    data->name = strdup(name);
    free(oldName);
}

void setGender(Hashtable *hashtable, unsigned int key, Gender gender) {
    User *data = getDate(hashtable, key);
    data->gender = gender;
}

void setCountry(Hashtable *hashtable, unsigned int key, char *country) {
    User *data = getDate(hashtable, key);
    char oldCountry[2];
    oldCountry[0] = data->country[0];
    oldCountry[1] = data->country[1];
    data->country[0] = country[0];
    data->country[1] = country[1];
}

void setAdress(Hashtable *hashtable, unsigned int key, char *address) {
    User *data = getDate(hashtable, key);
    char *oldAddress = data->address;
    data->address = strdup(address);
    free(oldAddress);
}

void setPassport(Hashtable *hashtable, unsigned int key, char *passport) {
    User *data = getDate(hashtable, key);
    char *oldPassport = data->passport;
    data->passport = strdup(passport);
    free(oldPassport);
}

void setBirth(Hashtable *hashtable, unsigned int key, Date birth) {
    User *data = getDate(hashtable, key);
    data->birth = birth;
}

void setEmail(Hashtable *hashtable, unsigned int key, char *email) {
    User *data = getDate(hashtable, key);
    char *oldEmail = data->email;
    data->email = strdup(email);
    free(oldEmail);
}


void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber phoneNumber) {
    User *data = getDate(hashtable, key);
    data->phoneNumber = phoneNumber;
}

void setAccountCreation(Hashtable *hashtable, unsigned int key, Date accountCreation) {
    User *data = getDate(hashtable, key);
    data->accountCreation = accountCreation;
}
