#include "similaridade.h"

void montarMatrizCompras(const ListaCompras& lista, std::vector<std::vector<int>>& matrizCompras) {
    int numClientes = lista.codigoClientes.size();
    int numProdutos = lista.produtos.size();
    matrizCompras.assign(numClientes, std::vector<int>(numProdutos, 0));

    for (int i = 0; i < numClientes; ++i) {
        for (int p: lista.compras[i]) {
            matrizCompras[i][p] = 1;
        }
    }
}

void transposta(const std::vector<std::vector<int>>& matriz, std::vector<std::vector<int>>& matrizTransposta) {
    int linhas = matriz.size();

    if (linhas == 0) {
        matrizTransposta.clear();
        return;
    }

    int colunas = matriz[0].size();
    matrizTransposta.assign(colunas, std::vector<int>(linhas, 0));

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            matrizTransposta[j][i] = matriz[i][j];
        }
    }
}

void multiplicar(const std::vector<std::vector<int>>& matrizA, const std::vector<std::vector<int>>& matrizB, std::vector<std::vector<int>>& resultado) {
    int linhasA = matrizA.size();
    int linhasB = matrizB.size();

    if (linhasA == 0 || linhasB == 0) {
        resultado.clear();
        return;
    }

    int colunasA = matrizA[0].size();
    int colunasB = matrizB[0].size();

    if (colunasA != linhasB) {
        resultado.clear();
        return;
    }

    resultado.assign(linhasA, std::vector<int>(colunasB, 0));

    for (int i = 0; i < linhasA; ++i) {
        for (int j = 0; j < colunasB; ++j) {
            for (int k = 0; k < colunasA; ++k) {
                resultado[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
}

void calcularSimilaridade(const ListaCompras& lista, std::vector<std::vector<double>>& matrizSimilaridade) {
    std::vector<std::vector<int>> matrizCompras;
    montarMatrizCompras(lista, matrizCompras);

    std::vector<std::vector<int>> matrizTransposta;
    transposta(matrizCompras, matrizTransposta);

    std::vector<std::vector<int>> produtoInterno;
    multiplicar(matrizCompras, matrizTransposta, produtoInterno);

    int numClientes = lista.codigoClientes.size();
    matrizSimilaridade.assign(numClientes, std::vector<double>(numClientes, 0.0));

    for (int i = 0; i < numClientes; ++i) {
        for (int j = 0; j < numClientes; ++j) {

            int intersecao = produtoInterno[i][j];
            int totalComprasI = produtoInterno[i][i];
            

            if (totalComprasI > 0) {
                matrizSimilaridade[i][j] = 1 - (double)intersecao / totalComprasI;
            } else {
                matrizSimilaridade[i][j] = 1.0;
            }
        }
    }
}

int clienteMaisSimilar(const std::vector<std::vector<double>>& matrizSimilaridade, int clienteIndex) {
    int numClientes = matrizSimilaridade.size();
    if (clienteIndex < 0 || clienteIndex >= numClientes) {
        return -1;
    }

    double menorSimilaridade = 1.0;
    int clienteMaisSimilarIndex = -1;

    for (int j = 0; j < numClientes; ++j) {
        if (j != clienteIndex && matrizSimilaridade[clienteIndex][j] < menorSimilaridade) {
            menorSimilaridade = matrizSimilaridade[clienteIndex][j];
            clienteMaisSimilarIndex = j;
        }
    }

    return clienteMaisSimilarIndex;
}