#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "userId.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct usersManager UsersManager;
//cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size);
//adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key);
void addUserIdToCatalog (UsersManager* usersManager, UserId* userId);
//adiciona um utilizador à lista de utilizadores ordenada por nome do catálogo de utilizadores
void addUserToCatalogList(UsersManager *usersManager, User *user);
//ordena o catálogo de utilizadores
void sortUserCatalog(UsersManager *usersManager);

//gets
User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id);
Hashtable *getHashtableUserCatalog(UsersManager *usersManager);
OrdList *getOrdListUser (UsersManager *usersManager);
OrdList *getUsersByName (UsersManager *usersManager);

//verifica se sum utilizador existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id);

//imprime todo o ctálogo de utilizadores, para efeitos de teste
void printUsers(UsersManager *usersManager);

//liberta espaço em memória do catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager);

#endif