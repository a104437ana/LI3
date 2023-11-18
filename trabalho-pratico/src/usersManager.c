#include <stdio.h>
#include <stdlib.h>
#include "usersManager.h"

struct usersManager {
    Hashtable *users;
    OrdList *usersId;
};

UsersManager *createUsersCatalog(int size) {
    UsersManager *usersManager = malloc(sizeof(UsersManager));
    usersManager->users = createHashtable(size);
    usersManager->usersId = createOrdList(size);
    return usersManager;
}

void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key) {
    addHashtable(usersManager->users, key, user, getUserId(user));
}

void addUserIdToCatalog (UsersManager* usersManager, UserId* userId) {
    addOrdList(usersManager->usersId, userId);
}

void sortUserCatalog(UsersManager *usersManager) {
    sortOrdlistHashtable(usersManager->users, sortUserList);
}
//gets

User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id) {
    User *user = (User*) getData(usersManager->users, key, id);
    return user;
}

int existsUser(UsersManager *usersManager, char *id) {
    int key = hashFunction(id);
    HashtableNode *user = searchHashtable(usersManager->users, key, id);
    if (user == NULL) return 0;
    return 1;
}

Hashtable *getHashtableUserCatalog(UsersManager *usersManager) {
    return usersManager->users;
}

OrdList *getOrdListUser (UsersManager *usersManager) {
    return usersManager->usersId;
}

void printFunctionUser(void *data) {
    char *userId = getUserId((User *) data);
    printf(" %8s, %d)", userId, getOrdListSize(getUserList((User *) data)));
    free(userId);
}

void printUsers(UsersManager *usersManager) {
    printTable(usersManager->users, printFunctionUser);
    printHashtableUsage(usersManager->users);
}

void destroyUsersCatalog(UsersManager *usersManager) {
    if (usersManager == NULL) return;
    destroyHashtable(usersManager->users, destroyUser);
    destroyOrdList(usersManager->usersId,destroyUserId);
    free(usersManager);
}

