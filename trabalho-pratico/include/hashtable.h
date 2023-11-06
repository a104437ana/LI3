#ifndef _HASHTABLE_
#define _HASHTABLE_

#include "utilidade.h"

typedef struct nodoHashtable NodoHashtable;
typedef struct hashtable Hashtable;

unsigned int funcaoHash(char *id);

NodoHashtable *criaNodoHashtable();
Hashtable *criaHashtable(int tamanho);
NodoHashtable **procuraNodo(Hashtable *hashtable, unsigned int chave);
NodoHashtable *procuraHashtable(Hashtable *hashtable, unsigned int chave);
void adicionaHashtable(Hashtable *hashtable, unsigned int chave, void *data);
void removeHashtable(Hashtable *hashtable, unsigned int chave);

//provisorio para testes
int getSize(Hashtable *hashtable);
int getNodos(Hashtable *hashtable);

//gest e sets
void *getData(Hashtable *hashtable, unsigned int chave);
void setData(Hashtable *hashtable, unsigned int chave, void *data);

void printTable(Hashtable *hashtable, void (*printFunction)(void*));

void destroiHashtable(Hashtable *hashtable);

#endif