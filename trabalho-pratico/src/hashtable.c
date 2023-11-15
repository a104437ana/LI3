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
    int key;
    char *id;
    void *data;
    struct hashtableNode *next;
};

struct hashtable {
    int size;
    int nodes;
    HashtableNode **node;
};

//funcao hash
unsigned int hashFunction(char *id) {
    unsigned long int hash = 1;
    for (int i=0; id[i] != '\0'; i++)
        hash = hash * 33 ^ id[i]; // hash[i] = (hash[i-1] * 33) XOR id[i]

    return hash;
}

HashtableNode *createHashtableNode() {
    HashtableNode *node = malloc(sizeof(HashtableNode));
    node->key = 0;
    node->id = NULL;
    node->data = NULL;
    node->next = NULL;

    return node;
}

Hashtable *createHashtable(int size) {
    Hashtable *newHashtable = malloc(sizeof(Hashtable));
    newHashtable->size = size;
    newHashtable->nodes = 0;
    newHashtable->node = malloc(sizeof(HashtableNode) * size);
    for (int i=0; i<size; i++)
        newHashtable->node[i] = NULL;

    return newHashtable;
}

HashtableNode **searchNode(Hashtable *hashtable, unsigned int key, char *id) {
    int index = key % hashtable->size;
    HashtableNode **node = &(hashtable->node[index]);
    while ((*node) != NULL && strcmp((*node)->id, id))
        node = &((*node)->next);

    return node;
}

HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key, char *id) {
    return *(searchNode(hashtable, key, id));
}

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
    node = searchNode(hashtable, key, id);
    if (*node != NULL) {
        if (!strcmp((*node)->id, id)) return;
        node = &((*node)->next);
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

void destroyHashtable(Hashtable *hashtable) {
}
