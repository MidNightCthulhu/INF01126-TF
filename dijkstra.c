#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include "dijkstra.h"
#include "heap.h"

Dijkstra* dijkstra(Grafo* G, int origem) {
    int n = G->v;
    if (origem < 0 || origem >= n) return NULL;

    Dijkstra* d = malloc(sizeof(Dijkstra));
    d->distancias = malloc(n * sizeof(float));
    d->antecessores = malloc(n * sizeof(int));
    d->origem = origem;
    d->num_vertices = n;

    MinHeap* heap = cria_heap(n);

    for (int i = 0; i < n; i++) {
        d->distancias[i] = DBL_MAX;
        d->antecessores[i] = -1;
    }
    d->distancias[origem] = 0.0;

    for (int i = 0; i < n; i++) {
        if (i == origem)
            insere_heap(heap, i, 0.0);
        else
            insere_heap(heap, i, DBL_MAX);
    }

    while (heap->tamanho > 0) {
        int u = extrai_min(heap).vertice;

        for (int v = 0; v < n; v++) {
            float peso = G->mat[u][v];
            if (peso != -1.0 && esta_na_heap(heap, v)) {
                float nova = d->distancias[u] + peso;
                if (nova < d->distancias[v]) {
                    d->distancias[v] = nova;
                    d->antecessores[v] = u;
                    diminui_chave(heap, v, nova);
                }
            }
        }
    }

    destroi_heap(heap);
    return d;
}

int* dijkstra_reconstroi_caminho(Dijkstra* d, int destino, int* tam) {
    int* tmp = malloc(d->num_vertices * sizeof(int));
    int count = 0, atual = destino;

    while (atual != -1 && atual != d->origem) {
        tmp[count++] = atual;
        atual = d->antecessores[atual];
    }
    if (atual == -1) { free(tmp); *tam = 0; return NULL; }
    tmp[count++] = d->origem;

    int* caminho = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) caminho[i] = tmp[count - 1 - i];
    free(tmp);
    *tam = count;
    return caminho;
}

void dijkstra_imprime_caminho(Dijkstra* d, int destino) {
    if (destino == d->origem) {
        printf("Origem e destino são o mesmo vértice (%d).\n", d->origem);
        return;
    }

    int tam;
    int* caminho = dijkstra_reconstroi_caminho(d, destino, &tam);

    if (!caminho) {
        printf("Sem caminho de %d a %d.\n", d->origem, destino);
        return;
    }

    printf("Caminho de %d a %d (custo %.2f): ", d->origem, destino, d->distancias[destino]);
    for (int i = 0; i < tam; i++) {
        printf("%d", caminho[i]);
        if (i < tam - 1) printf(" -> ");
    }
    printf("\n");
    free(caminho);
}

void dijkstra_destroi(Dijkstra* d) {
    free(d->distancias);
    free(d->antecessores);
    free(d);
}
