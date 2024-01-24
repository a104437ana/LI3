#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

struct heap {
    int used;
    int size;
    void **data;
    int (*compare)(void*,void*,void*);
    int (*addCompare)(void*,void*,void*);
    void *lookup;
    void (*destroy)(void*);
};

//troca a posição de dois elementos na heap
void swapHeap(Heap heap, int i, int j) {
    void *aux = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = aux;
}

//puxa um elemento para baixo da heap até estar numa posição válida
int bubbleDown(Heap heap) {
    int i = 0, e = 1, d = 2;
    int size = heap->used, min;
    void *lookup = heap->lookup;
    while (e < size) {
        if (d < size) min = heap->compare(heap->data[e],heap->data[d],lookup) <= 0 ? e : d; //mínimo dos dois filhos da posição atual
        else min = e;
        if (heap->compare(heap->data[i],heap->data[min],lookup) > 0) { //caso a posição atual seja maior que o mínimo
            swapHeap(heap, i, min); //troca as posições
            i = min; //atualiza posição atual e filhos dessa posição
            e = (i * 2) + 1;
            d = e + 1;
        }
        else break; //caso contrário pára o ciclo
    }
    return i;
}

//puxa um elemento para cima da heap até estar numa posição válida
int bubbleUp(Heap heap) {
    int i = heap->used-1, p = (i - 1) / 2;
    void *lookup = heap->lookup;
    while (i > 0 && heap->compare(heap->data[i],heap->data[p],lookup) < 0) { //enquanto posição atual for menor que o pai
        swapHeap(heap, i, p); //troca as posições
        i = p; //atualiza posição atual e o pai
        p = (i - 1) / 2;
    }
    return i;
}

//cria uma nova heap
Heap createHeap(int k, int (*compareFunction)(void*,void*,void*), int (*addCompareFunction)(void*,void*,void*), void *lookupTable, void (*destroyFunction)(void*)) {
    Heap h = malloc(sizeof(struct heap));
    h->used = 0;
    h->size = k;
    h->data = malloc(sizeof(void*) * k);
    h->compare = compareFunction;
    h->addCompare = addCompareFunction;
    h->lookup = lookupTable;
    h->destroy = destroyFunction;
    return h;
}
//adiciona um elemento à heap
int addHeap(void *data, Heap heap) {
    int used = heap->used, size = heap->size;
    int added = -1;
    if (used < size) { //caso a heap não estaja preenchida
        heap->data[used] = data; //insere no último elemento
        heap->used++;
        added = bubbleUp(heap); //atualiza a heap
    }
    else {
        if (heap->addCompare(heap->data[0],data,heap->lookup) < 0) { //caso esteja preenchida e possa inserir um novo elemento
            void *aux = heap->data[0];
            heap->data[0] = data; //insero novo elemento no início da heap
            heap->destroy(aux);
            added = bubbleDown(heap); //atualiza a heap
        }
    }
    return added;
}
//remove o primeiro elemento da heap
void *removeHeap(Heap heap) {
    if (heap->used > 0) {
        heap->used--;
        swapHeap(heap, 0, heap->used);
        bubbleDown(heap); //atualiza a heap
    }
    else return NULL;
    return heap->data[heap->used]; //retorna primeiro elemento
}
//retorna o número de espaços preenchidos na heap
int getHeapUsed(Heap heap) {
    return heap->used;
}

//liberta o espaço alocado pela heap
void destroyHeap(Heap heap) {
    int i, size = heap->used;
    for (i=0; i<size; i++)
        heap->destroy(heap->data[i]);
    free(heap->data);
    free(heap);
}
