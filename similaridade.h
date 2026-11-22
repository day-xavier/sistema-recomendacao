#ifndef SIMILARIDADE_H 
#define SIMILARIDADE_H
#include "listaCompras.h"

int **novaMatrizInt(int linhas, int colunas);

float **novaMatrizFloat(int linhas, int colunas);

void liberarMatrizInt(int **matriz, int linhas);

void liberarMatrizFloat(float **matriz, int linhas);

int **montarMatrizCompras(const ListaCompras& lista);

int **transposta(int **matriz, int linhas, int colunas);

int **multiplicar(int **matrizA, int **matrizB, int linhasA, int colunasA, int colunasB);

float **calcularSimilaridade(const ListaCompras& lista);

int clienteMaisSimilar(float **matrizSimilaridade, int numClientes, int clienteIndex);

void printarSimilaridade(ListaCompras *lista, char *codigos[]);

#endif