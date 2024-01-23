#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "orderedList.h"

struct ordList {
    int maxSize; //tamanho máximo
    int size; //tamanho atual
    bool ord; //1 se a lista está ordenada, 0 se não
    void **data; //lista de apontadores para data
    unsigned long int *value; //lista de inteiros
};
//função que cria uma nova lista vazia com tamanho 1
OrdList *createOrdList() {
    OrdList *ordList = malloc(sizeof(OrdList));
    void **data = malloc(sizeof(void *));
    ordList->maxSize = 1;
    ordList->size = 0;
    ordList->data = data;
    ordList->value = NULL;
    ordList->ord = 0;

    return ordList;
}
//função que adiciona um novo elemento a uma lista
void addOrdList(OrdList *ordList, void *data) {
    int maxSize = ordList->maxSize;
    int size = ordList->size;
    if (size == maxSize) { //se a lista estiver cheia cria uma nova lista com o dobro do tamanho
        maxSize *= 2;
        void **newData = malloc(sizeof(void *) * maxSize);
        int i=0;
        while (i < size) {
            newData[i] = ordList->data[i];
            i++;
        }
        free(ordList->data);
        ordList->data = newData;
        ordList->maxSize = maxSize;
    }
    ordList->data[size] = data; //adiciona novo elemnto na última posição da lista
    ordList->size = size + 1; //incrementa numero de elementos na lista
    ordList->maxSize = maxSize;
}
//função que devolve o indice da primeira ocorrência de um elemento numa lista
int searchDataOrdList(OrdList *list, void *data, int (*compareFunction)(void*,void*,void*), void *lookup, int equal, int (*searchBackFunction)(void*,void*,void*)) {
    int lower = 0, higher = list->size - 1; //limites para procura
    if (higher == -1) return -2;
    int i = (higher + lower) / 2, compare; //indice central para comparar elementos
    void *compareData = list->data[i]; //elemento a comparar
    // caso a lista tenha apenas 1 elemento (logo se tiver algum igual, será apenas este)
    if (higher == lower) {
        if ((compare = compareFunction(data, compareData, lookup)) == equal) return i;
        else return -1;
    }
    // se tiver mais de 1 elemento
    //enquanto os elementos não forem iguais e os limites não se cruzarem
    while ((compare = compareFunction(data, compareData, lookup)) != equal && (higher - lower) > 1) {
        if (compare < equal) higher = i; //se o elemento for menor o limite superior passa a ser o indice do elemento
        else lower = i; //caso contrário o limite inferior passa a ser o indice do elemento
        i = (higher + lower) / 2; //novo indice central entre os dois limites
        compareData = list->data[i]; //novo elemento a comparar
    }
    if (higher - lower == 1 && compare != equal) {
        if (compare < equal) i = lower;
        else i = higher;
        compareData = list->data[i];
        if ((compare = compareFunction(data, compareData, lookup)) != equal) return -1;
    }
    while (i > 0 && compare <= equal) { //compara com o anterior até encontrar um elemento diferente
        compareData = list->data[i-1];
        compare = searchBackFunction(data, compareData, lookup);
        i--;
    }
    if (compare != equal && i != 0) i++; //quando a comparação não dá igual incrementa indice para apontar para o último elemento que deu igual

    return i; //retorna indice do elemento que se procurou na lista
}

//funções de ordenação
//radixsort ordena uma lista por valores que estejam num intervalo conhecido
//recebe uma função que devolve o valor do parametro para o qual queremos ordenar os elementos
void radixSort(OrdList *list, int (*getParameterFunction)(void*,void*), void *lookupTable, int interval, int offset) {
    int size = list->size;
    void **newData = malloc(sizeof(void *) * size); //cria nova lista que irá ficar ordenada
    void *data;
    int count[interval+1], i ,j; //array com de tamanho do intervalo de valores conhecido
    for (i=0; i<=interval; i++) count[i] = 0; //inicializa array a zero
    for (j=0; j<size; j++) {
        //conta ocorrencias de cada parametro no indice correspondente ao valor desse parametro
        data = list->data[j]; //obtem elemento da lista
        i = (*getParameterFunction)(data, lookupTable) - offset; //obtem valor do parametro a considerar desse elemento
        count[i] += 1; //incrementa a contagem desse valor no array
    }
    for (i=1; i<=interval; i++) count[i] += count[i-1]; //incrementa todas as posições com o valor da posição anterior
    for (j=size-1; j>=0; j--) { //começando no fim da lista e até chegar ao início
        data = list->data[j]; //obtem elemento da lista
        i = (*getParameterFunction)(data, lookupTable) - offset; //obtem o valor do parametro
        //introduz o elemento na nova lista na posição do numero de contagens do valor do parametro desse elemento menos um
        newData[count[i]-1] = data;
        count[i] -= 1; //decrementa o numero de contagens desse elemento
    }
    free(list->data);
    list->data = newData; //retorna uma nova lista ordenada pelo valor do parametro dado
}

//função que troca duas posições de uma lista
void swapOrdList(OrdList *list, int i, int j) {
    void *aux = list->data[i];
    list->data[i] = list->data[j];
    list->data[j] = aux;
}

//função bubbledown que faz trocas sucessivas de um elemento na heap com os filhos, até este se encontrar numa posição válida
void bubbledown(OrdList *list, int i, int size, int (*compareFunction)(void*,void*,void*), void *lookup, int equal) {
    int left = (2 * i) + 1, right = (2 * i) + 2;
    int max;
    void **data = list->data;
    while (left < size) {
        if (right < size && compareFunction(data[left], data[right], lookup) < 0) max = right;
        else max = left;
        if (compareFunction(data[i], data[max], lookup) < 0) {
            swapOrdList(list, i, max);
            i = max;
            left = (2 * i) + 1;
            right = (2 * i) + 2;
        }
        else break;
    }
}

//função heapsort que ordena um array fazendo uso de uma heap, começa por transformar o array
//numa heap e depois troca o elemento que se encontra em primeiro na heap com o último fazendo
//bubbledown deste, diminuindo o tamanho da heap e repetindo o processo até o array estar ordenado
void heapsort(OrdList *list, int (*compareFunction)(void*,void*,void*), void *lookup, int equal) {
    int size = list->size;
    int i;
    for (i=(size/2)-1; i>=0; i--) //transforma o array numa heap
        bubbledown(list, i, size, compareFunction, lookup, equal);
    for (i=size-1; i>=0; i--) {
        swapOrdList(list, 0, i); //troca o primeiro elemento com o útimo da heap
        bubbledown(list, 0, i, compareFunction, lookup, equal); //faz bubbledown desse elemento e decrementa o tamanho da heap
    }
}

//quicksort recebe uma lista os indices inferiores e superiores para ordenar uma função que compara
//dois elementos da lista e o valor que a função retorna caso os elementos sejam iguais
void quickSort(OrdList* list, int lower, int higher, int (*compareFunction)(void*,void*,void*), void *lookup, int equal) {
    if (lower < higher) { //se a sublista tiver apenas um elemento está ordenada
        int pivot = (lower + higher) / 2; //escolhe elemento central como pivô
        int i = lower;
        int j = higher;
        void **data = list->data;
        void *pivotData = data[pivot];
        while (i <= j) { //enquanto os indices não se cruzarem move elementos menores que o pivot para a esquerda e maiores para a direita deste
            while(compareFunction(data[i], pivotData, lookup) < equal) i++;
            while(compareFunction(data[j], pivotData, lookup) > equal) j--;
            if (i <= j) {
                swapOrdList(list, i, j);
                i++;
                j--;
            }
        }
        if (lower < j) quickSort(list, lower, j, compareFunction, lookup, equal); //chamada recursiva para a metade esquerda da sublista
        if (i < higher) quickSort(list, i, higher, compareFunction, lookup, equal); //chamada recursiva para a metade direita da sublista
    }
}

//gets
//função que devolve o elemento de uma lista dado um indice
void *getDataOrdList(OrdList *ordList, int index) {
    return ordList->data[index];
}
//função que devolve o numero de elementos na lista
int getOrdListSize(OrdList *ordList) {
    return ordList->size;
}
//função que verifica se uma lista está ordenada
bool isOrdered(OrdList *ordList) {
    return ordList->ord;
}
//função que altera um elemento da lista dado um indice
void setDataOrdList (OrdList *ordList, int index, void* data) {
    void *oldData = ordList->data[index];
    ordList->data[index] = data;
    free(oldData);
}
//função que altera o campo de uma lista que diz se ela está ou não ordenada
void setOrdListOrd (OrdList *ordList, bool ord) {
    ordList->ord = ord;
}

//função que liberta toda a memória alocada de uma lista
void destroyOrdList(OrdList *ordlist, void (*destroyDataFunction)(void*)) {
    if (ordlist == NULL) return;
    void **data = ordlist->data;
    int size = ordlist->size;
    for (int i=0; i<size; i++)
        (*destroyDataFunction)(data[i]);
    free(ordlist->data);
    free(ordlist);
}
//função que liberta apenas a memória alocada pela lista
void destroyOnlyOrdList(OrdList *list) {
    if (list == NULL) return;
    free(list->data);
    free(list);
}
//função que troca a posição de dois elementos de uma lista
void swap (OrdList *ordlist, int i, int j) {
    void* data_i = ordlist->data[i];
    ordlist->data[i] = ordlist->data[j];
    ordlist->data[j] = data_i;
}

//lista ordenada de inteiros
//função que cria uma nova lista vazia com um certo tamanho
OrdList *createOrdListInt() {
    OrdList *ordList = malloc(sizeof(OrdList));
    unsigned long int *value = malloc(sizeof(unsigned long int));
    ordList->maxSize = 1;
    ordList->size = 0;
    ordList->data = NULL;
    ordList->value = value;
    ordList->ord = 0;

    return ordList;
}
//função que adiciona um novo elemento a uma lista
void addOrdListInt(OrdList *ordList, unsigned long int value) {
    int maxSize = ordList->maxSize;
    int size = ordList->size;
    if (size == maxSize) { //se a lista estiver cheia cria uma nova lista com o dobro do tamanho
        maxSize *= 2;
        unsigned long int *newValue = malloc(sizeof(unsigned long int *) * maxSize);
        int i=0;
        while (i < size) {
            newValue[i] = ordList->value[i];
            i++;
        }
        free(ordList->value);
        ordList->value = newValue;
        ordList->maxSize = maxSize;
    }
    ordList->value[size] = value; //adiciona novo elemnto na última posição da lista
    ordList->size = size + 1; //incrementa numero de elementos na lista
    ordList->maxSize = maxSize;
}
//função que devolve o indice da primeira ocorrência de um elemento numa lista
int searchValueOrdList(OrdList *list, unsigned long int value, int (*compareFunction)(unsigned long int,unsigned long int,void*), void *lookup, int equal, int (*searchBackFunction)(unsigned long int,unsigned long int,void*), int first) {
    int lower = 0, higher = list->size - 1; //limites para procura
    if (higher == -1) return -2;
    int i = (higher + lower) / 2, compare; //indice central para comparar elementos
    unsigned long int compareValue = list->value[i]; //elemento a comparar
    while ((compare = compareFunction(value, compareValue, lookup)) != equal && (higher - lower) > 1) {
        if (compare < equal) higher = i; //se o elemento for menor o limite superior passa a ser o indice do elemento
        else lower = i; //caso contrário o limite inferior passa a ser o indice do elemento
        i = (higher + lower) / 2; //novo indice central entre os dois limites
        compareValue = list->value[i]; //novo elemento a comparar
    }
    if (first) return (lower + higher) / 2;
    if (higher - lower == 1 && compare != equal) return -1; //se o elemento nao existir na lista
    while (i > 0 && compare <= equal) { //compara com o anterior até encontrar um elemento diferente
        compareValue = list->value[i-1];
        compare = searchBackFunction(value, compareValue, lookup);
        i--;
    }
    if (compare != equal && i != 0) i++; //quando a comparação não dá igual incrementa indice para apontar para o último elemento que deu igual

    return i; //retorna indice do elemento que se procurou na lista
}

//radixsort ordena uma lista por valores que estejam num intervalo conhecido
//recebe uma função que devolve o valor do parametro para o qual queremos ordenar os elementos
void radixSortInt(OrdList *list, int (*getParameterFunction)(unsigned long int,void*), void *lookupTable, int interval, int offset) {
    int size = list->size;
    unsigned long int *newValue = malloc(sizeof(unsigned long int) * size); //cria nova lista que irá ficar ordenada
    unsigned long int value;
    int count[interval+1], i ,j; //array com de tamanho do intervalo de valores conhecido
    for (i=0; i<=interval; i++) count[i] = 0; //inicializa array a zero
    for (j=0; j<size; j++) {
        //conta ocorrencias de cada parametro no indice correspondente ao valor desse parametro
        value = list->value[j]; //obtem elemento da lista
        i = (*getParameterFunction)(value, lookupTable) - offset; //obtem valor do parametro a considerar desse elemento
        count[i] += 1; //incrementa a contagem desse valor no array
    }
    for (i=1; i<=interval; i++) count[i] += count[i-1]; //incrementa todas as posições com o valor da posição anterior
    for (j=size-1; j>=0; j--) { //começando no fim da lista e até chegar ao início
        value = list->value[j]; //obtem elemento da lista
        i = (*getParameterFunction)(value, lookupTable) - offset; //obtem o valor do parametro
        //introduz o elemento na nova lista na posição do numero de contagens do valor do parametro desse elemento menos um
        newValue[count[i]-1] = value;
        count[i] -= 1; //decrementa o numero de contagens desse elemento
    }
    free(list->value);
    list->value = newValue; //retorna uma nova lista ordenada pelo valor do parametro dado
}

//função que troca duas posições de uma lista
void swapOrdListInt(OrdList *list, int i, int j) {
    unsigned long int aux = list->value[i];
    list->value[i] = list->value[j];
    list->value[j] = aux;
}

//função bubbledown que faz trocas sucessivas de um elemento na heap com os filhos, até este se encontrar numa posição válida
void bubbledownInt(OrdList *list, int i, int size, int (*compareFunction)(unsigned long int,unsigned long int,void*), void *lookup, int equal) {
    int left = (2 * i) + 1, right = (2 * i) + 2;
    int max;
    unsigned long int *value = list->value;
    while (left < size) {
        if (right < size && compareFunction(value[left], value[right], lookup) < 0) max = right;
        else max = left;
        if (compareFunction(value[i], value[max], lookup) < 0) {
            swapOrdListInt(list, i, max);
            i = max;
            left = (2 * i) + 1;
            right = (2 * i) + 2;
        }
        else break;
    }
}

//função heapsort que ordena um array fazendo uso de uma heap, começa por transformar o array
//numa heap e depois troca o elemento que se encontra em primeiro na heap com o último fazendo
//bubbledown deste, diminuindo o tamanho da heap e repetindo o processo até o array estar ordenado
void heapsortInt(OrdList *list, int (*compareFunction)(unsigned long int,unsigned long int,void*), void *lookup, int equal) {
    int size = list->size;
    int i;
    for (i=(size/2)-1; i>=0; i--)
        bubbledownInt(list, i, size, compareFunction, lookup, equal);
    for (i=size-1; i>=0; i--) {
        swapOrdListInt(list, 0, i);
        bubbledownInt(list, 0, i, compareFunction, lookup, equal);
    }
}

//função que devolve o elemento de uma lista dado um indice
unsigned long int getValueOrdList(OrdList *ordList, int index) {
    return ordList->value[index];
}

//função que liberta toda a memória alocada de uma lista
void destroyOrdListInt(OrdList *ordlist) {
    if (ordlist == NULL) return;
    free(ordlist->value);
    free(ordlist);
}
