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
typedef enum typeOfData {
    user,
    reservation,
    hotel,
    flight,
} TypeOfData;

struct hashtableNode {
    unsigned int key; //chave usada para hash
    void *data; //data guardada
    struct hashtableNode *next; //próximo nodo para gerir colisões
};

struct hashtable {
    int size; //tamanho
    int nodes; //numero de nodos
    struct hashtableNode **node; //lista dos primeiros nodos
    unsigned int (*hash)(void*);
    int (*compareKey)(void*,void*);
    void *(*dupKey)(void*);
    void (*destroy)(void*);
};

//funcao de hash
unsigned int hashString(void *key) {
    unsigned char *id = (unsigned char *) key, c;
    if (id == NULL) return 0;
    unsigned long int hash = 5381;
    while ((c = *id++)) //para cada caracter
        hash = ((hash << 5) + hash) + c; // hash[i] = (hash[i] * 33) + id[i]

    return hash;
}
unsigned int hashInt(void *key) {
    return *((unsigned int *) key);
}
////funcao de hash
//unsigned int hashString(void *key) {
//    char *id = (char *) key;
//    if (id == NULL) return 0;
//    int size = strlen(id);
//    unsigned long int hash = 1;
//    for (int i=0; i<size; i++) //para cada caracter
//        hash = hash * 33 ^ id[i]; // hash[i] = (hash[i-1] * 33) XOR id[i]
//
//    return hash;
//}
//função que cria uma nova hashtable com o tamanho dado
Hashtable *createHashtable(int size, unsigned int (*hash)(void*), int (*compareKey)(void*,void*), void *(*dupKey)(void*), void (*destroy)(void*)) {
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

//devolve número de nodos usados
int getHashtableUsed(Hashtable *hashtable) {
    return hashtable->nodes;
}

//funcção que retorna o apontador do nodo procurado
struct hashtableNode *searchHashtable(Hashtable *hashtable, void *key) {
    unsigned int hashKey = hashtable->hash(key);
    int index = hashKey % hashtable->size; //indice para onde a chave mapeia
    struct hashtableNode *node = hashtable->node[index]; //primeiro nodo
//    int (*compareKey)(void*,void*) = hashtable->compareKey;
    while (node != NULL && node->key != hashKey) //procura em todos os nodos o elemento
        node = node->next;
    return node;
}
//função que copia toda a hashtable para outra hashtable
void copyHashtable(Hashtable *hashtable, Hashtable *newHashtable) {
//    struct hashtableNode *node, *oldNode;
    int size = hashtable->size;
    int newSize = newHashtable->size;
    struct hashtableNode **nodes = newHashtable->node;
//    unsigned int (*hash)(void*) = hashtable->hash;
    for (int i=0; i<size; i++) {
        struct hashtableNode *node = hashtable->node[i];
        while (node != NULL) {
            unsigned int index = node->key % newSize;
            struct hashtableNode *new = malloc(sizeof(struct hashtableNode));
            new->key = node->key;
            new->data = node->data;
            new->next = nodes[index];
            nodes[index] = new;
            struct hashtableNode *oldNode = node;
            node = node->next;
            free(oldNode);
        }
    }
    newHashtable->nodes = hashtable->nodes;
}
//função que adiciona um novo elemento à hashtable
Hashtable *addHashtable(Hashtable *hashtable, void *data, void *key) {
    int nodes = hashtable->nodes, size = hashtable->size;
    float usage = nodes / size;
    if (usage >= 0.8) {
        Hashtable *newHashtable = createHashtable(size * 2, hashtable->hash, hashtable->compareKey, hashtable->dupKey, hashtable->destroy);
        copyHashtable(hashtable, newHashtable);
        Hashtable *oldHashtable = hashtable;
        hashtable = newHashtable;
        free(oldHashtable->node);
        free(oldHashtable);
    }
    struct hashtableNode **node = hashtable->node;
    unsigned int hashKey = hashtable->hash(key);
    int index = hashKey % hashtable->size;
    struct hashtableNode *new = malloc(sizeof(struct hashtableNode));
    new->key = hashKey;
    new->data = data;
    new->next = node[index];
    node[index] = new;
    hashtable->nodes += 1;

    return hashtable;
}

//falta remove elemento
void removeHashtable(Hashtable *hashtable, unsigned int key) {
}
//função que verifica se um elemento existe na hashtable
int existsData(Hashtable *hashtable, void *key) {
    if (searchHashtable(hashtable, key)) return 1; //caso o elemento exista
    return 0; //caso o elemnto não exista
}

//gets
//função que devolve o elemento guardado na hashtable
void *getData(Hashtable *hashtable, void *key) {
    struct hashtableNode *node = searchHashtable(hashtable, key);
    if (!node) return NULL;
    return node->data;
}
int getHashtableNodes(Hashtable *hashtable) {
    return hashtable->nodes;
}
//função que altera um elemento da hashtable
void setData(Hashtable *hashtable, void *data, void *key) {
    struct hashtableNode *node = searchHashtable(hashtable, key);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}
//função que ordena um parametro de todos os elementos de uma hashtable dada uma função de ordenação
void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable) {
    struct hashtableNode **node = hashtable->node; //todos os nodos da hashtable
    int size = hashtable->size; //tamanho da hashtable
    struct hashtableNode *iNode; //nodo de indice i da hashtable
    for (int i=0; i<size; i++) { //para cada indice da hashtable
        iNode = node[i];
        while (iNode != NULL) { //percorre todos os nodos
            sortFunction(iNode->data, lookupTable); //e aplica a função de ordenação a cada elemento da hashtable
            iNode = iNode->next;
        }
    }
}
//void *getNextData(Hashtable *hashtable, unsigned int key, char *id) {
//    int size = hashtable->size;
//    int index = key % size;
//    struct hashtableNode *node = hashtable->node[index];
//    if (node && node->next != NULL) node = node->next;
//    else {
//        index = (index + 1) % size;
//        while ((node = hashtable->node[index]) == NULL) index = (index + 1) % size;
//    }
//    return node->data;
//}
//função que imprime todos os elementos da hashtable, para efeitos de teste
void printTable(Hashtable *hashtable, void (*printFunction)(void*)) {
    struct hashtableNode *node;
    int size = hashtable->size;
    for (int i=0; i<size; i++) { //percorre todos os indices da hashtable
        node = hashtable->node[i];
        printf("%2d", i);
        if (node == NULL) printf(" ->    X\n");
        else {
            while (node != NULL) { //aplica a função de imprimir um elemento a todos os elementos nos nodos nesse indice
//                printf(" -> (%4d,", node->key);
                (*printFunction)(node->data);
                node = node->next;
            }
            printf(" -> X\n");
        }
    }
}
//função que imprime o nível de uso da hashtable, para efeitos de testes
void printHashtableUsage(Hashtable *hashtable) {
    float usage = (float) hashtable->nodes / (float) hashtable->size;
    printf("usage: %.3f\n", usage);
    printf("nodes: %d\n", hashtable->nodes);
    printf("size: %d\n", hashtable->size);
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
//            free(node->data); //double free se função anterior já libertar o espaço em memória do apontador
//            free(node->key); //liberta o id
            free(node); //liberta o nodo
            node = nodeAux; //avança para o próximo nodo
        }
    }
    free(hashtable->node);
    free(hashtable); //liberta a hashtable
}
