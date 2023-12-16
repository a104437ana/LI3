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

//funcao de hash
unsigned int hashFunction(char *id) {
    unsigned long int hash = 1;
    for (int i=0; id[i] != '\0'; i++) //para cada caracter
        hash = hash * 33 ^ id[i]; // hash[i] = (hash[i-1] * 33) XOR id[i]

    return hash;
}
//função que cria um novo nodo vazio
HashtableNode *createHashtableNode() {
    HashtableNode *node = malloc(sizeof(HashtableNode));
    node->key = 0;
    node->id = NULL;
    node->data = NULL;
    node->next = NULL;

    return node;
}
//função que cria uma nova hashtable com o tamanho dado
Hashtable *createHashtable(int size) {
    Hashtable *newHashtable = malloc(sizeof(Hashtable));
    newHashtable->size = size;
    newHashtable->nodes = 0;
    newHashtable->node = malloc(sizeof(HashtableNode) * size);
    for (int i=0; i<size; i++)
        newHashtable->node[i] = NULL;

    return newHashtable;
}
//função que procura um nodo onde se encontra o elemento com o id dado
HashtableNode **searchNode(Hashtable *hashtable, unsigned int key, char *id) {
    int index = key % hashtable->size; //indice para onde aponta a chave
    HashtableNode **node = &(hashtable->node[index]); //primeiro nodo com esse indice
    while ((*node) != NULL && strcmp((*node)->id, id)) //procura nodo com id se existir
        node = &((*node)->next);

    return node; //retorna o endereço do nodo encontrado ou o endereço do campo next caso não encontre nenhum elemnto
}
//funcção que retorna o apontador do nodo procurado
HashtableNode *searchHashtable(Hashtable *hashtable, unsigned int key, char *id) {
    return *(searchNode(hashtable, key, id));
}
//função que copia toda a hashtable para outra hashtable
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
//função que adiciona um novo elemento à hashtable
void addHashtable(Hashtable *hashtable, unsigned int key, void *data, char *id) {
    HashtableNode **node;
    //falta implementar alocamento dinâmico da hashtable para um determinado nível de uso
    //e mudar para inserir ao início da lista e fazer a procura antes de chamar a função
//    int nodes = hashtable->nodes, size = hashtable->size;
//    float usage = nodes / size;
//    if (usage >= 2) {
//        Hashtable *newHashtable = createHashtable(size * 2);
//        copyHashtable(hashtable, newHashtable);
//        Hashtable *oldHashtable = hashtable;
//        destroyHashtable(oldHashtable);
//        hashtable = newHashtable;
//    }
    node = searchNode(hashtable, key, id); //procura onde inserir o novo elemnto
    if (*node != NULL) { //caso essa chave já existir na hashtable
        if (!strcmp((*node)->id, id)) return; //caso o elemento já exista na hashtable
        node = &((*node)->next); //caso naõ exista insere no próximo nodo
    }
    *node = createHashtableNode();
    (*node)->key = key;
    (*node)->id = strdup(id);
    (*node)->data = data;
    hashtable->nodes += 1;
}

//falta remove elemento
void removeHashtable(Hashtable *hashtable, unsigned int key) {
}
//função que verifica se um elemento existe na hashtable
int existsData(Hashtable *hashtable, unsigned int key, char *id) {
    int index = key % hashtable->size; //indice para onde a chave mapeia
    HashtableNode *node = hashtable->node[index]; //primeiro nodo
    while (node != NULL && strcmp(node->id, id)) //procura em todos os nodos o elemento
        node = node->next;
    if (node != NULL) return 1; //caso encontre um elemento
    return 0; //caso o elemnto não exista
}

//gets
//função que devolve o elemento guardado na hashtable
void *getData(Hashtable *hashtable, unsigned int key, char *id) {
    HashtableNode *node = searchHashtable(hashtable, key, id);
    if (node == NULL) return node;

    return node->data;
}
//função que altera um elemento da hashtable
void setData(Hashtable *hashtable, unsigned int key, void *data, char *id) {
    HashtableNode *node = searchHashtable(hashtable, key, id);
    void *oldData = node->data;
    node->data = data;
    free(oldData);
}
//função que ordena um parametro de todos os elementos de uma hashtable dada uma função de ordenação
void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable) {
    HashtableNode **node = hashtable->node; //todos os nodos da hashtable
    int size = hashtable->size; //tamanho da hashtable
    HashtableNode *iNode; //nodo de indice i da hashtable
    for (int i=0; i<size; i++) { //para cada indice da hashtable
        iNode = node[i];
        while (iNode != NULL) { //percorre todos os nodos
            sortFunction(iNode->data, lookupTable); //e aplica a função de ordenação a cada elemento da hashtable
            iNode = iNode->next;
        }
    }
}
//função que imprime todos os elementos da hashtable, para efeitos de teste
void printTable(Hashtable *hashtable, void (*printFunction)(void*)) {
    HashtableNode *node;
    int size = hashtable->size;
    for (int i=0; i<size; i++) { //percorre todos os indices da hashtable
        node = hashtable->node[i];
        printf("%2d", i);
        if (node == NULL) printf(" ->    X\n");
        else {
            while (node != NULL) { //aplica a função de imprimir um elemento a todos os elementos nos nodos nesse indice
                printf(" -> (%4d,", node->key);
                (*printFunction)(node->data);
                node = node->next;
            }
            printf(" -> X\n");
        }
    }
}
//função que imprime todas as reservas de todos os hoteis da hashtable, para efeitos de testes
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
//função que imprime o nível de uso da hashtable, para efeitos de testes
void printHashtableUsage(Hashtable *hashtable) {
    float usage = (float) hashtable->nodes / (float) hashtable->size;
    printf("usage: %.3f\n", usage);
    printf("nodes: %d\n", hashtable->nodes);
    printf("size: %d\n", hashtable->size);
}
//função que liberta toda a memória alocada pela hashtable
void destroyHashtable(Hashtable *hashtable, void (*destroyDataFunction)(void*)) {
    if (hashtable == NULL) return;
    int size = hashtable->size;
    HashtableNode *node, *nodeAux;
    for (int i=0; i<size; i++) { //para todos os indices da hashtable
        node = hashtable->node[i];
        while (node != NULL) { //percorre todos os nodos
            nodeAux = node->next; //proximo nodo guardado para o próximo ciclo
            (*destroyDataFunction)(node->data); //liberta o espaço em memória de cada elemento
//            free(node->data); //double free se função anterior já libertar o espaço em memória do apontador
            free(node->id); //liberta o id
            free(node); //liberta o nodo
            node = nodeAux; //avança para o próximo nodo
        }
    }
    free(hashtable->node);
    free(hashtable); //liberta a hashtable
}
