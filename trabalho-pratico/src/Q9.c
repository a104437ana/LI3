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

struct user_id_name {
    char* id_user;
    char* name_user;
};

void swap(OrdList* ordList,int index1,int index2) {
    UserIdName* user1 = malloc(sizeof(UserIdName));
    user1 = getDataOrdList(user_id_name,index1);
    char* id1 = user1->id_user;
    char* name1 = user1->name_user;
    UserIdName* user2 = malloc(sizeof(UserIdName));
    user2 = getDataOrdList(user_id_name,index2);
    char* id2 = user2->id_user;
    char* name2 = user2->name_user;
    setDataOrdList(ordList,index1,user2);
    setDataOrdList(ordList,index2,user1);
}

int bigger_user (UserIdName* user1, UserIdName* user2) {
    int bigger_user = 2;
    int result = strcoll(user1->name_user,user2->name_user);
    if (result == 0) {
        result = strcoll(user1->id,user2->id);
    }
    if (result > 0) bigger_user = 1;
    return bigger_user;
}

void ord_list_by_name (UsersManager* usersCatalog, int begin, int end) {
    if (begin != end) {
        UserIdName* pivo = getDataOrdList(user_id_name,end);
        int i = begin-1;
        int j = begin;
        while (j < end) {
            UserIdName* user1 = getDataOrdList(user_id_name,j);
            if (bigger_user(user1,pivo) == 1) {
                j++;
            }
            else {
                i++;
                swap(user_id_name,j,i);
            }
        }
        if (j == end) {
            i++;
            swap(user_id_name,j,i);
        }
        ord_list_by_name(ordList,0,i-1);
        ord_list_by_name(ordList,i+1,end);
    }
}

void Q9 (char* prefix,OrdList* user_id_name) {
    OrdList* name_with_prefix = createOrdList(10000);
    int size = getOrdListSize(user_id_name);
    int i = 0;
    while (i<size) {
        UserIdName* user = getDataOrdList(user_id_name,i);
        int addToList = same_prefix(prefix,user->name);
        if (addToList) {
            addOrdList(name_with_prefix,user);
        }
        i++;
    }
    ord_list_by_name(name_with_prefix,0,size-1);
}