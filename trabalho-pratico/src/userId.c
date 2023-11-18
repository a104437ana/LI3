#include "userId.h"

struct userId {
    char* id;
};

UserId *createUserId (char *id) {
    UserId *userId = malloc(sizeof(UserId));
    userId->id = strdup(id);
    return userId;
}

char* getId_UserId (UserId* userId) {
    return userId->id;
}

void setId_UserId (UserId* userId, char *id) {
    char *old_id = userId->id;
    userId->id = id;
    free(old_id);
}

void destroyUserId (void* userId) {
     if (userId != NULL) {
        free(((UserId *) userId)->id);
        free(userId);
     }
}
