#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "hashtable.h"
#include "orderedList.h"
#include "results.h"

typedef struct usersManager UsersManager;

//função que cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size);
void createListPassengers (UsersManager* usersCatalog, int size);

//função que adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice, UsersManager *usersCatalog);
//adiciona uma reserva à lista de reservas de um utilizador
void addReservToUser(char *id_user, unsigned long int id_reserv, double totalSpent, UsersManager *usersCatalog);
//adiciona o utilizador à lista de passageiros do voo
void addFlightToUser(char *id_user, unsigned long int id_flight, UsersManager *usersCatalog);

//gets

//função que verifica se um utilizador já existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id);
int getAccountStatusUser(char *id, UsersManager *usersCatalog);
int getSizeUserList(int type, char *id, UsersManager *usersCatalog);
//retorna o id que se encontra numa certa posição da lista de voos e reservas do utilizador
unsigned long int getIdUserList_usersCatalog(int *type, char *id_user, int index, UsersManager *usersCatalog);
//retorna o ano do primeiro utilizador na lista de criação de contas
int getYearFirstResults_usersCatalog(UsersManager *usersCatalog);
//retorna o ano do último utilizador na lista de criação de contas
int getYearLastResults_usersCatalog(UsersManager *usersCatalog);
User *getUserCatalog(UsersManager *usersManager, char *id);

//conta o número de passageiros únicos
int count_unique_passengers (UsersManager* usersCatalog, OrdList* list);

//função que liberta o espaço em memória alocado pelo catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager);

//compara uma data com a criação de conta de um utilizador
int compareDates_user(void *date, void *user, void *usersCatalog);
//compara uma data com a criação de conta de um utilizador, sem considerar o dia
int compareMonths_user(void *date, void *user, void *usersCatalog);
//compara uma data com a criação de conta de um utilizador, só considerando o ano
int compareYears_user(void *date, void *user, void *usersCatalog);

//sort
//função que compara o nome de dois utilizadores
int compareUsersNames(void *user1, void *user2, void *lookup);
void sortUsersByName(UsersManager *usersCatalog);
void radixSortAccountCreation(OrdList *list, void *lookupTable);
void sortUsersByAccountCreation(UsersManager *usersCatalog);
int prefixSearch(void *prefixVoid, void *user, void *lookup);
int prefixSearchBack(void *prefixVoid, void *user, void *lookup);
int sameFirstLetterUser(char *string1, char *string2);
int isPrefixUser(int *firstLetterCheck, char *prefix, int index, UsersManager *usersCatalog);

//queries
//calcula os dados de um utilizador para a query 1
void user_catalog_compute_Q1 (char *id, UsersManager* usersManager, QueryResult* result);
void user_catalog_compute_Q9 (char *prefix, UsersManager* usersManager, QueryResult* result);
//calcula o número de utilizadores que criaram conta numa data
int getNewUsers(int year, int month, int day, UsersManager * users);

#endif