#ifndef _USER_BY_NAME_
#define _USER_BY_NAME_

#include <stdlib.h>
#include <string.h>

typedef struct userByName UserByName;
UserByName *createUserByName (char *id, char *name);
char* getId_UserByName (UserByName* userByName);
char* getName_UserByName (UserByName* userByName);
void setId_UserByName (UserByName* userByName, char *id);
void setName_UserByName (UserByName* userByName, char *name);
void destroyUserByName (void* userByName);

#endif