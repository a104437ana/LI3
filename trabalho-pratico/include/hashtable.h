#ifndef _HASHTABLE_
#define _HASHTABLE_

#include "utility.h"

typedef struct hashtableNode HashtableNode;
typedef struct hashtable Hashtable;
//função simples melhorar função de hash
unsigned int hashFunction(char *id);

HashtableNode *createHashtableNode();
Hashtable *createHashtable(int size);
HashtableNode **searchNode(Hashtable *hashtable, unsigned int key);
HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key);
void addHashtable(Hashtable *hashtable, unsigned int key, void *data);
void removeHashtable(Hashtable *hashtable, unsigned int key);

//gest e sets
void *getData(Hashtable *hashtable, unsigned int key);
void setData(Hashtable *hashtable, unsigned int key, void *data);
void *getDataIndex(Hashtable *hashtable, unsigned int index);

void sortHotelsReservsHashtable(Hashtable *hashtable);

//para testar
void printTable(Hashtable *hashtable, void (*printFunction)(void*));
void printHotelTableReservs(Hashtable *hashtable, void (*printFunction)(void*));
//falta acabar
void destroyHashtable(Hashtable *hashtable);

#endif