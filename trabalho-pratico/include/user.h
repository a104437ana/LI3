#ifndef _USER_
#define _USER_

#include "utility.h"
#include "hashtable.h"
#include "orderedList.h"

#define USER_LIST_INI_SIZE 200

#define YEAR 2023
#define MONTH 10
#define DAY 01

//typedef enum gender {
//    MALE,
//    FEMALE,
//} Gender;
typedef struct user User;
//cria um novo utilizador
User *createUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice);
//adiciona um voo ou reserva à lista de voos e ereservas de um utilizador
void addToUserList(User *user, int *id, char type, double totalSpent);

//gets
char *getName(User *user);
Gender getGender(User *user);
char *getCountry(User *user);
//char *getAdress(User *user);
char *getPassport(User *user);
Date *getBirth(User *user);
int getAge(User* user);
//char *getEmail(User *user);
//PhoneNumber *getPhoneNumber(User *user);
Date *getAccountCreation(User *user);
char *getUserId(User *user);
double getTotalSpent(User* user);
OrdList * getUserList(User* user);
bool getUserAccountStatus(User* user);
int getUListSize(User * user);
int getNumberFlights(User* user);
int getNumberReservations(User* user);
Date * getUserAccountCreation(void *id, void *lookupTable);
int getAccountCreationDay(void *user);
int getAccountCreationMonth(void *user); 
int getAccountCreationYear(void *user);
int *getUListId(int *type, User *user, int index);
int getIndice (User* user);

//sets
void setName(Hashtable *hashtable, char *name, char *id);
void setGender(Hashtable *hashtable, Gender gender, char *id);
void setCountry(Hashtable *hashtable, char *country, char *id);
//void setAdress(Hashtable *hashtable, unsigned int key, char *address, char *id);
void setPassport(Hashtable *hashtable, char *passport, char *id);
void setBirth(Hashtable *hashtable, Date *birth, char *id);
//void setEmail(Hashtable *hashtable, unsigned int key, char *email, char *id);
//void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber, char *id);
void setAccountCreation(Hashtable *hashtable, Date *accountCreation, char *id);

//liberta espaço em memória do utilizador
void destroyUser(void *user);

#endif
