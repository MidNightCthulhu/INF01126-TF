#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED

#include "grafo.h"

typedef struct {
    int* antecessores;
    float* distancias;
    int origem;
    int num_vertices;
} Dijkstra;

Dijkstra* dijkstra(Grafo* G, int origem);
int* dijkstra_reconstroi_caminho(Dijkstra* d, int destino, int* tamanho);
void dijkstra_imprime_caminho(Dijkstra* d, int destino);
void dijkstra_destroi(Dijkstra* d);

#endif // DIJKSTRA_H_INCLUDED
