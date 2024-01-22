#include <stdio.h>
#include <stdlib.h>
#include "usersManager.h"

struct usersManager {
    Hashtable *users;
    OrdList *usersByName;
    OrdList *usersByAccountCreation;
    bool* passengers_list;
    int size;
};
//função que cria um novo catálogo de utilizadores
UsersManager *createUsersCatalog(int size) {
    UsersManager *usersManager = malloc(sizeof(UsersManager)); //aloca espaço em memória para a estrutura do catálogo
    usersManager->users = createHashtable(size, hashString, strcmpVoid, strdupVoid, destroyUser); //cria uma hastable para os utilizadores
    usersManager->usersByName = createOrdList(); //cria uma lista para os utilizadores
    usersManager->usersByAccountCreation = createOrdList();
    return usersManager;
}

/*
void allZerosListPassengers (UsersManager* usersCatalog) {
    int size = usersCatalog->size;
    for (int i = 0; i < size; i++) {
        usersCatalog->passengers_list[i] = 0;
    }
}*/

void count_passenger (UsersManager* usersCatalog, char* id_user) {
    User* user =  getData(usersCatalog->users, id_user);
    int indice = getIndice(user);
    usersCatalog->passengers_list[indice] = 1;
}

int count_unique_passengers (UsersManager* usersCatalog, OrdList* list) {
    int size_list = getOrdListSize(list);
    char* id;
    for (int i = 0; i < size_list; i++) {
        id = getDataOrdList(list,i);
        count_passenger(usersCatalog,id);
    }

    int size = usersCatalog->size;
    int unique_passengers = 0;
    for (int i = 0; i < size; i++) {
        if (usersCatalog->passengers_list[i] != 0) {
            unique_passengers++;
            usersCatalog->passengers_list[i] = 0;
        }
    }
    return unique_passengers;
}

void createListPassengers (UsersManager* usersCatalog, int size) {
    usersCatalog->passengers_list = malloc(sizeof(bool)*size);
    usersCatalog->size = size;
    memset(usersCatalog->passengers_list, 0, size * sizeof(bool));
}

//função que adiciona um utilizador ao catálogo de utilizadores
void addUserToCatalog(char *id, char *name, int gender, char *country, char *passport, char *birth, char *accountCreation, int accountStatus, int indice, UsersManager *usersCatalog) {
    User *user = createUser(id, name, gender, country, passport, birth, accountCreation, accountStatus, indice);
    usersCatalog->users = addHashtable(usersCatalog->users, user, id);
    if (accountStatus){
        addOrdList(usersCatalog->usersByName, user);
    }
    addOrdList(usersCatalog->usersByAccountCreation, user);
}
//adiciona uma reserva à lista de reservas de um utilizador
void addReservToUser(char *id_user, int id_reserv, double totalSpent, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id_user);
    addToUserList(user, id_reserv, 'R', totalSpent);
}
//adiciona o utilizador à lista de passageiros do voo
void addFlightToUser(char *id_user, int id_flight, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id_user);
    addToUserList(user, id_flight, 'F', 0);
}

//função que ordena o catálogo de utilizadores
void sortUsersByName(UsersManager *usersCatalog) {
    OrdList *usersByName = usersCatalog->usersByName;
    heapsort(usersByName, compareUsersNames, NULL, 0);
//    quickSort(usersByName, 0, getOrdListSize(usersByName)-1, compareUsersNames, NULL, 0); //ordena os utilizadores por nome na lista de utilizadores
}

void radixSortAccountCreation(OrdList *list, void *lookupTable) {
    radixSort(list, getAccountCreationDay, lookupTable, 31, 0);
    radixSort(list, getAccountCreationMonth, lookupTable, 12, 0);
    radixSort(list, getAccountCreationYear, lookupTable, N_YEARS, BEGIN_YEAR);
}

void sortUsersByAccountCreation(UsersManager *usersCatalog) {
    OrdList * list = usersCatalog->usersByAccountCreation;
    if(!isOrdered(list)) {
        radixSortAccountCreation(list, NULL); //ordena as reservas por data
        setOrdListOrd(list, 1);
    }
}


//função que compara o nome de dois utilizadores
int compareUsersNames(void *user1, void *user2, void *lookup) {
    return compareUsersNames_user((User *) user1, (User *) user2);
}

//função que verifica se um utilizador já existe no catálogo de utilizadores
int existsUser(UsersManager *usersManager, char *id) {
    return existsData(usersManager->users, id);
}

OrdList *getUsersByAccountCreation (UsersManager *usersManager) {
    return usersManager->usersByAccountCreation;
}
int getCreationDayUser(char *id, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id);
    return getAccountCreationDay(user, NULL);
}
int getCreationMonthUser(char *id, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id);
    return getAccountCreationMonth(user, NULL);
}
int getCreationYearUser(char *id, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id);
    return getAccountCreationYear(user, NULL);
}

int getYearFirstResults_usersCatalog(UsersManager *usersCatalog) {
    User *user = getDataOrdList(usersCatalog->usersByAccountCreation, 0);
    return getAccountCreationYear(user, NULL);
}

int getYearLastResults_usersCatalog(UsersManager *usersCatalog) {
    OrdList *list = usersCatalog->usersByAccountCreation;
    User *user = getDataOrdList(list, getOrdListSize(list)-1);
    return getAccountCreationYear(user, NULL);
}

/*
OrdList *getOrdListUser (UsersManager *usersManager) {
    return usersManager->usersId;
}
*/

//função que liberta o espaço em memória alocado pelo catálogo de utilizadores
void destroyUsersCatalog(UsersManager *usersManager) {
    if (usersManager == NULL) return; //se o catálogo não existir
    destroyHashtable(usersManager->users); //liberta a hashtable de utilizadores
    //destroyOrdList(usersManager->usersId,destroyUserId);
    destroyOnlyOrdList(usersManager->usersByName); //liberta a lista de utilizadores
    destroyOnlyOrdList(usersManager->usersByAccountCreation);
    free(usersManager->passengers_list);
    free(usersManager);
}

char *sameLenPrefix(char *prefix, char *name) {
  unsigned char *up = (unsigned char *) prefix, *un = (unsigned char *) name;
  int i = 0, j = 0, p = 0, n = 0, e = 0;
  while (up[i] != '\0' && un[j] != '\0') {
    if (up[i] == un[j]) e++;
    if (up[i] > 128) {p++; i+=2;}
    else if (up[i] != '\0') i++;
    if (un[j] > 128) {n++; j+=2;}
    else if (un[j] != '\0') j++;
  }

  char *namePrefix;
  if (i == e + 1) return NULL;
  else if (i < j) {
    if (n > p) {i += n;}
    namePrefix = malloc(sizeof(char) * (i + 1));
    //namePrefix = 
    strncpy(namePrefix, name, i);
    namePrefix[i] = '\0';
  }
  else {
    int len;
    if (n > p) len = i + (n - p);
    else len = i;
    namePrefix = malloc(sizeof(char) * (len + 1));
    //namePrefix = 
    strncpy(namePrefix, name, len);
    namePrefix[len] = '\0';
  }

  return namePrefix;
}
int prefixSearch(void *prefixVoid, void *user, void *lookup) {
  int compare;
  char *prefix = (char *) prefixVoid;
  char *name = getName((User *) user); //nome do utilizador
  char *namePrefix = sameLenPrefix(prefix, name);
  if (namePrefix == NULL){
    free(namePrefix); free(name);
    return 0;
  }
  compare = strcoll(prefix, namePrefix); //compara os dois prefixos
  free(namePrefix); //liberta o prefixo do utilizador
  free(name);
  return compare;
}
int prefixSearchBack(void *prefixVoid, void *user, void *lookup) {
  int compare;
  char *prefix = (char *) prefixVoid;
  char *name = getName((User *) user); //nome do utilizador
  compare = strcmp(prefix, name); //compara os dois prefixos
  free(name);
  return compare;
}

int searchPrefix(char *prefix, UsersManager *usersCatalog) {
    return searchDataOrdList(usersCatalog->usersByName, prefix, prefixSearch, usersCatalog->users, 0, prefixSearchBack);
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
    char *id = getDataOrdList(usersCatalog->usersByName, index);
    User *user = getData(usersCatalog->users, id);
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
    User* user = getData(usersManager->users,id);
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
    User *user = (User*) getData(usersManager->users, id);
    return user;
}

int getAccountStatusUser(char *id, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id);
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
    User *user = getData(usersCatalog->users, id);
    int res = 0;
    if (type == 0)
        res = getUListSize(user);
    else if(type == 1)
        res = getNumberFlights(user);
    else if (type == 2)
        res = getNumberReservations(user);
    return res;
}
int getIdUserList(int *type, char *id_user, int index, UsersManager *usersCatalog) {
    User *user = getData(usersCatalog->users, id_user);
    return getUListId(type, user, index);
}

int getUsersByNameSize(UsersManager *usersCatalog) {
    return getOrdListSize(usersCatalog->usersByName);
}
char *getIdUsersByName(int index, UsersManager *usersCatalog) {
    char *id = getDataOrdList(usersCatalog->usersByName, index);
    return strdup(id);
}
char *getNameUsersByName(int index, UsersManager *usersCatalog) {
    char *id = getDataOrdList(usersCatalog->usersByName, index);
    User *user = getData(usersCatalog->users, id);
    char *name = getName(user);
    return name;
}

int compareDates_user(void *date, void *user, void *usersCatalog) {
    Date * d = (Date *) date;
    Date * userDate = getAccountCreation((User *) user);
    int res = compareDates(d,userDate)*(-1);
    destroyDate(userDate);
    return res;
}
void getIdNameUsersByName(int index, char **id, char **name, UsersManager *usersCatalog) {
    User *user = getDataOrdList(usersCatalog->usersByName, index);
    *id = getUserId(user);
    *name = getName(user);
}
/*
int getNewUsers(int year, int month, int day, UsersManager * users){
    int i; int res = 0; char * id;
    int size = getOrdListSize(users->usersByAccountCreation);
    OrdList * list = users->usersByAccountCreation;
    Date * accCre;
    if (day!=-1){
        for (i=0; i<size; i++){
            id = strdup(getDataOrdList(list, i));
            User* user = getData(getHashtableUserCatalog(users),id);
            accCre = getAccountCreation(user);
            if (getYear(accCre)==year){
                if (getMonth(accCre)==month){
                    if (getDay(accCre)==day) res++;
                    else if (getDay(accCre)>day) break;
                }
                else if (getMonth(accCre)>month) break;
            }
            else if (getYear(accCre)>year) break;
        }
    }
    else if (month!=-1){
        for (i=0; i<size; i++){
            id = strdup(getDataOrdList(list, i));
            User* user = getData(getHashtableUserCatalog(users),id);
            accCre = getAccountCreation(user);
            if (getYear(accCre)==year){
                if (getMonth(accCre)==month) res++;
                else if (getMonth(accCre)>month) break;
            }
            else if (getYear(accCre)>year) break;
        }
    }
    else{
        for (i=0; i<size; i++){
            id = strdup(getDataOrdList(list, i));
            User* user = getData(getHashtableUserCatalog(users),id);
            accCre = getAccountCreation(user);
            if (getYear(accCre)==year) res++;
            else if (getYear(accCre)>year) break;
        }
    }
    free(id); destroyDate(accCre);
    return res;
}
*/
int compareMonths_user(void *date, void *user, void *usersCatalog) {
    Date * d = (Date *) date;
    Date * userDate = getAccountCreation((User *) user);
    int month1 = getMonth(d), year1 = getYear(d);
    int month2 = getMonth(userDate), year2 = getYear(userDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    else if (month1 > month2) res = 1;
    else if (month2 > month1) res = -1;
    destroyDate(userDate);
    return res;
}

int compareYears_user(void *date, void *user, void *usersCatalog) {
    Date * d = (Date *) date;
    Date * userDate = getAccountCreation((User *) user);
    int year1 = getYear(d);
    int year2 = getYear(userDate);
    int res = 0;
    if (year1 > year2) res = 1;
    else if (year2 > year1) res = -1;
    destroyDate(userDate);
    return res;
}

int getNewUsers(int year, int month, int day, UsersManager * users){
    int res = 0;
    Date * date = malloc(sizeof(Date));
    date->year = year;
    date->month = month;
    date->day = day;
    OrdList * list = users->usersByAccountCreation;
    if (day!=-1){
        int i = searchDataOrdList(list, date, compareDates_user, users, 0, compareDates_user);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            User * user;
            while (i < size && !exit) {
                user = getDataOrdList(list, i);
                if (compareDates_user(date, user, users) != 0) exit = 1;
                else {
                    i++;
                    res++;
                }
            }
        }
    }
    if (month!=-1){
        int i = searchDataOrdList(list, date, compareMonths_user, users, 0, compareMonths_user);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            User * user;
            while (i < size && !exit) {
                user = getDataOrdList(list, i);
                if (compareMonths_user(date, user, users) != 0) exit = 1;
                else {
                    i++;
                    res++;
                }
            }
        }
    }
    else if (year!=-1){
        int i = searchDataOrdList(list, date, compareYears_user, users, 0, compareYears_user);
        if (i>=0){
            int size = getOrdListSize(list);
            int exit = 0;
            User * user;
            while (i < size && !exit) {
                user = getDataOrdList(list, i);
                if (compareYears_user(date, user, users) != 0) exit = 1;
                else {
                    i++;
                    res++;
                }
            }
        }
    }
    destroyDate(date);
    return res;
}