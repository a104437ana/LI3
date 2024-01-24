#ifndef _HEAP_
#define _HEAP_

typedef struct heap *Heap;

//cria uma nova heap
Heap createHeap(int k, int (*compareFunction)(void*,void*,void*), int (*addCompareFunction)(void*,void*,void*), void *lookup, void (*destroyFunction)(void*));
//adiciona um elemento à heap
int addHeap(void *data, Heap heap);
//remove o primeiro elemento da heap
void *removeHeap(Heap heap);
//retorna o número de espaços preenchidos na heap
int getHeapUsed(Heap heap);

//liberta o espaço alocado pela heap
void destroyHeap(Heap heap);

#endif