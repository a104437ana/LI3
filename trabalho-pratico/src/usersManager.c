#include <stdio.h>
#include <stdlib.h>
#include "usersManager.h"

struct usersManager {
    Hashtable *users;
    OrdList *usersId;
    OrdList *usersByName;
};
//função que cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size) {
    UsersManager *usersManager = malloc(sizeof(UsersManager)); //aloca espaço em memória para a estrutura do catálogo
    usersManager->users = createHashtable(size); //cria uma hastable para os utilizadores
    //usersManager->usersId = createOrdList(size);
    usersManager->usersByName = createOrdList(size); //cria uma lista para os utilizadores
    return usersManager;
}
//função que adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(UsersManager *usersManager, User *user, unsigned int key) {
    addHashtable(usersManager->users, key, user, getUserId(user));
}
//função que adiciona um utilizador à lista de utilizadores ordenada por nome do catálogo de utilizadores
void addUserToCatalogList(UsersManager *usersManager, User *user) {
    addOrdList(usersManager->usersByName, user);
}
/*
void addUserIdToCatalog (UsersManager* usersManager, UserId* userId) {
    addOrdList(usersManager->usersId, userId);
}
*/
//função que compara o nome de dois utilizadores
int compareUsersNames(void *user1, void *user2) {
    char *name1 = getName((User *) user1), *name2 = getName((User *) user2);
    int compare = strcoll(name1, name2); //compara os dois nomes
    if (compare == 0) { //caso sejam iguais compara os seus ids
        char *id1 = getUserId((User *) user1), *id2 = getUserId((User *) user2);
        compare = strcoll(id1, id2);
    }

    return compare;
}
//função que ordena o catálogo de utilizadores
void sortUserCatalog(UsersManager *usersManager) {
    sortOrdlistHashtable(usersManager->users, sortUserList); //ordena a lista de voos e reservas de todos os utilizadores
    OrdList *usersByName = usersManager->usersByName;
    quickSort(usersByName, 0, getOrdListSize(usersByName)-1, compareUsersNames, 0); //ordena os utilizadores por nome na lista de utilizadores
}

//gets
User *getUserCatalog(UsersManager *usersManager, unsigned int key, char *id) {
    User *user = (User*) getData(usersManager->users, key, id);
    return user;
}

//função que verifica se um utilizador já existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id) {
    int key = hashFunction(id);
    HashtableNode *user = searchHashtable(usersManager->users, key, id);
    if (user == NULL) return 0;
    return 1;
}

Hashtable *getHashtableUserCatalog(UsersManager *usersManager) {
    return usersManager->users;
}

OrdList *getUsersByName (UsersManager *usersManager) {
    return usersManager->usersByName;
}

OrdList *getOrdListUser (UsersManager *usersManager) {
    return usersManager->usersId;
}

//função que imprime um utilizador
void printFunctionUser(void *data) {
    char *userId = getUserId((User *) data);
    printf(" %8s, %d)", userId, getOrdListSize(getUserList((User *) data)));
    free(userId);
}
//função que imprime todo o catálogo de utilizadores, para efeitos de teste
void printUsers(UsersManager *usersManager) {
    printTable(usersManager->users, printFunctionUser);
    printHashtableUsage(usersManager->users);
}

//função que liberta o espaço em memória alocado pelo catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager) {
    if (usersManager == NULL) return; //se o catálogo não existir
    destroyHashtable(usersManager->users, destroyUser); //liberta a hashtable de utilizadores
    //destroyOrdList(usersManager->usersId,destroyUserId);
    destroyOnlyOrdList(usersManager->usersByName); //liberta a lista de utilizadores
    free(usersManager);
}

