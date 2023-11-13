#include <stdio.h>
#include <stdlib.h>
#include "usersManager.h"

struct usersManager {
    Hashtable *users;
};

UsersManager *createUsersCatalog(int size) {
    UsersManager *usersManager = malloc(sizeof(UsersManager));
    usersManager->users = createHashtable(size);
    return usersManager;
}

void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key) {
    addHashtable(usersManager->users, key, user);
}

void sortUserCatalog(UsersManager *usersManager) {
    sortUsersReservsHashtable(usersManager->users);
    sortUsersFlightsHashtable(usersManager->users);
}
//gets

User *getUserCatalog(UsersManager *usersManager, unsigned int key) {
    User *user = (User*) getData(usersManager->users, key);
    return user;
}

Hashtable *getHashtableUserCatalog(UsersManager *usersManager) {
    return usersManager->users;
}
