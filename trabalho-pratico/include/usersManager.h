#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "hashtable.h"

typedef struct usersManager UsersManager;

UsersManager *createUsersCatalog(int size);
void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key);
void sortUserCatalog(UsersManager *usersManager);
//gets
User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id);
Hashtable *getHashtableUserCatalog(UsersManager *usersManager);
int existsUser(UsersManager *usersManager, char *id);

void printUsers(UsersManager *usersManager);

void destroyUsersCatalog(UsersManager *usersManager);

#endif