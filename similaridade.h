#ifndef SIMILARIDADE_H 
#define SIMILARIDADE_H
#include "listaCompras.h"

typedef struct {
    int numLinhas;
    int numColunas;
    int naoNulos;
    float *valores;
    int *colunas;
    int *inicioLinhas;
} MatrizEsparsa;

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

int **calculoMatrizEficiente(int **matrizA, int linhasA, int colunasA, int colunasB);

float **calcularSimilaridadeEficiente(const ListaCompras& lista);

void printarSimilaridadeEficiente(ListaCompras *lista, char *codigos[]);

MatrizEsparsa montarComprasEsparsa(const ListaCompras& lista);

float produtoLinhas(const MatrizEsparsa& matriz, int i, int j);

MatrizEsparsa multiplicarTranspostaEsparsa(const MatrizEsparsa& matriz);

MatrizEsparsa calcularSimilaridadeEsparsa(const ListaCompras& lista);

int clienteMaisSimilarEsparsa(const MatrizEsparsa& similaridade, int clienteIndex);

void liberarMatrizEsparsa(MatrizEsparsa& matriz);

long long memoriaDensa(int numLinhas, int numColunas);

long long memoriaEsparsa(const MatrizEsparsa& matriz);

void printarComparacaoEsparsa(ListaCompras *lista, char *codigos[]);

#endif