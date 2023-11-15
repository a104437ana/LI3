#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "flight.h"
#include "reservation.h"
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
    memcpy(user->country, country, 2);
//    user->country[0] = country[0];
//    user->country[1] = country[1];
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
char *getName(User *user) {
    char *name;
    name = strdup(user->name);

    return name;
}

Gender getGender(User *user) {
    Gender gender;
    gender = user->gender;

    return gender;
}

char *getCountry(User *user) {
    char *country = malloc(sizeof(char) * 2);
    memcpy(country, user->country, 2);

    return country;
}

char *getAdress(User *user) {
    char *address;
    address = strdup(user->address);

    return address;
}

char *getPassport(User *user) {
    char *passport;
    passport = strdup(user->passport);

    return passport;
}

Date *getBirth(User *user) {
    Date *birth;
    birth = user->birth;

    return birth;
}

char *getEmail(User *user) {
    char *email;
    email = strdup(user->email);

    return email;
}

PhoneNumber *getPhoneNumber(User *user) {
    PhoneNumber *number;
    number = user->phoneNumber;

    return number;
}

Date *getAccountCreation(User *user) {
    Date *accountCreation;
    accountCreation = user->accountCreation;

    return accountCreation;
}

char *getUserId(User *user) {
    return strdup(user->id);
}

double getTotalSpent(User* user) {
    return user->totalSpent;
}

OrdList * getFlightsByDate(User* user){
     OrdList* flights = user->flightsByDate;
     return(flights);
}

OrdList * getReservationsByDate(User* user){
     OrdList* reservations = user->reservationsByDate;
     return(reservations);
}

bool getAccountStatus(User* user){
    return(user->accounStatus);
}

//sets
void setName(Hashtable *hashtable, unsigned int key, char *name, char *id) {
    User *data = getData(hashtable, key, id);
    char *oldName = data->name;
    data->name = strdup(name);
    free(oldName);
}

void setGender(Hashtable *hashtable, unsigned int key, Gender gender, char *id) {
    User *data = getData(hashtable, key, id);
    data->gender = gender;
}

void setCountry(Hashtable *hashtable, unsigned int key, char *country, char *id) {
    User *data = getData(hashtable, key, id);
    memcpy(data->country, country, 2);
//    char oldCountry[2];
//    oldCountry[0] = data->country[0];
//    oldCountry[1] = data->country[1];
//    data->country[0] = country[0];
//    data->country[1] = country[1];
}

void setAdress(Hashtable *hashtable, unsigned int key, char *address, char *id) {
    User *data = getData(hashtable, key, id);
    char *oldAddress = data->address;
    data->address = strdup(address);
    free(oldAddress);
}

void setPassport(Hashtable *hashtable, unsigned int key, char *passport, char *id) {
    User *data = getData(hashtable, key, id);
    char *oldPassport = data->passport;
    data->passport = strdup(passport);
    free(oldPassport);
}

void setBirth(Hashtable *hashtable, unsigned int key, Date *birth, char *id) {
    User *data = getData(hashtable, key, id);
    data->birth = birth;
}

void setEmail(Hashtable *hashtable, unsigned int key, char *email, char *id) {
    User *data = getData(hashtable, key, id);
    char *oldEmail = data->email;
    data->email = strdup(email);
    free(oldEmail);
}


void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber, char *id) {
    User *data = getData(hashtable, key, id);
    data->phoneNumber = phoneNumber;
}

void setAccountCreation(Hashtable *hashtable, unsigned int key, Date *accountCreation, char *id) {
    User *data = getData(hashtable, key, id);
    data->accountCreation = accountCreation;
}

void destroyUser(void *user) {
    if (user == NULL) return;
//    destroyOrdList(((User *) user)->flightsByDate, destroyFlight);
//    destroyOrdList(((User *) user)->reservationsByDate, destroyReservation);
//    destroyFlights(((User *) user)->flightsByDate);
//    destroyReservations(((User *) user)->reservationsByDate);
    destroyDate(((User *)user)->birth);
    destroyDate(((User *) user)->accountCreation);
    destroyPhoneNumber(((User *) user)->phoneNumber);
    free(((User *) user)->paymentMethod);
    free(((User *) user)->email);
    free(((User *) user)->passport);
    free(((User *) user)->address);
//    free(((User *) user)->country);
    free(((User *) user)->name);
    free(((User *) user)->id);
    free(user);
}
