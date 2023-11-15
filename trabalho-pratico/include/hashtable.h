#ifndef _HASHTABLE_
#define _HASHTABLE_

#include "utility.h"

typedef struct hashtableNode HashtableNode;
typedef struct hashtable Hashtable;
//função simples melhorar função de hash
unsigned int hashFunction(char *id);

HashtableNode *createHashtableNode();
Hashtable *createHashtable(int size);
HashtableNode **searchNode(Hashtable *hashtable, unsigned int key, char *id);
HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key, char *id);
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable);
void addHashtable(Hashtable *hashtable, unsigned int key, void *data, char *id);
void removeHashtable(Hashtable *hashtable, unsigned int key);
int existsData(Hashtable *hashtable, unsigned int key, char *id);

//gest e sets
void *getData(Hashtable *hashtable, unsigned int key, char *id);
void setData(Hashtable *hashtable, unsigned int key, void *data, char *id);
void *getDataIndex(Hashtable *hashtable, unsigned int index);
void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*));

//para testar
void printTable(Hashtable *hashtable, void (*printFunction)(void*));
void printHotelTableReservs(Hashtable *hashtable, void (*printFunction)(void*));
void printHashtableUsage(Hashtable *hashtable);
//falta acabar
void removeNode(HashtableNode *hashtable);
void destroyHashtable(Hashtable *hashtable);

#endif