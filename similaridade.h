#ifndef SIMILARIDADE_H 
#define SIMILARIDADE_H
#include "listaCompras.h"

int **alocarMatrizInt(int linhas, int colunas);

double **alocarMatrizDouble(int linhas, int colunas);

void liberarMatrizInt(int **matriz, int linhas);

void liberarMatrizDouble(double **matriz, int linhas);

int **montarMatrizCompras(const ListaCompras& lista);

int **transposta(int **matriz, int linhas, int colunas);

int **multiplicar(int **matrizA, int **matrizB, int linhasA, int colunasA, int colunasB);

double **calcularSimilaridade(const ListaCompras& lista);

int clienteMaisSimilar(double **matrizSimilaridade, int numClientes, int clienteIndex);

#endif