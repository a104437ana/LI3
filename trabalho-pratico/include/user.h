#ifndef _USER_
#define _USER_

#include "utility.h"
#include "hashtable.h"
#include "orderedList.h"

#define USER_FLIGHTS_INI_SIZE 100
#define USER_RESERVATIONS_INI_SIZE 100

//typedef enum gender {
//    MALE,
//    FEMALE,
//} Gender;
typedef struct user User;

User *createUser(char *id, char *name, Gender gender, char country[2], char *address, char *passport, Date *birth, char *email, PhoneNumber *phoneNumber, Date *accountCreation, char *paymentMethod, bool accountStatus);
void addReservationToUser(User *user, void *reservation);
void addFlightToUser(User *user, void *flight);
void sortUserReservationsByDate(void *user);
void sortUserFlightsByDate(void *user);

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
OrdList * getFlightsByDate(User* user);
OrdList * getReservationsByDate(User* user);

//sets
void setName(Hashtable *hashtable, unsigned int key, char *name);
void setGender(Hashtable *hashtable, unsigned int key, Gender gender);
void setCountry(Hashtable *hashtable, unsigned int key, char *country);
void setAdress(Hashtable *hashtable, unsigned int key, char *address);
void setPassport(Hashtable *hashtable, unsigned int key, char *passport);
void setBirth(Hashtable *hashtable, unsigned int key, Date *birth);
void setEmail(Hashtable *hashtable, unsigned int key, char *email);
void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber *phoneNumber);
void setAccountCreation(Hashtable *hashtable, unsigned int key, Date *accountCreation);

#endif