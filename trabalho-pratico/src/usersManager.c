#include <stdio.h>
#include <stdlib.h>
#include "usersManager.h"

struct usersManager {
    Hashtable *users;
    OrdList *usersByName;
};
//função que cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size) {
    UsersManager *usersManager = malloc(sizeof(UsersManager)); //aloca espaço em memória para a estrutura do catálogo
    usersManager->users = createHashtable(size); //cria uma hastable para os utilizadores
    usersManager->usersByName = createOrdList(); //cria uma lista para os utilizadores
    return usersManager;
}
//função que adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, UsersManager *usersCatalog) {
    int key = hashFunction(id);
    User *user = createUser(id, name, gender, country, passport, birth, accountCreation, accountStatus);
    usersCatalog->users = addHashtable(usersCatalog->users, key, user, id);
    if (accountStatus)
        addOrdList(usersCatalog->usersByName, user);
}
//função que adiciona um utilizador à lista de utilizadores ordenada por nome do catálogo de utilizadores
void addUserToCatalogList(UsersManager *usersManager, User *user) {
    addOrdList(usersManager->usersByName, user);
}
//adiciona uma reserva à lista de reservas de um utilizador
void addReservToUser(char *id_user, char *id_reserv, double totalSpent, UsersManager *usersCatalog) {
    int key = hashFunction(id_user);
    User *user = getData(usersCatalog->users, key, id_user);
    addToUserList(user, id_reserv, 'R', totalSpent);
}
//adiciona o utilizador à lista de passageiros do voo
void addFlightToUser(char *id_user, char *id_flight, UsersManager *usersCatalog) {
    int key = hashFunction(id_user);
    User *user = getData(usersCatalog->users, key, id_user);
    addToUserList(user, id_flight, 'F', 0);
}

//função que ordena o catálogo de utilizadores
void sortUsersByName(UsersManager *usersCatalog) {
    OrdList *usersByName = usersCatalog->usersByName;
    quickSort(usersByName, 0, getOrdListSize(usersByName)-1, compareUsersNames, 0); //ordena os utilizadores por nome na lista de utilizadores
}

//função que compara o nome de dois utilizadores
int compareUsersNames(void *user1, void *user2) {
    char *name1 = getName((User *) user1);
    char *name2 = getName((User *) user2);
    int compare = strcoll(name1, name2); //compara os dois nomes
    if (compare == 0) { //caso sejam iguais compara os seus ids
        char *id1 = getUserId((User *) user1), *id2 = getUserId((User *) user2);
        compare = strcoll(id1, id2);
        free(id1);
        free(id2);
    }
    free(name1);
    free(name2);
    return compare;
}

//função que verifica se um utilizador já existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id) {
    int key = hashFunction(id);
    HashtableNode *user = searchHashtable(usersManager->users, key, id);
    if (user == NULL) return 0;
    return 1;
}

//função que liberta o espaço em memória alocado pelo catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager) {
    if (usersManager == NULL) return; //se o catálogo não existir
    destroyHashtable(usersManager->users, destroyUser); //liberta a hashtable de utilizadores
    //destroyOrdList(usersManager->usersId,destroyUserId);
    destroyOnlyOrdList(usersManager->usersByName); //liberta a lista de utilizadores
    free(usersManager);
}

int searchPrefix(char *prefix, int (*compareFunction)(void*,void*,void*), int (*compareFunctiobBack)(void*,void*,void*), UsersManager *usersCatalog) {
    return searchDataOrdList(usersCatalog->usersByName, prefix, compareFunction, NULL, 0, compareFunctiobBack);
}
int sameFirstLetterUser(char *string1, char *string2) {
  int compare = 1;
  char c1 = string1[0], c2 = string2[0];
  if (c1 == c2) compare = 0;
  else if (c1 == 'A' || c1 == 'E' || c1 == 'I' || c1 == 'O' || c1 == 'U' ||
           c2 == 'A' || c2 == 'E' || c2 == 'I' || c2 == 'O' || c2 == 'U') compare = 0;
  return compare;
}
int isPrefixUser(int *firstLetterCheck, char *prefix, int index, UsersManager *usersCatalog) {
    User *user = getDataOrdList(usersCatalog->usersByName, index);
    char *name = getName(user);
    int nameSize = strlen(name);
    int prefixSize = strlen(prefix);
    char *namePrefix = malloc(sizeof(char) * (prefixSize + 1));
    if (nameSize >= prefixSize) {
        namePrefix = strncpy(namePrefix, name, prefixSize); //prefixo do utilizador com o mesmo tamanho do prefixo a comparar
        namePrefix[prefixSize] = '\0';
    }
    else
        namePrefix = strdup(name);
    int compare = strcoll(prefix, namePrefix); //compara os dois prefixos
    *firstLetterCheck = sameFirstLetterUser(prefix, name);
    free(namePrefix); //liberta o prefixo do utilizador
    free(name);
    return compare;
}

//queries
void user_catalog_compute_Q1 (char *id, UsersManager* usersManager, QueryResult* result) {
    User* user = getData(usersManager->users,hashFunction(id),id);
    if (user == NULL) {
        return;
    }
    else {
        bool account_status_active = getUserAccountStatus(user);
        if (account_status_active == true) {

            setNumberResults(result,1);
            setNumberFieldsQ(result, 0, 8);
            char* name = getName(user); char * field0 = strdup("name");
            Gender gender = getGender(user); char * sex; if (gender==MALE) sex = strdup("M"); else sex = strdup("F"); char * field1 = strdup("sex");
            int age = getAge(user);
            char * ageS = malloc(sizeof(char)*4);
            sprintf(ageS, "%d", age); char * field2 = strdup("age");
            char* country_code = getCountry(user); char * field3 = strdup("country_code");
            char* passport = getPassport(user); char * field4 = strdup("passport");
            int number_of_flights = getNumberFlights(user);
            char * nFlights = malloc(sizeof(char)*4);
            sprintf(nFlights, "%d", number_of_flights); char * field5 = strdup("number_of_flights");
            int number_of_reservations = getNumberReservations(user);
            char * nReserv = malloc(sizeof(char)*4);
            sprintf(nReserv, "%d", number_of_reservations); char * field6 = strdup("number_of_reservations");
            double total_spent = getTotalSpent(user);
            char * totalS = malloc(sizeof(char)*10);
            sprintf(totalS, "%.3f", total_spent); char * field7 = strdup("total_spent");

            setFieldQ(result, 0, 0, field0, name);
            setFieldQ(result, 0, 1, field1, sex); 
            setFieldQ(result, 0, 2, field2, ageS); 
            setFieldQ(result, 0, 3, field3, country_code);
            setFieldQ(result, 0, 4, field4, passport); 
            setFieldQ(result, 0, 5, field5, nFlights); 
            setFieldQ(result, 0, 6, field6, nReserv); 
            setFieldQ(result, 0, 7, field7, totalS); 
        
            free(name); free(sex); free(country_code); free(passport); free(ageS); free(nFlights); free(nReserv); free(totalS);
            free(field0); free(field1); free(field2); free(field3); free(field4); free(field5); free(field6); free(field7);
        }
        else return;
    }
}

//gets
User *getUserCatalog(UsersManager *usersManager, char *id) {
    int key = hashFunction(id);
    User *user = (User*) getData(usersManager->users, key, id);
    return user;
}

int getAccountStatusUser(char *id, UsersManager *usersCatalog) {
    int key = hashFunction(id);
    User *user = getData(usersCatalog->users, key, id);
    if (user == NULL) return -1;
    return getUserAccountStatus(user);
}

Hashtable *getHashtableUserCatalog(UsersManager *usersManager) {
    return usersManager->users;
}

OrdList *getUsersByName (UsersManager *usersManager) {
    return usersManager->usersByName;
}

int getSizeUserList(int type, char *id, UsersManager *usersCatalog) {
    int key = hashFunction(id);
    User *user = getData(usersCatalog->users, key, id);
    int res = 0;
    if (type == 0)
        res = getUListSize(user);
    else if(type == 1)
        res = getNumberFlights(user);
    else if (type == 2)
        res = getNumberReservations(user);
    return res;
}
char *getIdUserList(int *type, char *id_user, int index, UsersManager *usersCatalog) {
    int key = hashFunction(id_user);
    User *user = getData(usersCatalog->users, key, id_user);
    return getUListId(type, user, index);
}

int getUsersByNameSize(UsersManager *usersCatalog) {
    return getOrdListSize(usersCatalog->usersByName);
}
char *getIdUsersByName(int index, UsersManager *usersCatalog) {
    User *user = getDataOrdList(usersCatalog->usersByName, index);
    return getUserId(user);
}
char *getNameUsersByName(int index, UsersManager *usersCatalog) {
    User *user = getDataOrdList(usersCatalog->usersByName, index);
    return getName(user);
}
