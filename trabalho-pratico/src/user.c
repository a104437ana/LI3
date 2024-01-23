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
    char *name;
    Gender gender;
    char country[3];
    char *passport;
    Date birth;
    Date accountCreation;
    bool accounStatus;          
    OrdList *flightsReservationsByDate;
    double totalSpent;
    int nFlights;
    int nReservations;
    int indice;
};
//função que cria um novo utilizador
User *createUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice) {
    User *user = malloc(sizeof(User)); //aloca espaço a estrutura do utilizador
    user->id = strdup(id); //preenche os diferentes campos com a informação dada
    user->name = strdup(name);
    user->gender = gender;
    memcpy(user->country, country, 3);
    user->passport = strdup(passport);
    stringToDate(&(user->birth), birth);
    stringToDate(&(user->accountCreation), accountCreation);
//    Date *birthDate = string_to_date(birth);
//    user->birth = birthDate;
//    Date *accountCreationDate = string_to_date(accountCreation);
//    user->accountCreation = accountCreationDate;
    user->accounStatus = accountStatus;
    user->totalSpent = 0;
    user->flightsReservationsByDate = createOrdList(); //cria a lista de voos e reservas do utilizador
    user->nFlights=0;
    user->nReservations=0;
    user->indice = indice;

    return user;
}
//adiciona um voo ou reserva à lista de voos e ereservas de um utilizador
void addToUserList(User *user, unsigned long int id, char type, double totalSpent) {
    ResultQ2 *res = malloc(sizeof(ResultQ2));
    if (type == 'R') {
        res->resultType = RESERVATIONS;
        user->nReservations++;
        user->totalSpent += totalSpent;
    }
    else if (type == 'F'){
        res->resultType = FLIGHTS;
        user->nFlights++;
    }
    res->id = id;
    addOrdList(user->flightsReservationsByDate, res);
}

int compareUsersNames_user(User *user1, User *user2) {
    int compare = strcoll(user1->name, user2->name);
    if (compare == 0)
        return strcoll(user1->id, user2->id);
    return compare;
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
    char *country;
    country = strdup(user->country);

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
    passport = strdup(user->passport);

    return passport;
}

Date *getBirth(User *user) {
    Date *birth = malloc(sizeof(Date));
    birth->day = user->birth.day;
    birth->month = user->birth.month;
    birth->year = user->birth.year;
    birth->hours = 0;
    birth->minutes = 0;
    birth->seconds = 0;
    return birth;
}

//calcula a idade de um utilizador em anos
int getAge(User* user){
  Date *birthdate = getBirth(user);
  bool birthday; //se o aniversário do utilizador é ou não antes da data atual
  if(MONTH<birthdate->month) birthday=false;
  else if(MONTH>birthdate->month) birthday=true;
  else{
    if(DAY<birthdate->day) birthday=false;
    else birthday=true;
  }
  int r = 0;
  if(birthday==true) r = YEAR-birthdate->year;
  else r = YEAR-birthdate->year-1;
  destroyDate(birthdate);
  return r;
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

Date * getUserAccountCreation(void *id, void *lookupTable) {
    User *user = getData((Hashtable *) lookupTable,id);
    return (&(user->accountCreation));
}

Date *getAccountCreation(User *user) {
    Date *accountCreation = malloc(sizeof(Date));
    accountCreation->day = user->accountCreation.day;
    accountCreation->month = user->accountCreation.month;
    accountCreation->year = user->accountCreation.year;
    return accountCreation;
}

int getAccountCreationDay(void *user, void *lookup) {
    return ((User*)user)->accountCreation.day;
}

int getAccountCreationMonth(void *user, void *lookup) {
    return ((User*)user)->accountCreation.month;
}

int getAccountCreationYear(void *user, void *lookup) {
    return ((User*)user)->accountCreation.year;
}


char *getUserId(User *user) {
    return strdup(user->id); //falta encapsulamento
}

double getTotalSpent(User* user) {
    return user->totalSpent;
}

OrdList * getUserList(User* user){
     OrdList* list = user->flightsReservationsByDate;
     return(list);
}

bool getUserAccountStatus(User* user){
    return(user->accounStatus);
}

int getUListSize(User * user) {
    return getOrdListSize(user->flightsReservationsByDate);
}

int getNumberFlights(User* user){
    return(user->nFlights);
}

int getNumberReservations(User* user){
    return (user->nReservations);
}

unsigned long int getIdUserList_user(int *type, User *user, int index) {
    OrdList *list = user->flightsReservationsByDate;
    ResultQ2 *res = (ResultQ2 *) getDataOrdList(list, index);
    *type = res->resultType;
    unsigned long int id = res->id;
    return id;
}

int getIndice (User* user) {
    return user->indice;
}
//sets
void setName(Hashtable *hashtable, char *name, char *id) {
    User *data = getData(hashtable, id);
    char *oldName = data->name;
    data->name = strdup(name);
    free(oldName);
}

void setGender(Hashtable *hashtable, Gender gender, char *id) {
    User *data = getData(hashtable, id);
    data->gender = gender;
}

void setCountry(Hashtable *hashtable, char *country, char *id) {
    User *data = getData(hashtable, id);
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
void setPassport(Hashtable *hashtable, char *passport, char *id) {
    User *data = getData(hashtable, id);
    char *oldPassport = data->passport;
    data->passport = strdup(passport);
    free(oldPassport);
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

//função que liberto o espaço em memória de um utilizador
void destroyUser(void *user) {
    if (user == NULL) return; //se o utilizador não existir
//    destroyDate(((User *)user)->birth); //liberta as datas
//    destroyDate(((User *) user)->accountCreation);
    //destroyPhoneNumber(((User *) user)->phoneNumber);
    //free(((User *) user)->paymentMethod);
    //free(((User *) user)->email);
    free(((User *) user)->passport); //liberta as strings
    //free(((User *) user)->address);
//    free(((User *) user)->country);
    free(((User *) user)->name);
    free(((User *) user)->id);
    destroyOrdList(((User *) user)->flightsReservationsByDate, destroyResultQ2);
    free(user);
}
