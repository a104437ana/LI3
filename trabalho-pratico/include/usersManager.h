#ifndef _USERS_MANAGER_
#define _USERS_MANAGER_

#include "user.h"
#include "hashtable.h"

typedef struct usersManager UsersManager;

UsersManager *createUsersCatalog(int size);
void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key);
//gets
User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id);
Hashtable *getHashtableUserCatalog(UsersManager *usersManager);
int existsUser(UsersManager *usersManager, char *id);

void printUsers(UsersManager *usersManager);

#endif