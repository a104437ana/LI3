#ifndef _HASHTABLE_
#define _HASHTABLE_

typedef struct hashtable Hashtable;
typedef struct hashtableInt HashtableInt;
//funão de hash
unsigned long int hashString(void *key);
unsigned long int hashInt(void *key);
//cria uma nova hashtable
Hashtable *createHashtable(int size, unsigned long int (*hash)(void*), int (*compareKey)(void*,void*), void *(*dupKey)(void*), void (*destroy)(void*));
HashtableInt *createHashtableInt(int size, void (*destroy)(void*));
//copia hashtable para outra hashtable
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable);
void copyHashtableInt(HashtableInt *hashtable, HashtableInt *newHashtable);
//adiciona um elemnto à hashtbale
Hashtable *addHashtable(Hashtable *hashtable, void *data, void *key);
HashtableInt *addHashtableInt(HashtableInt *hashtable, void *data, unsigned long int key);
//verifica se existe um elemnto na hashtable
int existsData(Hashtable *hashtable, void *key);
int existsDataInt(HashtableInt *hashtable, unsigned long int key);

//gest e sets
//devolve número de nodos usados
int getHashtableUsed(Hashtable *hashtable);
int getHashtableIntUsed(HashtableInt *hashtable);
//obtem elemnto da hahtable
void *getData(Hashtable *hashtable, void *key);
void *getDataInt(HashtableInt *hashtable, unsigned long int key);
//modifica elemento da hashtable
void setData(Hashtable *hashtable, void *data, void *key);
void setDataInt(HashtableInt *hashtable, void *data, unsigned long int key);
//ordena um parametro de todos os elementos da hashtable
void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable);

//liberta espaço em memória da hashtable
void destroyHashtable(Hashtable *hashtable);
void destroyHashtableInt(HashtableInt *hashtable);

#endif