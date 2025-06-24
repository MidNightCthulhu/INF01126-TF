#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct {
    int vertice;
    float distancia;
} ItemHeap;

typedef struct {
    ItemHeap* dados;
    int* pos;
    int tamanho;
    int capacidade;
} MinHeap;

MinHeap* cria_heap(int capacidade);
void insere_heap(MinHeap* h, int vertice, float dist);
ItemHeap extrai_min(MinHeap* h);
void diminui_chave(MinHeap* h, int vertice, float nova_dist);
int esta_na_heap(MinHeap* h, int vertice);
void destroi_heap(MinHeap* h);

#endif // HEAP_H_INCLUDED
