#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "orderedList.h"

//enum gender {
//    MALE,
//    FEMALE,
//};

struct user {
    char *id;
    char *name;             //q1
    Gender gender;          //q1
    char country[2];
    char *address;
    char *passport;       //q1
    Date *birth;        //q1
    char *email;
    PhoneNumber *phoneNumber;
    Date *accountCreation;
    char *paymentMethod;
    bool accounStatus;
    OrdList *flightsByDate;            //q1/q2
    OrdList *reservationsByDate;        //q1/q2     //? Book<id>
    double totalSpent;     //q1        //?
};

User *createUser(char *id, char *name, Gender gender, char country[2], char *address, char *passport, Date *birth, char *email, PhoneNumber *phoneNumber, Date *accountCreation, char *paymentMethod, bool accountStatus) {
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
    user->paymentMethod = strdup(paymentMethod);
    user->accounStatus = accountStatus;
    user->totalSpent = 0;
    user->flightsByDate = createOrdList(USER_FLIGHTS_INI_SIZE);
    user->reservationsByDate = createOrdList(USER_RESERVATIONS_INI_SIZE);

    return user;
}

void addReservationToUser(User *user, void *reservation) {
    addOrdList(user->reservationsByDate, reservation);
}

void addFlightToUser(User *user, void *flight) {
    addOrdList(user->flightsByDate, flight);
}

void sortUserReservationsByDate(void *user) {
    radixSortDate(((User *)user)->reservationsByDate);
}

void sortUserFlightsByDate(void *user) {
    radixSortDate(((User *)user)->flightsByDate);
}

//gets
char *getName(Hashtable *hashtable, unsigned int key) {
    char *name;
    User *data = getData(hashtable, key);
    name = strdup(data->name);

    return name;
}

Gender getGender(Hashtable *hashtable, unsigned int key) {
    Gender gender;
    User *data = getData(hashtable, key);
    gender = data->gender;

    return gender;
}

char *getCountry(Hashtable *hashtable, unsigned int key) {
    char country[2];
    User *data = getData(hashtable, key);
    country[0] = data->country[0];
    country[1] = data->country[1];

    return country;
}

char *getAdress(Hashtable *hashtable, unsigned int key) {
    char *address;
    User *data = getData(hashtable, key);
    address = strdup(data->address);

    return address;
}

char *getPassport(Hashtable *hashtable, unsigned int key) {
    char *passport;
    User *data = getData(hashtable, key);
    passport = strdup(data->passport);

    return passport;
}

Date *getBirth(Hashtable *hashtable, unsigned int key) {
    Date *birth;
    User *data = getData(hashtable, key);
    birth = data->birth;

    return birth;
}

char *getEmail(Hashtable *hashtable, unsigned int key) {
    char *email;
    User *data = getData(hashtable, key);
    email = strdup(data->email);

    return email;
}

PhoneNumber *getPhoneNumber(Hashtable *hashtable, unsigned int key) {
    PhoneNumber *number;
    User *data = getData(hashtable, key);
    number = data->phoneNumber;

    return number;
}

Date *getAccountCreation(Hashtable *hashtable, unsigned int key) {
    Date *accountCreation;
    User *data = getData(hashtable, key);
    accountCreation = data->accountCreation;

    return accountCreation;
}

//sets
void setName(Hashtable *hashtable, unsigned int key, char *name) {
    User *data = getData(hashtable, key);
    char *oldName = data->name;
    data->name = strdup(name);
    free(oldName);
}

void setGender(Hashtable *hashtable, unsigned int key, Gender gender) {
    User *data = getData(hashtable, key);
    data->gender = gender;
}

void setCountry(Hashtable *hashtable, unsigned int key, char *country) {
    User *data = getData(hashtable, key);
    char oldCountry[2];
    oldCountry[0] = data->country[0];
    oldCountry[1] = data->country[1];
    data->country[0] = country[0];
    data->country[1] = country[1];
}

void setAdress(Hashtable *hashtable, unsigned int key, char *address) {
    User *data = getData(hashtable, key);
    char *oldAddress = data->address;
    data->address = strdup(address);
    free(oldAddress);
}

void setPassport(Hashtable *hashtable, unsigned int key, char *passport) {
    User *data = getData(hashtable, key);
    char *oldPassport = data->passport;
    data->passport = strdup(passport);
    free(oldPassport);
}

void setBirth(Hashtable *hashtable, unsigned int key, Date *birth) {
    User *data = getData(hashtable, key);
    data->birth = birth;
}

void setEmail(Hashtable *hashtable, unsigned int key, char *email) {
    User *data = getData(hashtable, key);
    char *oldEmail = data->email;
    data->email = strdup(email);
    free(oldEmail);
}


void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber) {
    User *data = getData(hashtable, key);
    data->phoneNumber = phoneNumber;
}

void setAccountCreation(Hashtable *hashtable, unsigned int key, Date *accountCreation) {
    User *data = getData(hashtable, key);
    data->accountCreation = accountCreation;
}
