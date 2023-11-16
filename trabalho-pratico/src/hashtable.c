#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hotel.h"

typedef enum typeOfData {
    user,
    reservation,
    hotel,
    flight,
} TypeOfData;

struct hashtableNode {
    int key; //chave de hash
    char *id; //id usado para hash
    void *data; //data guardada
    struct hashtableNode *next; //próximo nodo para gerir colisões
};

struct hashtable {
    int size; //tamanho
    int nodes; //numero de nodos
    HashtableNode **node; //lista dos primeiros nodos
};

//funcao hash
unsigned int hashFunction(char *id) {
    unsigned long int hash = 1;
    for (int i=0; id[i] != '\0'; i++)
        hash = hash * 33 ^ id[i]; // hash[i] = (hash[i-1] * 33) XOR id[i]

    return hash;
}
//cria um novo nodo vazio
HashtableNode *createHashtableNode() {
    HashtableNode *node = malloc(sizeof(HashtableNode));
    node->key = 0;
    node->id = NULL;
    node->data = NULL;
    node->next = NULL;

    return node;
}
//cria hashtable vazia
Hashtable *createHashtable(int size) {
    Hashtable *newHashtable = malloc(sizeof(Hashtable));
    newHashtable->size = size;
    newHashtable->nodes = 0;
    newHashtable->node = malloc(sizeof(HashtableNode) * size);
    for (int i=0; i<size; i++)
        newHashtable->node[i] = NULL;

    return newHashtable;
}
//procura nodo com o id dado na hashtable
HashtableNode **searchNode(Hashtable *hashtable, unsigned int key, char *id) {
    int index = key % hashtable->size; //indice para onde aponta a chave
    HashtableNode **node = &(hashtable->node[index]); //primeiro nodo com esse indice
    while ((*node) != NULL && strcmp((*node)->id, id)) //procura nodo com id se existir
        node = &((*node)->next);

    return node;
}

HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key, char *id) {
    return *(searchNode(hashtable, key, id));
}
//copia uma hashtable para outra
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable) {
    HashtableNode *node;
    int size = hashtable->size;
    for (int i=0; i<size; i++) {
        node = hashtable->node[i];
        while (node != NULL) {
            addHashtable(newHashtable, node->key, node->data, node->id);
            node = node->next;
        }
    }
}
//adiciona nova data à hashtable
void addHashtable(Hashtable *hashtable, unsigned int key, void *data, char *id) {
    HashtableNode **node;
    //falta implementar alocamento dinâmico da hashtable para um determinado nível de uso
//    int nodes = hashtable->nodes, size = hashtable->size;
//    float usage = nodes / size;
//    if (usage >= 2) {
//        Hashtable *newHashtable = createHashtable(size * 2);
//        copyHashtable(hashtable, newHashtable);
//        Hashtable *oldHashtable = hashtable;
//        destroyHashtable(oldHashtable);
//        hashtable = newHashtable;
//    }
    node = searchNode(hashtable, key, id); //procura onde inserir a nova data
    if (*node != NULL) {
        if (!strcmp((*node)->id, id)) return; //caso a data já exista na hashtable
        node = &((*node)->next); //caso naõ exista insere no próximo nodo
    }
    *node = createHashtableNode();
    (*node)->key = key;
    (*node)->id = strdup(id);
    (*node)->data = data;
    hashtable->nodes += 1;
}

//fazer remove
void removeHashtable(Hashtable *hashtable, unsigned int key) {
}

int existsData(Hashtable *hashtable, unsigned int key, char *id) {
    int index = key % hashtable->size;
    HashtableNode *node = hashtable->node[index];
    while (node != NULL && strcmp(node->id, id))
        node = node->next;
    if (node != NULL) return 1;
    return 0;
}

//gets
void *getData(Hashtable *hashtable, unsigned int key, char *id) {
    HashtableNode *node = searchHashtable(hashtable, key, id);
    if (node == NULL) return node;

    return node->data;
}

void setData(Hashtable *hashtable, unsigned int key, void *data, char *id) {
    HashtableNode *node = searchHashtable(hashtable, key, id);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}
//nao usado
void *getDataIndex(Hashtable *hashtable, unsigned int index) {
    return NULL;
}

void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*)) {
    HashtableNode **node = hashtable->node;
    int size = hashtable->size;
    HashtableNode *iNode;
    for (int i=0; i<size; i++) {
        iNode = node[i];
        while (iNode != NULL) {
            sortFunction(iNode->data);
            iNode = iNode->next;
        }
    }
}

void printTable(Hashtable *hashtable, void (*printFunction)(void*)) {
    HashtableNode *node;
    int size = hashtable->size;
    for (int i=0; i<size; i++) {
        node = hashtable->node[i];
        printf("%2d", i);
        if (node == NULL) printf(" ->    X\n");
        else {
            while (node != NULL) {
                printf(" -> (%4d,", node->key);
                (*printFunction)(node->data);
                node = node->next;
            }
            printf(" -> X\n");
        }
    }
}

void printHotelTableReservs(Hashtable *hashtable, void (*printFunction)(void*)) {
    HashtableNode *node;
    int size = hashtable->size;
    for (int i=0; i<size; i++) {
        node = hashtable->node[i];
        printf("%2d", i);
        if (node == NULL) printf(" ->    X\n");
        else {
            while (node != NULL) {
                printf(" -> (%4d", node->key);
                printOrdList(getHotelOrdList(node->data), printFunction);
                node = node->next;
            }
            printf(" -> X\n");
        }
    }
}

void printHashtableUsage(Hashtable *hashtable) {
    float usage = (float) hashtable->nodes / (float) hashtable->size;
    printf("usage: %.3f\n", usage);
    printf("nodes: %d\n", hashtable->nodes);
    printf("size: %d\n", hashtable->size);
}

void removeNode(HashtableNode *node) {
//    switch (typeOfData) {
//        case user:
//            destroyUser(node->data);
//            break;
//        case reservation:
//            destroyReservation(node->data);
//            break;
//        case hotel:
//            destroyHotel(node->data);
//            break;
//        case flight:
//            destroyFlight(node->data);
//            break;
//    }
//    free(node->id);
}

void destroyHashtable(Hashtable *hashtable, void (*destroyDataFunction)(void*)) {
    if (hashtable == NULL) return;
    int size = hashtable->size;
    HashtableNode *node, *nodeAux;
    for (int i=0; i<size; i++) {
        node = hashtable->node[i];
        while (node != NULL) {
            nodeAux = node->next;
            (*destroyDataFunction)(node->data);
//            free(node->data);
            free(node->id);
            free(node);
            node = nodeAux;
        }
    }
    free(hashtable);
}
