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
User *createUser(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus);
//adiciona uma reserva ao utilizador
void addReservationToUser(User *user, void *reservation, Hashtable *hotels);
//adiciona um voo ao utilizador
void addFlightToUser(User *user, void *flight);
//ordena a lista de voos e reservas de um utilizador
void sortUserList(void *data, Hashtable *lookupTable);

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
bool getAccountStatus(User* user);
int getNumberFlights(User* user);
int getNumberReservations(User* user);

//sets
void setName(Hashtable *hashtable, unsigned int key, char *name, char *id);
void setGender(Hashtable *hashtable, unsigned int key, Gender gender, char *id);
void setCountry(Hashtable *hashtable, unsigned int key, char *country, char *id);
//void setAdress(Hashtable *hashtable, unsigned int key, char *address, char *id);
void setPassport(Hashtable *hashtable, unsigned int key, char *passport, char *id);
void setBirth(Hashtable *hashtable, unsigned int key, Date *birth, char *id);
//void setEmail(Hashtable *hashtable, unsigned int key, char *email, char *id);
//void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber, char *id);
void setAccountCreation(Hashtable *hashtable, unsigned int key, Date *accountCreation, char *id);

//liberta espaço em memória do utilizador
void destroyUser(void *user);

#endif
