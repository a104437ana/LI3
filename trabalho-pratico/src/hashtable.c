#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

struct hashtableNode {
    int key;
    void *data;
    struct hashtableNode *next;
};

struct hashtable {
    int size;
    int nodes;
    HashtableNode **node;
};

//funcao hash simples
unsigned int hashFunction(char *id) {
    unsigned int hash = 0;
    for (int i=0; id[i]; i++) 
        hash += id[i];

    return hash;
}

HashtableNode *createHashtableNode() {
    HashtableNode *node = malloc(sizeof(HashtableNode));
    node->key = 0;
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

HashtableNode **searchNode(Hashtable *hashtable, unsigned int key) {
    int index = key % hashtable->size;
    HashtableNode **node = &(hashtable->node[index]);
    if (*node != NULL) {
        while ((*node)->next != NULL)
            node = &((*node)->next);
    }

    return node;
}

HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key) {
    return *(searchNode(hashtable, key));
}

void addHashtable(Hashtable *hashtable, unsigned int key, void *data) {
    int index = key % hashtable->size;
    HashtableNode **node = &(hashtable->node[index]);
    node = searchNode(hashtable, key);
    if (*node != NULL) node = &((*node)->next);
    *node = createHashtableNode();
    (*node)->key = key;
    (*node)->data = data;
    hashtable->nodes += 1;
}

//fazer remove
void removeHashtable(Hashtable *hashtable, unsigned int key) {
}

//gets e sets provisorios para teste
int getSize(Hashtable *hashtable) {
    return hashtable->size;
}

int getNodes(Hashtable *hashtable) {
    return hashtable->nodes;
}

//gets
void *getDate(Hashtable *hashtable, unsigned int key) {
    HashtableNode *node = searchHashtable(hashtable, key);

    return node->data;
}

void setDate(Hashtable *hashtable, unsigned int key, void *data) {
    HashtableNode *node = searchHashtable(hashtable, key);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}

void printTable(Hashtable *hashtable, void (*printFunction)(void*)) {
    HashtableNode *node;
    int size = hashtable->size;
    for (int i=0; i<size; i++) {
        node = hashtable->node[i];
        printf("%2d", i);
        if (node == NULL) printf(" ->    0");
        while (node != NULL) {
            printf(" -> %4d", node->key);
            (*printFunction)(node->data);
            node = node->next;
        }
        printf(" -> X\n");
    }
}

void destroyHashtable(Hashtable *hashtable) {
}
