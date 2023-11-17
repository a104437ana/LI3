#include "userByName.h"

struct userByName {
    char* id_user;
    char* name_user;
};

UserByName *createUserByName (char *id, char *name) {
    UserByName *userByName = malloc(sizeof(UserByName));
    userByName->id_user = strdup(id);
    userByName->name_user = strdup(name);
    return userByName;
}

char* getId_UserByName (UserByName* userByName) {
    return strdup(userByName->id_user);
}

char* getName_UserByName (UserByName* userByName) {
    return strdup(userByName->name_user);
}

void setId_UserByName (UserByName* userByName, char *id) {
    char *old_id = userByName->id_user;
    userByName->id_user = strdup(id);
    free(old_id);
}

void setName_UserByName (UserByName* userByName, char *name) {
    char *old_name = userByName->name_user;
    userByName->name_user = strdup(name);
    free(old_name);
}

void destroyUserByName (void* userByName) {
     if (userByName != NULL) {
        free(((UserByName *) userByName)->name_user);
        free(((UserByName *) userByName)->id_user);
        free(userByName);
     }
}
