#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "userId.h"
#include "hashtable.h"
#include "orderedList.h"

typedef struct usersManager UsersManager;

UsersManager *createUsersCatalog(int size);
void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key);
void addUserIdToCatalog (UsersManager* usersManager, UserId* userId);
void addUserToCatalogList(UsersManager *usersManager, User *user);
void sortUserCatalog(UsersManager *usersManager);
//gets
User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id);
Hashtable *getHashtableUserCatalog(UsersManager *usersManager);
OrdList *getOrdListUser (UsersManager *usersManager);
OrdList *getUsersByName (UsersManager *usersManager);
int existsUser(UsersManager *usersManager, char *id);

void printUsers(UsersManager *usersManager);

void destroyUsersCatalog(UsersManager *usersManager);

#endif