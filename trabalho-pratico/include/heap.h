#ifndef _HEAP_
#define _HEAP_

typedef struct heap *Heap;

Heap createHeap(int k, int (*compareFunction)(void*,void*,void*), int (*addCompareFunction)(void*,void*,void*), void *lookup, void (*destroyFunction)(void*));
int addHeap(void *data, Heap heap);
void *removeHeap(Heap heap);
int getHeapUsed(Heap heap);

void destroyHeap(Heap heap);

#endif