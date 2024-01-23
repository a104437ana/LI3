#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

//normal
//123.53 seg 4910.48 MB

//id -> 33
//128.75 seg 4915.70 MB

//33 -> id
//124.74 seg 4910.30 MB

//normal strlen size
//122.66 seg 4902.19 MB
//123.07 seg 4902.36 MB
//122.31 seg 4910.18 MB

//normal strlen size strcoll
//125.34 seg 4902.38 MB
//125.14 seg 4902.54 MB

//normal strlen size, guardar funções, void *key
//121.13 seg 4902.83 MB
struct hashtableNode {
    void *key; //chave usada para hash
    void *data; //data guardada
    struct hashtableNode *next; //próximo nodo para gerir colisões
};

struct hashtable {
    int size; //tamanho
    int nodes; //numero de nodos
    struct hashtableNode **node; //lista dos primeiros nodos
    unsigned long int (*hash)(void*);
    int (*compareKey)(void*,void*);
    void *(*dupKey)(void*);
    void (*destroy)(void*);
};

//funcões de hash
unsigned long int hashString(void *key) {
    unsigned char *id = (unsigned char *) key, c;
    if (id == NULL) return 0;
    unsigned long int hash = 5381;
    while ((c = *id++)) //para cada caracter
        hash = ((hash << 5) + hash) + c; // hash[i] = (hash[i] * 33) + id[i]

    return hash;
}
unsigned long int hashInt(void *key) {
    return *((unsigned int *) key); //retorna o valor guardado no apontador
}

//função que cria uma nova hashtable dado um tamanho, uma função de hash, uma função de comparação, uma função de copia da key e uma função para libertar memória da data
Hashtable *createHashtable(int size, unsigned long int (*hash)(void*), int (*compareKey)(void*,void*), void *(*dupKey)(void*), void (*destroy)(void*)) {
    Hashtable *newHashtable = malloc(sizeof(Hashtable));
    newHashtable->size = size;
    newHashtable->nodes = 0;
    newHashtable->hash = hash;
    newHashtable->dupKey = dupKey;
    newHashtable->destroy = destroy;
    newHashtable->compareKey = compareKey;
    newHashtable->node = malloc(sizeof(struct hashtableNode) * size);
    for (int i=0; i<size; i++)
        newHashtable->node[i] = NULL;

    return newHashtable;
}

//funcção que retorna o apontador do nodo procurado
struct hashtableNode *searchHashtable(Hashtable *hashtable, void *key) {
    unsigned long int index = hashtable->hash(key) % hashtable->size; //indice para onde a chave mapeia
    struct hashtableNode *node = hashtable->node[index]; //primeiro nodo
    int (*compareKey)(void*,void*) = hashtable->compareKey;
    while (node != NULL && compareKey(node->key, key)) //procura em todos os nodos o elemento
        node = node->next;
    return node;
}
//função que copia toda a hashtable para outra hashtable
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable) {
    int size = hashtable->size;
    int newSize = newHashtable->size;
    struct hashtableNode **nodes = newHashtable->node;
    unsigned long int (*hash)(void*) = hashtable->hash;
    for (int i=0; i<size; i++) {
        struct hashtableNode *node = hashtable->node[i]; //para cada nodo da hashtable
        while (node != NULL) {
            unsigned long int index = hash(node->key) % newSize; //remapeia esse nodo para um novo lugar na newHashtable
            struct hashtableNode *new = malloc(sizeof(struct hashtableNode));
            new->key = node->key;
            new->data = node->data;
            new->next = nodes[index];
            nodes[index] = new;
            struct hashtableNode *oldNode = node;
            node = node->next; //próximo nodo na lista de colisões
            free(oldNode);
        }
    }
    newHashtable->nodes = hashtable->nodes;
}
//função que adiciona um novo elemento à hashtable
Hashtable *addHashtable(Hashtable *hashtable, void *data, void *key) {
    int nodes = hashtable->nodes, size = hashtable->size;
    float usage = nodes / size;
    if (usage >= 0.8) { //caso o uso dos nodos esteja acima de 80% cria uma nova hashtbale com o dobro do tamanho
        Hashtable *newHashtable = createHashtable(size * 2, hashtable->hash, hashtable->compareKey, hashtable->dupKey, hashtable->destroy);
        copyHashtable(hashtable, newHashtable);
        Hashtable *oldHashtable = hashtable;
        hashtable = newHashtable;
        free(oldHashtable->node);
        free(oldHashtable);
    }
    struct hashtableNode **node = hashtable->node;
    unsigned long int index = hashtable->hash(key) % hashtable->size;
    struct hashtableNode *new = malloc(sizeof(struct hashtableNode));
    new->key = hashtable->dupKey(key);
    new->data = data;
    new->next = node[index];
    node[index] = new;
    hashtable->nodes += 1;

    return hashtable;
}
//função que verifica se um elemento existe na hashtable
int existsData(Hashtable *hashtable, void *key) {
    if (searchHashtable(hashtable, key)) return 1; //caso o elemento exista
    return 0; //caso o elemnto não exista
}

//gets
//devolve número de nodos usados
int getHashtableUsed(Hashtable *hashtable) {
    return hashtable->nodes;
}
//função que devolve o elemento guardado na hashtable
void *getData(Hashtable *hashtable, void *key) {
    struct hashtableNode *node = searchHashtable(hashtable, key);
    if (!node) return NULL; //caso o elemento não exista
    return node->data; //caso exista
}
//função que altera um elemento da hashtable
void setData(Hashtable *hashtable, void *data, void *key) {
    struct hashtableNode *node = searchHashtable(hashtable, key);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}

//função que liberta toda a memória alocada pela hashtable
void destroyHashtable(Hashtable *hashtable) {
    if (hashtable == NULL) return;
    int size = hashtable->size;
    void (*destroy)(void*) = hashtable->destroy;
    for (int i=0; i<size; i++) { //para todos os indices da hashtable
        struct hashtableNode *node = hashtable->node[i];
        while (node != NULL) { //percorre todos os nodos
            struct hashtableNode *nodeAux = node->next; //proximo nodo guardado para o próximo ciclo
            destroy(node->data); //liberta o espaço em memória de cada elemento
            free(node->key); //liberta o id
            free(node); //liberta o nodo
            node = nodeAux; //avança para o próximo nodo
        }
    }
    free(hashtable->node); //liberta a lista de nodos
    free(hashtable); //liberta a hashtable
}

//hashtable de inteiros
struct hashtableNodeInt {
    unsigned long int key; //chave usada para hash
    void *data; //data guardada
    struct hashtableNodeInt *next; //próximo nodo para gerir colisões
};

struct hashtableInt {
    int size; //tamanho
    int nodes; //numero de nodos
    struct hashtableNodeInt **node; //ints
    void (*destroy)(void*);
};

//função que cria uma nova hashtable dado um tamanho e uma função de libertar o espaço em memória de cada elemento
HashtableInt *createHashtableInt(int size, void (*destroy)(void*)) {
    HashtableInt *newHashtable = malloc(sizeof(HashtableInt));
    newHashtable->size = size;
    newHashtable->nodes = 0;
    newHashtable->destroy = destroy;
    newHashtable->node = malloc(sizeof(struct hashtableNodeInt) * size);
    for (int i=0; i<size; i++) newHashtable->node[i] = NULL;
    return newHashtable;
}

//funcção que retorna o apontador do nodo procurado
struct hashtableNodeInt *searchHashtableInt(HashtableInt *hashtable, unsigned long int key) {
    unsigned long int index = (key) % hashtable->size; //indice para onde a chave mapeia
    struct hashtableNodeInt* node = hashtable->node[index]; //primeiro nodo
    while (node != NULL && node->key != key) //procura em todos os nodos o elemento
        node = node->next;
    return node;
}

//função que copia toda a hashtable para outra hashtable
void copyHashtableInt(HashtableInt *hashtable, HashtableInt *newHashtable) {
    int size = hashtable->size;
    int newSize = newHashtable->size;
    struct hashtableNodeInt **nodes = newHashtable->node;
    for (int i=0; i<size; i++) {
        struct hashtableNodeInt *node = hashtable->node[i]; //para cada nodo da hashtable
        while (node != NULL) {
            unsigned long int index = (node->key) % newSize; //remapeia esse nodo para um novo lugar na newHashtable
            struct hashtableNodeInt *new = malloc(sizeof(struct hashtableNodeInt));
            new->key = node->key;
            new->data = node->data;
            new->next = nodes[index];
            nodes[index] = new;
            struct hashtableNodeInt *oldNode = node;
            node = node->next; //próximo nodo na lista de colisões
            free(oldNode);
        }
    }
    newHashtable->nodes = hashtable->nodes;
}

//função que adiciona um novo elemento à hashtable
HashtableInt *addHashtableInt(HashtableInt *hashtable, void *data, unsigned long int key) {
    int nodes = hashtable->nodes, size = hashtable->size;
    float usage = nodes / size;
    if (usage >= 0.8) { //caso o uso dos nodos esteja acima de 80% cria uma nova hashtbale com o dobro do tamanho
        HashtableInt *newHashtable = createHashtableInt(size * 2, hashtable->destroy);
        copyHashtableInt(hashtable, newHashtable);
        HashtableInt *oldHashtable = hashtable;
        hashtable = newHashtable;
        free(oldHashtable->node);
        free(oldHashtable);
    }
    struct hashtableNodeInt **node = hashtable->node;
    unsigned long int index = (key) % hashtable->size;
    struct hashtableNodeInt *new = malloc(sizeof(struct hashtableNodeInt));
    new->key = (key);
    new->data = data;
    new->next = node[index];
    node[index] = new;
    hashtable->nodes += 1;

    return hashtable;
}

//função que verifica se um elemento existe na hashtable
int existsDataInt(HashtableInt *hashtable, unsigned long int key) {
    if (searchHashtableInt(hashtable, key)) return 1; //caso o elemento exista
    return 0; //caso o elemnto não exista
}

//gets
//devolve número de nodos usados
int getHashtableIntUsed(HashtableInt *hashtable) {
    return hashtable->nodes;
}

//função que devolve o elemento guardado na hashtable
void *getDataInt(HashtableInt *hashtable, unsigned long int key) {
    struct hashtableNodeInt *node = searchHashtableInt(hashtable, key);
    if (!node) return NULL; //caso não exista o elemento
    return node->data; //caso exista
}

//função que altera um elemento da hashtable
void setDataInt(HashtableInt *hashtable, void *data, unsigned long int key) {
    struct hashtableNodeInt *node = searchHashtableInt(hashtable, key);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}

//função que liberta toda a memória alocada pela hashtable
void destroyHashtableInt(HashtableInt *hashtable) {
    if (hashtable == NULL) return;
    int size = hashtable->size;
    void (*destroy)(void*) = hashtable->destroy;
    for (int i=0; i<size; i++) { //para todos os indices da hashtable
        struct hashtableNodeInt *node = hashtable->node[i];
        while (node != NULL) { //percorre todos os nodos
            struct hashtableNodeInt *nodeAux = node->next; //proximo nodo guardado para o próximo ciclo
            destroy(node->data); //liberta o espaço em memória de cada elemento
            free(node); //liberta o nodo
            node = nodeAux; //avança para o próximo nodo
        }
    }
    free(hashtable->node); //liberta a lista de nodos
    free(hashtable); //liberta a hashtable
}
