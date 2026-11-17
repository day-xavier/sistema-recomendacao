#ifndef RECOMENDACAO_H
#define RECOMENDACAO_H

#include "similaridade.h"
#include "listaCompras.h"

typedef struct {
    int produto; 
    float rank;
} Ranking;

int *analogos(float **matrizSimilaridade, int clientes, int indiceCliente, int *numAnalogos);
int *jaAdquiridos(ListaCompras *lista, int indiceCliente);
Ranking *criarRank(int numProd);
void atualizarRank(ListaCompras *lista, float **matrizSimilaridade, int indiceCliente, int *vetorAnalogos, int numAnalogos, int *vetorAdquiridos, Ranking *rank);
Ranking *ordenarRank(Ranking *rank, int tamanho, int k, int *vetorAdquiridos, int *candidatos);
int *recomendar(ListaCompras *lista, float **matrizSimilaridade, int indiceCliente, int k, int *tamanho);

#endif