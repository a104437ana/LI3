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

void swapHeap(Heap heap, int i, int j) {
    void *aux = heap->data[i];
    heap->data[i] = heap->data[j];
    heap->data[j] = aux;
}

int bubbleDown(Heap heap) {
    int i = 0, e = 1, d = 2;
    int size = heap->used, min;
    void *lookup = heap->lookup;
    while (e < size) {
        if (d < size) min = heap->compare(heap->data[e],heap->data[d],lookup) <= 0 ? e : d;
        else min = e;
        if (heap->compare(heap->data[i],heap->data[min],lookup) > 0) {
            swapHeap(heap, i, min);
            i = min;
            e = (i * 2) + 1;
            d = e + 1;
        }
        else break;
    }
    return i;
}

int bubbleUp(Heap heap) {
    int i = heap->used-1, p = (i - 1) / 2;
    void *lookup = heap->lookup;
    while (i > 0 && heap->compare(heap->data[i],heap->data[p],lookup) < 0) {
        swapHeap(heap, i, p);
        i = p;
        p = (i - 1) / 2;
    }
    return i;
}

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
int addHeap(void *data, Heap heap) {
    int used = heap->used, size = heap->size;
    int added = -1;
    if (used < size) {
        heap->data[used] = data;
        heap->used++;
        added = bubbleUp(heap);
    }
    else {
        if (heap->addCompare(heap->data[0],data,heap->lookup) < 0) {
            void *aux = heap->data[0];
            heap->data[0] = data;
            heap->destroy(aux);
            added = bubbleDown(heap);
        }
    }
    return added;
}
void *removeHeap(Heap heap) {
    if (heap->used > 0) {
        heap->used--;
        swapHeap(heap, 0, heap->used);
        bubbleDown(heap);
    }
    else return NULL;
    return heap->data[heap->used];
}
int getHeapUsed(Heap heap) {
    return heap->used;
}

void destroyHeap(Heap heap) {
    int i, size = heap->used;
    for (i=0; i<size; i++)
        heap->destroy(heap->data[i]);
    free(heap->data);
    free(heap);
}
