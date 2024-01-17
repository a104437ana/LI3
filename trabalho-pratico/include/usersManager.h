#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "hashtable.h"
#include "orderedList.h"
#include "results.h"

/*
typedef enum {
    Id,
    Name,
    Gender,
    Country,
    Passport,
    Birth,
    AccountCreation,
    AccountStatus,
    TotalSpent,
    NumberFlights,
    NumberReservations
} UserField;
*/
typedef struct usersManager UsersManager;
//cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size);
void allZerosListPassengers (UsersManager* usersCatalog);
void count_passenger (UsersManager* usersCatalog, char* id_user);
int count_unique_passengers (UsersManager* usersCatalog,OrdList* list);
void createListPassengers (UsersManager* usersCatalog, int size);
void createListPassengers (UsersManager* usersCatalog, int size);
//adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice, UsersManager *usersCatalog);
//adiciona uma reserva à lista de reservas de um utilizador
void addReservToUser(char *id_user, int *id_reserv, double totalSpent, UsersManager *usersCatalog);
//adiciona o utilizador à lista de passageiros do voo
void addFlightToUser(char *id_user, int *id_flight, UsersManager *usersCatalog);
//função que ordena o catálogo de utilizadores
void sortUsersByName(UsersManager *usersCatalog);
void sortUsersByAccountCreation(UsersManager *usersCatalog);
//compara o nome de dois utilizadores
int compareUsersNames(void *id1, void *id2, void *lookup);

//verifica se um utilizador existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id);

int getAccountStatusUser(char *id, UsersManager *usersCatalog);

//imprime todo o ctálogo de utilizadores, para efeitos de teste
void printUsers(UsersManager *usersManager);

//liberta espaço em memória do catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager);

void user_catalog_compute_Q1 (char *id, UsersManager* usersManager,QueryResult* result);
int getNewUsers(int year, int month, int day, UsersManager * users);

//gets
User *getUserCatalog(UsersManager *usersManager, char *id);
Hashtable *getHashtableUserCatalog(UsersManager *usersManager);
int getNumberFlightsUser(char *id, UsersManager *usersCatalog);
int getNumberReservationsUser(char *id, UsersManager *usersCatalog);
OrdList *getUsersByName (UsersManager *usersManager);
OrdList *getUsersByAccountCreation (UsersManager *usersManager);
int getCreationDayUser(char *id, UsersManager *usersCatalog);
int getCreationMonthUser(char *id, UsersManager *usersCatalog);
int getCreationYearUser(char *id, UsersManager *usersCatalog);
int getYearFirstResults_usersCatalog(UsersManager *usersCatalog);
int getYearLastResults_usersCatalog(UsersManager *usersCatalog);
int compareDates_user(void *date, void *id, void *usersCatalog);
int compareMonths_user(void *date, void *id, void *usersCatalog);
int compareYears_user(void *date, void *id, void *usersCatalog);
int getSizeUserList(int type, char *id, UsersManager *usersCatalog);
int *getIdUserList(int *type, char* id_user, int index, UsersManager *usersCatalog);
int getUsersByNameSize(UsersManager *usersCatalog);
int searchPrefix(char *prefix, UsersManager *usersCatalog);
int isPrefixUser(int *firstLetterCheck, char *prefix, int index, UsersManager *usersCatalog);
char *getIdUsersByName(int index, UsersManager *usersCatalog);
char *getNameUsersByName(int index, UsersManager *usersCatalog);
void getIdNameUsersByName(int index, char **id, char **name, UsersManager *usersCatalog);

#endif