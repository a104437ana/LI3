#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define FREE 0
#define USED 1
#define DEL  2

typedef enum typeOfData {
    user,
    reservation,
    hotel,
    flight,
} TypeOfData;

struct hashtableNode {
    int status;
    void *key; //chave
    void *data; //data guardada
};

struct hashtable {
    int size; //tamanho
    int used; //numero de nodos usados
    int deleted; //numero de nodos eliminados
    struct hashtableNode *node; //lista dos nodos
    unsigned int (*hash)(void*);
    unsigned int (*index)(int);
    void (*destroy)(void*);
};

//funcao de hash
unsigned int hashFunction(char *id) {
    unsigned long int hash = 1;
    if (id == NULL) return 0;
    for (int i=0; id[i] != '\0'; i++) //para cada caracter
        hash = hash * 33 ^ id[i]; // hash[i] = (hash[i-1] * 33) XOR id[i]

    return hash;
}
//função que cria uma nova hashtable com o tamanho dado
Hashtable *createHashtable(int size, unsigned int (*hash)(void*), unsigned int (*index)(int), void (*destroy)(void*)) {
    Hashtable *newHashtable = malloc(sizeof(Hashtable));
    newHashtable->size = size;
    newHashtable->used = 0;
    newHashtable->deleted = 0;
    newHashtable->hash = hash;
    newHashtable->index = index;
    newHashtable->destroy = destroy;
    newHashtable->node = malloc(sizeof(struct hashtableNode) * size);
    for (int i=0; i<size; i++) {
        newHashtable->node[i].status = FREE;
        newHashtable->node[i].key = NULL;
        newHashtable->node[i].data = NULL;
    }

    return newHashtable;
}

//devolve número de nodos usados
int getHashtableUsed(Hashtable *hashtable) {
    return hashtable->used;
}

//função que procura um nodo onde se encontra o elemento com o id dado
unsigned int searchIndex(Hashtable *hashtable, void *id) {
    unsigned int key = hashtable->hash(id);
    int size = hashtable->size;
    unsigned int index = key % size;
    unsigned int iniIndex = index;
    int exit = 0;
//    unsigned int (*probe)(int) = hashtable->index;
    while (!exit && hashtable->node[index].status == DEL) {
        index = hashtable->index(index) % size;
        if (iniIndex == index) exit = 1;
    }
    if (exit || hashtable->node[index].status == FREE) return -1;
    return index;
}
unsigned int addIndex(Hashtable *hashtable, void *id) {
    unsigned int key = hashtable->hash(id);
    int size = hashtable->size;
    unsigned int index = key % size;
    unsigned int iniIndex = index;
    int exit = 0;
//    unsigned int (*probe)(int) = hashtable->index;
    while (!exit && hashtable->node[index].status == USED) {
        index = hashtable->index(index) % size;
        if (iniIndex == index) exit = 1;
    }
    if (exit) return -1;
    return index;
}
//função que copia toda a hashtable para outra hashtable
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable) {
    struct hashtableNode *node, *newNode;
    int size = hashtable->size;
    unsigned int index;
    for (int i=0; i<size; i++) {
        node = &(hashtable->node[i]);
        index = addIndex(newHashtable, node->key);
        newNode = &(newHashtable->node[index]);
        if (node->status == USED) {
            newNode->status = USED;
            newNode->key = node->key;
            newNode->data = node->data;
            newHashtable->used++;
        }
        else if (node->status == DEL) {
            free(node->key);
            hashtable->destroy(node->data);
        }
    }
}
//função que adiciona um novo elemento à hashtable
Hashtable *addHashtable(Hashtable *hashtable, void *data, void *id) {
    int nodes = hashtable->used, size = hashtable->size;
    float usage = nodes / size;
    if (usage >= 0.8) {
        Hashtable *newHashtable = createHashtable(size * 2, hashtable->hash, hashtable->index, hashtable->destroy);
        copyHashtable(hashtable, newHashtable);
        Hashtable *oldHashtable = hashtable;
        hashtable = newHashtable;
        free(oldHashtable->node);
        free(oldHashtable);
    }
    unsigned int index = addIndex(hashtable, id);
    struct hashtableNode *node = &(hashtable->node[index]);
    if (node == NULL) return hashtable;
    node->status = USED;
    node->key = id;
    node->data = data;
    hashtable->used++;

    return hashtable;
}

//falta remove elemento
void removeHashtable(Hashtable *hashtable, unsigned int key) {
}
//função que verifica se um elemento existe na hashtable
int existsData(Hashtable *hashtable, void *id) {
    unsigned int index = searchIndex(hashtable, id);
    if (index == -1) return 0;
    struct hashtableNode *node = &(hashtable->node[index]);
    if (node != NULL) return 1;
    return 0; //caso o elemento não exista
}

//gets
//função que devolve o elemento guardado na hashtable
void *getData(Hashtable *hashtable, void *id) {
    unsigned int index = searchIndex(hashtable, id);
    if (index == -1) return NULL;
    struct hashtableNode *node = &(hashtable->node[index]);
    if (node == NULL) return node;

    return node->data;
}
int getHashtableNodes(Hashtable *hashtable) {
    return hashtable->used;
}
//função que altera um elemento da hashtable
void setData(Hashtable *hashtable, void *data, void *id) {
    unsigned int index = searchIndex(hashtable, id);
    if (index == -1) return;
    struct hashtableNode *node = &(hashtable->node[index]);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}
////função que ordena um parametro de todos os elementos de uma hashtable dada uma função de ordenação
//void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable) {
//    struct hashtableNode **node = hashtable->node; //todos os nodos da hashtable
//    int size = hashtable->size; //tamanho da hashtable
//    struct hashtableNode *iNode; //nodo de indice i da hashtable
//    for (int i=0; i<size; i++) { //para cada indice da hashtable
//        iNode = node[i];
//        while (iNode != NULL) { //percorre todos os nodos
//            sortFunction(iNode->data, lookupTable); //e aplica a função de ordenação a cada elemento da hashtable
//            iNode = iNode->next;
//        }
//    }
//}
//void *getNextData(Hashtable *hashtable, int index) {
//    struct hashtableNode *node = &(hashtable->node[index]);
//    while (node->status != USED) {
//        index++;
//        node = hashtable->node[index];
//    }
//    return node->data;
//}
//função que imprime o nível de uso da hashtable, para efeitos de testes
void printHashtableUsage(Hashtable *hashtable) {
    float usage = (float) hashtable->used / (float) hashtable->size;
    printf("usage: %.3f\n", usage);
    printf("nodes: %d\n", hashtable->used);
    printf("deleted: %d\n", hashtable->deleted);
    printf("size: %d\n", hashtable->size);
}
//função que liberta toda a memória alocada pela hashtable
void destroyHashtable(Hashtable *hashtable) {
    if (hashtable == NULL) return;
    int size = hashtable->size;
    struct hashtableNode *node;
    for (int i=0; i<size; i++) { //para todos os indices da hashtable
        node = &(hashtable->node[i]);
        free(node->key); //liberta a chave
        hashtable->destroy(node->data); //liberta o espaço em memória de cada elemento
    }
    free(hashtable->node);
    free(hashtable); //liberta a hashtable
}
