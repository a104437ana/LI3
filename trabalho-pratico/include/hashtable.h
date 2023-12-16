#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

typedef struct hashtableNode HashtableNode;
typedef struct hashtable Hashtable;
//funão de hash
unsigned int hashFunction(char *id);
//cria um nodo da hashtable
HashtableNode *createHashtableNode();
//cria uma nova hashtable
Hashtable *createHashtable(int size);
//procura nodo na hashtable
HashtableNode **searchNode(Hashtable *hashtable, unsigned int key, char *id);
HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key, char *id);
//copia hashtable para outra hashtable
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable);
//adiciona um elemnto à hashtbale
void addHashtable(Hashtable *hashtable, unsigned int key, void *data, char *id);
void removeHashtable(Hashtable *hashtable, unsigned int key);
//verifica se existe um elemnto na hashtable
int existsData(Hashtable *hashtable, unsigned int key, char *id);

//gest e sets
//obtem elemnto da hahtable
void *getData(Hashtable *hashtable, unsigned int key, char *id);
//modifica elemento da hashtable
void setData(Hashtable *hashtable, unsigned int key, void *data, char *id);
//ordena um parametro de todos os elementos da hashtable
void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable);

//para efeitos de teste
//imprime todos os elemntos da hashtable
void printTable(Hashtable *hashtable, void (*printFunction)(void*));
void printHotelTableReservs(Hashtable *hashtable, void (*printFunction)(void*));
//imprime nível de uso da hashtable
void printHashtableUsage(Hashtable *hashtable);

//liberta espaço em memória da hashtable
void destroyHashtable(Hashtable *hashtable, void (*destroyDataFunction)(void*));

#endif