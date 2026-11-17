#include <stdlib.h>
#include "similaridade.h"

using namespace std;

int **novaMatrizInt(int linhas, int colunas) {
    int **matriz = (int **) malloc(linhas * sizeof(int *));

    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int *) malloc(colunas * sizeof(int));

        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

float **novaMatrizFloat(int linhas, int colunas) {
    float **matriz = (float **) malloc(linhas * sizeof(float *));

    for (int i = 0; i < linhas; i++) {
        matriz[i] = (float *) malloc(colunas * sizeof(float));

        for (int j = 0; j < colunas; j++) {
            matriz[i][j] = 0.0;
        }
    }

    return matriz;
}

void liberarMatrizInt(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void liberarMatrizFloat(float **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int **montarMatrizCompras(const ListaCompras& lista) {
    int numClientes = lista.codigoClientes.size();
    int numProdutos = lista.produtos.size();

    int **matrizCompras = novaMatrizInt(numClientes, numProdutos);

    for (int i = 0; i < numClientes; i++) {
        for (int p: lista.compras[i]) {
            matrizCompras[i][p] = 1;
        }
    }

    return matrizCompras;
}

int **transposta(int **matriz, int linhas, int colunas) {
    int **matrizTransposta = novaMatrizInt(colunas, linhas);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            matrizTransposta[j][i] = matriz[i][j];
        }
    }

    return matrizTransposta;
}

int **multiplicar(int **matrizA, int **matrizB, int linhasA, int colunasA, int colunasB) {
    int **resultado = novaMatrizInt(linhasA, colunasB);

    for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
            for (int k = 0; k < colunasA; k++) {
                resultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }

    return resultado;
}

float **calcularSimilaridade(const ListaCompras& lista) {
    int numClientes = lista.codigoClientes.size();
    int numProdutos = lista.produtos.size();

    int **matrizCompras = montarMatrizCompras(lista);
    int **matrizTransposta = transposta(matrizCompras, numClientes, numProdutos);
    int **matrizProduto = multiplicar(matrizCompras, matrizTransposta, numClientes, numProdutos, numClientes);

    float **matrizSimilaridade = novaMatrizFloat(numClientes, numClientes);

    for (int i = 0; i < numClientes; i++) {
        for (int j = 0; j < numClientes; j++) {
            int intersecao = matrizProduto[i][j];
            int totalComprasI = matrizProduto[i][i];

            if (totalComprasI > 0) {
                matrizSimilaridade[i][j] = 1 - (float) intersecao / totalComprasI;
            } else {
                matrizSimilaridade[i][j] = 1.0;
            }
        }
    }

    liberarMatrizInt(matrizCompras, numClientes);
    liberarMatrizInt(matrizTransposta, numProdutos);
    liberarMatrizInt(matrizProduto, numClientes);

    return matrizSimilaridade;
}

int clienteMaisSimilar(float **matrizSimilaridade, int numClientes, int clienteIndex) {

    if (clienteIndex < 0 || clienteIndex >= numClientes) {
        return -1; 
    }

    float menorSimilaridade = 1.0;
    int clienteMaisSimilarIndex = -1;

    for (int j = 0; j < numClientes; j++) {
        if (j != clienteIndex && matrizSimilaridade[clienteIndex][j] < menorSimilaridade) {
            menorSimilaridade = matrizSimilaridade[clienteIndex][j];
            clienteMaisSimilarIndex = j;
        }
    }

    return clienteMaisSimilarIndex;
}