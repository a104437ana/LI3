#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "hashtable.h"
#include "orderedList.h"
#include "results.h"

typedef struct usersManager UsersManager;
//cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size);
//adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, UsersManager *usersCatalog);
//adiciona um utilizador à lista de utilizadores ordenada por nome do catálogo de utilizadores
void addUserToCatalogList(UsersManager *usersManager, User *user);

//gets
User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id);
Hashtable *getHashtableUserCatalog(UsersManager *usersManager);
//OrdList *getOrdListUser (UsersManager *usersManager);
OrdList *getUsersByName (UsersManager *usersManager);

//verifica se sum utilizador existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id);

//imprime todo o ctálogo de utilizadores, para efeitos de teste
void printUsers(UsersManager *usersManager);

//liberta espaço em memória do catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager);

void user_catalog_compute_Q1 (char *id, UsersManager* usersManager, Results* results);
#endif