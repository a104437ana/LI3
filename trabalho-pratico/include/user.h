#ifndef _USER_
#define _USER_

#include "utility.h"
#include "hashtable.h"

typedef struct user User;

// melhor forma de criar user garantindo encapsulamento, sem passar todos parametros um a um
User *createUser(char *id, char *name, Gender gender, char country[2], char *address, char *passport, Date birth, char *email, PhoneNumber phoneNumber, Date accountCreation);
void addUserFlight(char *id, int id_flight);
void addUserReservation(char *id, int id_reservation);
//adicionar validacao
//gets e sets fazer get multiplo e set multiplo
//gets
char *getName(Hashtable *hashtable, unsigned int key);
Gender getGender(Hashtable *hashtable, unsigned int key);
char *getCountry(Hashtable *hashtable, unsigned int key);
char *getAdress(Hashtable *hashtable, unsigned int key);
char *getPassport(Hashtable *hashtable, unsigned int key);
Date getBirth(Hashtable *hashtable, unsigned int key);
char *getEmail(Hashtable *hashtable, unsigned int key);
PhoneNumber getPhoneNumber(Hashtable *hashtable, unsigned int key);
Date getAccountCreation(Hashtable *hashtable, unsigned int key);
//sets
void setName(Hashtable *hashtable, unsigned int key, char *name);
void setGender(Hashtable *hashtable, unsigned int key, Gender gender);
void setCountry(Hashtable *hashtable, unsigned int key, char *country);
void setAdress(Hashtable *hashtable, unsigned int key, char *address);
void setPassport(Hashtable *hashtable, unsigned int key, char *passport);
void setBirth(Hashtable *hashtable, unsigned int key, Date birth);
void setEmail(Hashtable *hashtable, unsigned int key, char *email);
void setPhoneNumber(Hashtable *hashtable, unsigned int key, PhoneNumber phoneNumber);
void setAccountCreation(Hashtable *hashtable, unsigned int key, Date accountCreation);

#endif