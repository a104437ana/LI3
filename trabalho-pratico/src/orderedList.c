#include "orderedList.h"

struct ordList {
    int maxSize;
    int size;
    bool ord; //1 se a lista está ordenada, 0 se não
    void **data;
};
//função que cria uma nova lista vazia com um certo tamanho
OrdList *createOrdList() {
    OrdList *ordList = malloc(sizeof(OrdList));
    void **data = malloc(sizeof(void *));
    ordList->maxSize = 1;
    ordList->size = 0;
    ordList->data = data;
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
    //enquanto os elementos não forem iguais e os limites não se cruzarem
//    printf("Prefix: %s\n", (char*) data);

    // caso a lista tenha apenas 1 elemento (logo se tiver algum igual, será apenas este)
    if (higher == lower) {
        if ((compare = compareFunction(data, compareData, lookup)) == equal) return i;
        else return -1;
    }

    // se tiver mais de 1 elemento
    while ((compare = compareFunction(data, compareData, lookup)) != equal && (higher - lower) > 1) {
        if (compare < equal) higher = i; //se o elemento for menor o limite superior passa a ser o indice do elemento
        else lower = i; //caso contrário o limite inferior passa a ser o indice do elemento
        i = (higher + lower) / 2; //novo indice central entre os dois limites
        compareData = list->data[i]; //novo elemento a comparar
//        printf("\t%s\n", getName(compareData));
    }

    if (higher - lower == 1 && compare != equal) {
        if (compare < equal) {
            i = lower;
        }
        else {
            i = higher;
        }
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

void removeOrdList(OrdList *ordList, unsigned int key) {
}
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

//função de partição recebe uma lista os indices inferiores e superiores onde se pretende fazer uma partição
//um elemento pivô uma função que compara dois elementos da lista e o valor de retorno dessa função caso sejam iguais
int partitionOrdList(OrdList *list, int lower, int higher, void *pivotData, int (*compareFunction)(void*,void*,void*), void *lookup, int equal) {
    void *data = getDataOrdList(list, lower); //obtem o elemento do indice inferior da lista
    //enquanto os indices inferior e superior não se cruzarem
    while (higher > lower) {
        //enquanto o elemento do indice inferior for menor que o pivô
        while (compareFunction(data, pivotData, lookup) < equal) {
            lower++; //incrementa o indice inferior
            data = getDataOrdList(list, lower);
        }
        data = getDataOrdList(list, higher); //obtem o elemento do indice superior
        //enquanto o elemento do indice superior for maior ou igual que o pivô
        while (higher-1 >= lower && compareFunction(data, pivotData, lookup) > equal) {
            higher--; //decrementa o indice superior
            data = getDataOrdList(list, higher);
        }
        if (lower < higher) //caso os indices inferior e superior não se cruzaram
            swapOrdList(list, lower, higher); //troca a posição dos elementos
    }

    return lower; //devolve o indice onde os elementos são todos menores à esquerda e maiores à direita que o pivô
}
////quicksort recebe uma lista os indices inferiores e superiores para ordenar uma função que compara
////dois elementos da lista e o valor que a função retorna caso os elementos sejam iguais
//void quickSort(OrdList* list, int lower, int higher, int (*compareFunction)(void*,void*,void*), void *lookup, int equal) {
//    if (higher - lower > 1) { //se a sublista tiver apenas um elemento está ordenada
//        int pivot = (lower + higher) / 2; //escolhe elemento central como pivô
//        swapOrdList(list, pivot, higher); //move pivô para o fim da sublista
//        void *pivotData = getDataOrdList(list, higher); //obtem a data do pivô
//        //faz uma partição da sublista fazendo swaps até obter o indice para o qual
//        //todos os elementos da sublista à esquerda do indice são menores que o pivô e à direita maiores
//        int partition = partitionOrdList(list, lower, higher-1, pivotData, compareFunction, lookup, equal);
//        swapOrdList(list, partition, higher); //move pivô para a posição da partição
//        quickSort(list, lower, partition, compareFunction, lookup, equal); //chamada recursiva para a metade esquerda da sublista
//        quickSort(list, partition, higher, compareFunction, lookup, equal); //chamada recursiva para a metade direita da sublista
//    }
//}
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
//função que inverte a posição de todos os elementos de uma lista
void reverseOrdList(OrdList* list){
    int size = list->size;
    int i = 0;
    int j = size-1;
    while(i<j){
        swapOrdList(list, i, j);
        i++; j--;
    }
}

//void quickSortUserNames(OrdList *list) {
//    qSort(list->data, list->size, strcmp);
//}
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
//função que imprime todos os elementos de uma lista, para efeitos de teste
void printOrdList(OrdList *ordList, void (*printFunction)(void*)) {
    int size = ordList->size;
    void **data = ordList->data;
    for (int i=0; i<size; i++) {
        (*printFunction)(data[i]);
    }
    printf(")");
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
