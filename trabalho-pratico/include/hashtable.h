#ifndef _HASHTABLE_
#define _HASHTABLE_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

typedef struct hashtable Hashtable;
//funão de hash
unsigned int hashString(void *key);
unsigned int hashInt(void *key);
//cria uma nova hashtable
Hashtable *createHashtable(int size, unsigned int (*hash)(void*), int (*compareKey)(void*,void*), void *(*dupKey)(void*), void (*destroy)(void*));
//devolve número de nodos usados
int getHashtableUsed(Hashtable *hashtable);
//copia hashtable para outra hashtable
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable);
//adiciona um elemnto à hashtbale
Hashtable *addHashtable(Hashtable *hashtable, void *data, void *key);
void removeHashtable(Hashtable *hashtable, unsigned int key);
//verifica se existe um elemnto na hashtable
int existsData(Hashtable *hashtable, void *key);

//gest e sets
//obtem elemnto da hahtable
void *getData(Hashtable *hashtable, void *key);
int getHashtableNodes(Hashtable *hashtable);
//modifica elemento da hashtable
void setData(Hashtable *hashtable, void *data, void *key);
//ordena um parametro de todos os elementos da hashtable
void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable);
////obtem o próximo elemento da hashtable
//void *getNextData(Hashtable *hashtable, unsigned int key, char *id);

//para efeitos de teste
//imprime todos os elemntos da hashtable
void printTable(Hashtable *hashtable, void (*printFunction)(void*));
void printHotelTableReservs(Hashtable *hashtable, void (*printFunction)(void*));
//imprime nível de uso da hashtable
void printHashtableUsage(Hashtable *hashtable);

//liberta espaço em memória da hashtable
void destroyHashtable(Hashtable *hashtable);

void ht_applyToAll(Hashtable *table, void function(void*), void *getFunction(void*));

typedef struct hashtableInt HashtableInt;
HashtableInt *createHashtableInt(int size, void (*destroy)(void*));
int getHashtableIntUsed(HashtableInt *hashtable);
void copyHashtableInt(HashtableInt *hashtable, HashtableInt *newHashtable);
HashtableInt *addHashtableInt(HashtableInt *hashtable, void *data, int key);
int existsDataInt(HashtableInt *hashtable, int key);
void *getDataInt(HashtableInt *hashtable, int key);
int getHashtableNodesInt(HashtableInt *hashtable);
void setDataInt(HashtableInt *hashtable, void *data, int key);
void destroyHashtableInt(HashtableInt *hashtable);

#endif