#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#include "flight.h"
#include "reservation.h"
#include "orderedList.h"
#include "queries.h"

struct resultQ2{
    unsigned long int id;
    Q2Type resultType; //flight ou reservation
};

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
    if (type == 'R') { //se for uma reserva
        res->resultType = RESERVATIONS;
        user->nReservations++;
        user->totalSpent += totalSpent;
    }
    else if (type == 'F'){ //se for um voo
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
char *getUserId(User *user) {
    return strdup(user->id);
}

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

char *getPassport(User *user) {
    char *passport;
    passport = strdup(user->passport);

    return passport;
}

Date *getBirth(User *user) {
    return dupDate(&user->birth);
}

Date *getAccountCreation(User *user) {
    return dupDate(&(user->accountCreation));
}

bool getUserAccountStatus(User* user){
    return(user->accounStatus);
}

double getTotalSpent(User* user) {
    return user->totalSpent;
}

//número de voos
int getNumberFlights(User* user){
    return(user->nFlights);
}

//número de reservas
int getNumberReservations(User* user){
    return (user->nReservations);
}

//tamanho total da lista
int getUListSize(User * user) {
    return getOrdListSize(user->flightsReservationsByDate);
}

OrdList * getUserList(User* user){
     OrdList* list = user->flightsReservationsByDate;
     return(list);
}

//retorna o id que se encontra numa certa posição da lista
unsigned long int getIdUserList_user(int *type, User *user, int index) {
    OrdList *list = user->flightsReservationsByDate;
    ResultQ2 *res = (ResultQ2 *) getDataOrdList(list, index);
    *type = res->resultType;
    unsigned long int id = res->id;
    return id;
}

//retorna o índice do utilizador
int getIndice (User* user) {
    return user->indice;
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

//devolve o id de uma reserva ou voo
int getIdResultQ2(ResultQ2* data){
  return data->id;
}

//devolve se é um voo ou reserva
Q2Type getResultType(ResultQ2 *data) {
  return data->resultType;
}

//liberta dados do tipo ResultQ2
void destroyResultQ2(void * data){
  free((ResultQ2*)data);
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
}

void setPassport(Hashtable *hashtable, char *passport, char *id) {
    User *data = getData(hashtable, id);
    char *oldPassport = data->passport;
    data->passport = strdup(passport);
    free(oldPassport);
}

//função que liberto o espaço em memória de um utilizador
void destroyUser(void *user) {
    if (user == NULL) return; //se o utilizador não existir
    free(((User *) user)->passport); //liberta as strings
    free(((User *) user)->name);
    free(((User *) user)->id);
    destroyOrdList(((User *) user)->flightsReservationsByDate, destroyResultQ2);
    free(user);
}

//sorts
//devolve o dia de início de uma reserva ou de um voo
int getBeginDay(void* data, void *catalog){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(0, res->id, (Catalogs *) catalog));
  else return (getReservationBegin(0, res->id, (Catalogs *) catalog));
}

//devolve o mês de início de uma reserva ou de um voo
int getBeginMonth(void* data, void *catalog){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(1, res->id, (Catalogs *) catalog));
  else return (getReservationBegin(1, res->id, (Catalogs *) catalog));
}

//devolve o ano de início de uma reserva ou de um voo
int getBeginYear(void* data, void *catalog){
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(2, res->id, (Catalogs *) catalog));
  else return (getReservationBegin(2, res->id, (Catalogs *) catalog));
}

//devolve o segundo de início de um voo
int getBeginSeconds(void* data, void *catalog) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(3, res->id, (Catalogs *) catalog));
  else return (0);
}

//devolve o minuto de início de um voo
int getBeginMinutes(void* data, void *catalog) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(4, res->id, (Catalogs *) catalog));
  else return (0);
}

//devolve a hora de início de um voo
int getBeginHours(void* data, void *catalog) {
  ResultQ2* res = (ResultQ2*) data;
  if (res->resultType == FLIGHTS) return (getFlightScheduleDepartureTime(5, res->id, (Catalogs *) catalog));
  else return (0);
}

//devolve o dia da criação da conta
int getAccountCreationDay(void *user, void *lookup) {
    return ((User*)user)->accountCreation.day;
}

//devolve o mês da criação da conta
int getAccountCreationMonth(void *user, void *lookup) {
    return ((User*)user)->accountCreation.month;
}

//devolve o ano da criação da conta
int getAccountCreationYear(void *user, void *lookup) {
    return ((User*)user)->accountCreation.year;
}
