#include <stdlib.h>
#include "heap.h"

static void troca(ItemHeap* a, ItemHeap* b) {
    ItemHeap tmp = *a; *a = *b; *b = tmp;
}

static void heapify_subir(MinHeap* h, int i) {
    while (i > 0 && h->dados[i].distancia < h->dados[(i-1)/2].distancia) {
        int pai = (i-1)/2;
        h->pos[h->dados[i].vertice] = pai;
        h->pos[h->dados[pai].vertice] = i;
        troca(&h->dados[i], &h->dados[pai]);
        i = pai;
    }
}

static void heapify_descer(MinHeap* h, int i) {
    int menor = i, esq = 2*i+1, dir = 2*i+2;
    if (esq < h->tamanho && h->dados[esq].distancia < h->dados[menor].distancia) menor = esq;
    if (dir < h->tamanho && h->dados[dir].distancia < h->dados[menor].distancia) menor = dir;
    if (menor != i) {
        h->pos[h->dados[i].vertice] = menor;
        h->pos[h->dados[menor].vertice] = i;
        troca(&h->dados[i], &h->dados[menor]);
        heapify_descer(h, menor);
    }
}

MinHeap* cria_heap(int capacidade) {
    MinHeap* h = malloc(sizeof(MinHeap));
    h->dados = malloc(capacidade * sizeof(ItemHeap));
    h->pos = malloc(capacidade * sizeof(int));
    h->tamanho = 0;
    h->capacidade = capacidade;
    for (int i = 0; i < capacidade; i++) h->pos[i] = -1;
    return h;
}

void insere_heap(MinHeap* h, int vertice, float dist) {
    int i = h->tamanho++;
    h->dados[i].vertice = vertice;
    h->dados[i].distancia = dist;
    h->pos[vertice] = i;
    heapify_subir(h, i);
}

ItemHeap extrai_min(MinHeap* h) {
    ItemHeap min = h->dados[0];
    h->dados[0] = h->dados[--h->tamanho];
    h->pos[h->dados[0].vertice] = 0;
    h->pos[min.vertice] = -1;
    heapify_descer(h, 0);
    return min;
}

void diminui_chave(MinHeap* h, int v, float nova) {
    int i = h->pos[v];
    h->dados[i].distancia = nova;
    heapify_subir(h, i);
}

int esta_na_heap(MinHeap* h, int v) {
    return h->pos[v] != -1;
}

void destroi_heap(MinHeap* h) {
    free(h->dados);
    free(h->pos);
    free(h);
}
