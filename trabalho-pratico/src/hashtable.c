#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "hotel.h"

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
        hash = hash * 33 ^ id[i];

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
//    if (*node != NULL && (*node)->key != key) {
    if (*node != NULL && strcmp((*node)->id, id)) {
        while ((*node)->next != NULL && strcmp((*node)->id, id)) {
            node = &((*node)->next);
        }
    }

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
//        if ((*node)->key == key) return;
        if (!strcmp((*node)->id, id)) return;
        node = &((*node)->next);
    }
    *node = createHashtableNode();
    (*node)->key = key;
    (*node)->id = strdup(id);
    (*node)->data = data;
    hashtable->nodes += 1;
}

//void addHashtable(Hashtable *hashtable, unsigned int key, void *data, char *id) {
//    HashtableNode *node, *nodeAux;
////    int nodes = hashtable->nodes, size = hashtable->size;
////    float usage = nodes / size;
////    if (usage >= 2) {
////        Hashtable *newHashtable = createHashtable(size * 2);
////        copyHashtable(hashtable, newHashtable);
////        Hashtable *oldHashtable = hashtable;
////        destroyHashtable(oldHashtable);
////        hashtable = newHashtable;
////    }
//    int index = key % hashtable->size;
//    nodeAux = hashtable->node[index];
//    node = createHashtableNode();
//    node->key = key;
//    node->id = strdup(id);
//    node->data = data;
//    node->next = nodeAux;
//    hashtable->node[index] = node;
//    hashtable->nodes += 1;
//}

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

//void *getData(Hashtable *hashtable, unsigned int key, char *id) {
//    int index = key % hashtable->size;
//    HashtableNode *node = hashtable->node[index];
//    while (node != NULL && strcmp(node->id, id))
//        node = node->next;
//    if (node == NULL) return NULL;
//
//    return node->data;
//}

void setData(Hashtable *hashtable, unsigned int key, void *data, char *id) {
    HashtableNode *node = searchHashtable(hashtable, key, id);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}

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

void destroyHashtable(Hashtable *hashtable) {
}
