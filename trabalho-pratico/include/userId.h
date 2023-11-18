#ifndef _USER_ID_
#define _USER_ID_

#include <stdlib.h>
#include <string.h>

typedef struct userId UserId;
UserId *createUserId (char *id);
char* getId_UserId (UserId* userId);
void setId_UserId (UserId* userId, char *id);
void destroyUserId (void* userId);

#endif