#ifndef _USER_
#define _USER_

#include "utility.h"
#include "hashtable.h"
#include "orderedList.h"

#define USER_LIST_INI_SIZE 200

#define YEAR 2023
#define MONTH 10
#define DAY 01

typedef enum{
   FLIGHTS,
   RESERVATIONS,
   BOTH
} Q2Type;
typedef struct resultQ2 ResultQ2;
typedef struct user User;
//cria um novo utilizador
User *createUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice);
//adiciona um voo ou reserva à lista de voos e ereservas de um utilizador
void addToUserList(User *user, unsigned long int id, char type, double totalSpent);
int compareUsersNames_user(User *user1, User *user2);

//gets
char *getName(User *user);
Gender getGender(User *user);
char *getCountry(User *user);
char *getPassport(User *user);
Date *getBirth(User *user);
int getAge(User* user);
Date *getAccountCreation(User *user);
char *getUserId(User *user);
double getTotalSpent(User* user);
OrdList * getUserList(User* user);
bool getUserAccountStatus(User* user);
int getUListSize(User * user);
int getBeginDay(void* data, void *catalog);
int getBeginMonth(void* data, void *catalog);
int getBeginYear(void* data, void *catalog);
int getBeginSeconds(void* data, void *catalog);
int getBeginMinutes(void* data, void *catalog);
int getBeginHours(void* data, void *catalog);
int getIdResultQ2(ResultQ2* data);
Q2Type getResultType(ResultQ2 *data);
void destroyResultQ2(void * data);
int getNumberFlights(User* user);
int getNumberReservations(User* user);
Date * getUserAccountCreation(void *id, void *lookupTable);
int getAccountCreationDay(void *user, void *lookup);
int getAccountCreationMonth(void *user, void *lookup); 
int getAccountCreationYear(void *user, void *lookup);
unsigned long int getIdUserList_user(int *type, User *user, int index);
int getIndice (User* user);

//sets
void setName(Hashtable *hashtable, char *name, char *id);
void setGender(Hashtable *hashtable, Gender gender, char *id);
void setCountry(Hashtable *hashtable, char *country, char *id);
void setPassport(Hashtable *hashtable, char *passport, char *id);
void setBirth(Hashtable *hashtable, Date *birth, char *id);
void setAccountCreation(Hashtable *hashtable, Date *accountCreation, char *id);

//liberta espaço em memória do utilizador
void destroyUser(void *user);

#endif
