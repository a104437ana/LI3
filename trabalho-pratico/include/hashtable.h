#ifndef _HASHTABLE_
#define _HASHTABLE_

#include "utility.h"

typedef struct hashtableNode HashtableNode;
typedef struct hashtable Hashtable;

unsigned int hashFunction(char *id);

HashtableNode *createHashtableNode();
Hashtable *createHashtable(int size);
HashtableNode **searchNode(Hashtable *hashtable, unsigned int key);
HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key);
void addHashtable(Hashtable *hashtable, unsigned int key, void *data);
void removeHashtable(Hashtable *hashtable, unsigned int key);

//provisorio para testes
int getSize(Hashtable *hashtable);
int getNodes(Hashtable *hashtable);

//gest e sets
void *getDate(Hashtable *hashtable, unsigned int key);
void setDate(Hashtable *hashtable, unsigned int key, void *data);

void printTable(Hashtable *hashtable, void (*printFunction)(void*));

void destroyHashtable(Hashtable *hashtable);

#endif