#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "flight.h"
#include "reservation.h"
#include "orderedList.h"
#include "queries.h"

//enum gender {
//    MALE,
//    FEMALE,
//};

struct user {
    char *id;
    char *name;             //q1
    Gender gender;          //q1
    char country[3];
    //char *address;
    char *passport;       //q1
    Date *birth;        //q1
    //char *email;
    //PhoneNumber *phoneNumber;
    Date *accountCreation;
    //char *paymentMethod;
    bool accounStatus;          
    OrdList *flightsReservationsByDate;      
    double totalSpent;     //q1        //?
    int nFlights;
    int nReservations;
};

User *createUser(char *id, char *name, Gender gender, char country[3], /*char *address,*/ char *passport, Date *birth, /*char *email, PhoneNumber *phoneNumber,*/ Date *accountCreation, /*char *paymentMethod,*/ bool accountStatus) {
    User *user = malloc(sizeof(User));
    user->id = strdup(id);
    user->name = strdup(name);
    user->gender = gender;
    memcpy(user->country, country, 3);
//    user->country[0] = country[0];
//    user->country[1] = country[1];
    //user->address = strdup(address);
    user->passport = strdup(passport);
    user->birth = birth;
    //user->email = strdup(email);
    //user->phoneNumber = phoneNumber;
    user->accountCreation = accountCreation;
    //user->paymentMethod = strdup(paymentMethod);
    user->accounStatus = accountStatus;
    user->totalSpent = 0;
    user->flightsReservationsByDate = createOrdList(USER_LIST_INI_SIZE);
    user->nFlights=0;
    user->nReservations=0;

    return user;
}

void addReservationToUser(User *user, void *reservation) {
    ResultQ2* res = malloc(sizeof(ResultQ2));
    res->resultType=RESERVATIONS;
    res->result = reservation;
    addOrdList(user->flightsReservationsByDate, res);
    user->nReservations++;
    user->totalSpent+=getReservPrice((Reservation*)reservation);
}

void addFlightToUser(User *user, void *flight) {
    ResultQ2* res = malloc(sizeof(ResultQ2));
    res->resultType=FLIGHTS;
    res->result = flight;
    addOrdList(user->flightsReservationsByDate, res);
    user->nFlights++;
}

int compareFlightReservsIds(void *data1, void *data2) {
    char *id1 = getIdResultQ2((ResultQ2 *)data1), *id2 = getIdResultQ2((ResultQ2 *)data2);
    return strcoll(id1, id2);
}

void sortUserList(void *data) {
    User *user = (User *) data;
    OrdList *list = user->flightsReservationsByDate;
    quickSort(list, 0, getOrdListSize(list)-1, compareFlightReservsIds, 0);
    reverseOrdList(list);
    radixSortUserList(list);
}

//gets
char *getName(User *user) {
    char *name;
    name = user->name; //falta encapsulamento

    return name;
}

Gender getGender(User *user) {
    Gender gender;
    gender = user->gender;

    return gender;
}

char *getCountry(User *user) {
    char *country; //falta encapsulamento
    country = user->country;

    return country;
}
/*
char *getAdress(User *user) {
    char *address;
    address = user->address; //falta encapsulamento

    return address;
}
*/
char *getPassport(User *user) {
    char *passport;
    passport = user->passport; //falta encapsulamento

    return passport;
}

Date *getBirth(User *user) {
    Date *birth;
    birth = user->birth;

    return birth;
}
/*
char *getEmail(User *user) {
    char *email;
    email = user->email; //falta encapsulamento

    return email;
}

PhoneNumber *getPhoneNumber(User *user) {
    PhoneNumber *number;
    number = user->phoneNumber;

    return number;
}
*/
Date *getAccountCreation(User *user) {
    Date *accountCreation;
    accountCreation = user->accountCreation;

    return accountCreation;
}

char *getUserId(User *user) {
    return user->id; //falta encapsulamento
}

double getTotalSpent(User* user) {
    return user->totalSpent;
}

OrdList * getUserList(User* user){
     OrdList* list = user->flightsReservationsByDate;
     return(list);
}

bool getAccountStatus(User* user){
    return(user->accounStatus);
}

int getNumberFlights(User* user){
    return(user->nFlights);
}

int getNumberReservations(User* user){
    return (user->nReservations);
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
/*
void setAdress(Hashtable *hashtable, unsigned int key, char *address, char *id) {
    User *data = getData(hashtable, key, id);
    char *oldAddress = data->address;
    data->address = strdup(address);
    free(oldAddress);
}
*/
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
/*
void setEmail(Hashtable *hashtable, unsigned int key, char *email, char *id) {
    User *data = getData(hashtable, key, id);
    char *oldEmail = data->email;
    data->email = strdup(email);
    free(oldEmail);
}


void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber, char *id) {
    User *data = getData(hashtable, key, id);
    destroyPhoneNumber(data->phoneNumber);
    data->phoneNumber = phoneNumber;
}
*/
void setAccountCreation(Hashtable *hashtable, unsigned int key, Date *accountCreation, char *id) {
    User *data = getData(hashtable, key, id);
    destroyDate(data->accountCreation);
    data->accountCreation = accountCreation;
}

void destroyUser(void *user) {
    if (user == NULL) return;
    destroyDate(((User *)user)->birth);
    destroyDate(((User *) user)->accountCreation);
    //destroyPhoneNumber(((User *) user)->phoneNumber);
    //free(((User *) user)->paymentMethod);
    //free(((User *) user)->email);
    free(((User *) user)->passport);
    //free(((User *) user)->address);
//    free(((User *) user)->country);
    free(((User *) user)->name);
    free(((User *) user)->id);
    destroyOrdList(((User *) user)->flightsReservationsByDate, destroyResultQ2);
    free(user);
}
