#ifndef _HASHTABLE_
#define _HASHTABLE_

#define FREE 0
#define USED 1
#define DEL  2

typedef struct hashtable Hashtable;

//funcao de hash
unsigned int hashString(char *id);

//função que cria uma nova hashtable com o tamanho dado
Hashtable *createHashtable(int size, unsigned int (*hash)(void*), unsigned int (*index)(int), void (*destroy)(void*));

//devolve número de nodos usados
int getHashtableUsed(Hashtable *hashtable);

//função que procura um nodo onde se encontra o elemento com o id dado
unsigned int searchIndex(Hashtable *hashtable, void *id);

//função que adiciona um novo elemento à hashtable
Hashtable *addHashtable(Hashtable *hashtable, void *data, void *id);

//falta remove elemento
void removeHashtable(Hashtable *hashtable, unsigned int key);

//função que verifica se um elemento existe na hashtable
int existsData(Hashtable *hashtable, void *id);

//gets
//função que devolve o elemento guardado na hashtable
void *getData(Hashtable *hashtable, void *id);

int getHashtableNodes(Hashtable *hashtable);

//função que altera um elemento da hashtable
void setData(Hashtable *hashtable, void *data, void *id);

////função que ordena um parametro de todos os elementos de uma hashtable dada uma função de ordenação
//void sortOrdlistHashtable(Hashtable *hashtable, void (*sortFunction)(void*,Hashtable*), Hashtable *lookupTable);

void *getNextData(Hashtable *hashtable, int index);

//função que imprime o nível de uso da hashtable, para efeitos de testes
void printHashtableUsage(Hashtable *hashtable);

//função que liberta toda a memória alocada pela hashtable
void destroyHashtable(Hashtable *hashtable);

#endif