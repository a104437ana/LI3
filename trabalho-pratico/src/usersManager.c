#include <stdio.h>
#include <stdlib.h>
#include "usersManager.h"

struct usersManager {
    Hashtable *users;
//    OrdList *usersByName;
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
    sortOrdlistHashtable(usersManager->users, sortUserReservationsByDate);
    sortOrdlistHashtable(usersManager->users, sortUserFlightsByDate);
}
//gets

User *getUserCatalog(UsersManager *usersManager, unsigned int key) {
    User *user = (User*) getData(usersManager->users, key);
    return user;
}

int existsUser(UsersManager *usersManager, char *id) {
    int key = hashFunction(id);
    HashtableNode *user = searchHashtable(usersManager->users, key);
    if (user == NULL) return 0;
    return 1;
}

Hashtable *getHashtableUserCatalog(UsersManager *usersManager) {
    return usersManager->users;
}
