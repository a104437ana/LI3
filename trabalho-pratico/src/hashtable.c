#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

struct nodoHashtable {
    int chave;
    void *data;
    struct nodoHashtable *proximo;
};

struct hashtable {
    int tamanho;
    int nodos;
    NodoHashtable **nodo;
};

//funcao hash simples
unsigned int funcaoHash(char *id) {
    unsigned int hash = 0;
    for (int i=0; id[i]; i++) 
        hash += id[i];

    return hash;
}

NodoHashtable *criaNodoHashtable() {
    NodoHashtable *nodo = malloc(sizeof(NodoHashtable));
    nodo->chave = 0;
    nodo->data = NULL;
    nodo->proximo = NULL;

    return nodo;
}

Hashtable *criaHashtable(int tamanho) {
    Hashtable *novaHashtable = malloc(sizeof(Hashtable));
    novaHashtable->tamanho = tamanho;
    novaHashtable->nodos = 0;
    novaHashtable->nodo = malloc(sizeof(NodoHashtable) * tamanho);
    for (int i=0; i<tamanho; i++)
        novaHashtable->nodo[i] = NULL;

    return novaHashtable;
}

NodoHashtable **procuraNodo(Hashtable *hashtable, unsigned int chave) {
    int indice = chave % hashtable->tamanho;
    NodoHashtable **nodo = &(hashtable->nodo[indice]);
    if (*nodo != NULL) {
        while ((*nodo)->proximo != NULL)
            nodo = &((*nodo)->proximo);
    }

    return nodo;
}

NodoHashtable *procuraHashtable(Hashtable *hashtable, unsigned int chave) {
    return *(procuraNodo(hashtable, chave));
}

void adicionaHashtable(Hashtable *hashtable, unsigned int chave, void *data) {
    int indice = chave % hashtable->tamanho;
    NodoHashtable **nodo = &(hashtable->nodo[indice]);
    nodo = procuraNodo(hashtable, chave);
    if (*nodo != NULL) nodo = &((*nodo)->proximo);
    *nodo = criaNodoHashtable();
    (*nodo)->chave = chave;
    (*nodo)->data = data;
    hashtable->nodos += 1;
}

//fazer remove
void removeHashtable(Hashtable *hashtable, unsigned int chave) {
}

//gets e sets provisorios para teste
int getSize(Hashtable *hashtable) {
    return hashtable->tamanho;
}

int getNodos(Hashtable *hashtable) {
    return hashtable->nodos;
}

//gets
void *getData(Hashtable *hashtable, unsigned int chave) {
    NodoHashtable *nodo = procuraHashtable(hashtable, chave);

    return nodo->data;
}

void setData(Hashtable *hashtable, unsigned int chave, void *data) {
    NodoHashtable *nodo = procuraHashtable(hashtable, chave);
    void *dataAntiga = nodo->data;
    nodo->data = data;
    free(dataAntiga);
}

void printTable(Hashtable *hashtable, void (*printFunction)(void*)) {
    NodoHashtable *nodo;
    int tamanho = hashtable->tamanho;
    for (int i=0; i<tamanho; i++) {
        nodo = hashtable->nodo[i];
        printf("%2d", i);
        if (nodo == NULL) printf(" ->    0");
        while (nodo != NULL) {
            printf(" -> %4d", nodo->chave);
            (*printFunction)(nodo->data);
            nodo = nodo->proximo;
        }
        printf(" -> X\n");
    }
}

void destroiHashtable(Hashtable *hashtable) {
}
