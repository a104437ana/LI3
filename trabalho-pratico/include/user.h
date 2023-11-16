#ifndef _USER_
#define _USER_

#include "utility.h"
#include "hashtable.h"
#include "orderedList.h"

#define USER_LIST_INI_SIZE 200

//typedef enum gender {
//    MALE,
//    FEMALE,
//} Gender;
typedef struct user User;

User *createUser(char *id, char *name, Gender gender, char country[2], char *address, char *passport, Date *birth, char *email, PhoneNumber *phoneNumber, Date *accountCreation, char *paymentMethod, bool accountStatus);
void addReservationToUser(User *user, void *reservation);
void addFlightToUser(User *user, void *flight);
void sortUserList(User *user);

//gets e sets fazer get multiplo e set multiplo
//gets
char *getName(User *user);
Gender getGender(User *user);
char *getCountry(User *user);
char *getAdress(User *user);
char *getPassport(User *user);
Date *getBirth(User *user);
char *getEmail(User *user);
PhoneNumber *getPhoneNumber(User *user);
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
void setAdress(Hashtable *hashtable, unsigned int key, char *address, char *id);
void setPassport(Hashtable *hashtable, unsigned int key, char *passport, char *id);
void setBirth(Hashtable *hashtable, unsigned int key, Date *birth, char *id);
void setEmail(Hashtable *hashtable, unsigned int key, char *email, char *id);
void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber, char *id);
void setAccountCreation(Hashtable *hashtable, unsigned int key, Date *accountCreation, char *id);

void destroyUser(void *user);

#endif