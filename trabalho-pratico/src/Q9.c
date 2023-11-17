#include "Q9.h"

int same_prefix (char* prefix, char* name) { 
    int same_prefix = 0;
    if (strlen(name) >= strlen(prefix)) {
        int i = 0;
        while (prefix[i] != '\0') {
            if (prefix[i] != name[i]) break;
            i++;
        }
        if (prefix[i] == '\0') same_prefix = 1;
    }
    return same_prefix;
}

void swap (UserByName* user1, UserByName* user2) {
    char* name1 = getName_UserByName(user1);
    char* name2 = getName_UserByName(user2);
    char* id1 = getId_UserByName(user1);
    char* id2 = getId_UserByName(user2);
    setName_UserByName(user1,name2);
    setName_UserByName(user2,name1);
    setId_UserByName(user1,id2);
    setId_UserByName(user2,id1);
    free(name1);
    free(name2);
    free(id1);
    free(id2);
}

int bigger_user (UserByName* user1, UserByName* user2) {
    int bigger_user = 2;
    char* name1 = getName_UserByName(user1);
    char* name2 = getName_UserByName(user2);
    int result = strcoll(name1,name2);
    free(name1);
    free(name2);
    if (result == 0) {
        char* id1 = getId_UserByName(user1);
        char* id2 = getId_UserByName(user2);
        result = strcoll(id1,id2);
        free(id1);
        free(id2);
    }
    if (result > 0) bigger_user = 1;
    return bigger_user;
}

void ord_list_by_name (OrdList* list, int begin, int end) {
    if (begin != end) {
        UserByName* pivo = getDataOrdList(list,end);
        int i = begin-1;
        int j = begin;
        while (j < end) {
            UserByName* user_j = getDataOrdList(list,j);
            if (bigger_user(user_j,pivo) == 1) {
                j++;
            }
            else {
                i++;
                UserByName* user_i = getDataOrdList(list,i);
                swap(user_i,user_j);
            }
        }
        if (j == end) {
            i++;
            UserByName* user_i = getDataOrdList(list,i);
            swap(user_i,user_j);
        }
        ord_list_by_name(list,0,i-1);
        ord_list_by_name(list,i+1,end);
    }
}

OrdList* Q9 (char* prefix,UsersManager *usersCatalog) {
    OrdList* name_with_prefix = createOrdList(10000);
    int size = getOrdListSize(usersCatalog->usersByName);
    int i = 0;
    while (i<size) {
        UserByName* userByName = getDataOrdList(usersCatalog->usersByName,i);
        char* name = getName_UserByName(userByName);
        int addToList = same_prefix(prefix,name);
        free(name);
        if (addToList) {
            addOrdList(name_with_prefix,userByName);
        }
        i++;
    }
    ord_list_by_name(name_with_prefix,0,size-1);
    return name_with_prefix;
}