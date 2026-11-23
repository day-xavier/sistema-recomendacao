#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <algorithm>

#include "similaridade.h"

using namespace std;

double contagemTempo(clock_t inicio) {
    return double(clock() - inicio) / CLOCKS_PER_SEC;
}

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

void printarSimilaridade(ListaCompras *lista, char *codigos[]){

    cout << "Numero de clientes: " << lista->codigoClientes.size() << endl;
    cout << "Numero de produtos: " << lista->produtos.size() << endl;

    int numClientes = lista->codigoClientes.size();
    clock_t inicio = clock();
    float **matrizSimilaridade = calcularSimilaridade(*lista);
    cout << "Tempo: " << contagemTempo(inicio) << " s" << endl;

    for (int i = 0; codigos[i] != NULL; i++) {
        string codigo(codigos[i]);

        int clienteIndex = lista->indiceClientes[codigo];
        int clienteMaisSimilarIndex = clienteMaisSimilar(matrizSimilaridade, numClientes, clienteIndex);

        if (clienteMaisSimilarIndex != -1) {
            cout << "Cliente mais similar ao cliente " << lista->codigoClientes[clienteIndex] << ": "
                      << lista->codigoClientes[clienteMaisSimilarIndex] << " (S = " << matrizSimilaridade[clienteIndex][clienteMaisSimilarIndex] << ")" << endl;
        } else {
            cout << "Cliente " << lista->codigoClientes[clienteIndex] << " nao possui clientes similares." << endl;
        }
    }

    liberarMatrizFloat(matrizSimilaridade, numClientes);
}

int **calculoMatrizEficiente(int **matrizA, int linhasA, int colunasA){
    int **matrizEficaz = novaMatrizInt(linhasA, linhasA);

    for (int i = 0; i < linhasA; i++) {
        for (int j = i; j < linhasA; j++) {
            int soma = 0;

            for (int k = 0; k < colunasA; k++) {
                soma += matrizA[i][k] * matrizA[j][k];
            }

            matrizEficaz[i][j] = soma;
            matrizEficaz[j][i] = soma;
        }
    }

    return matrizEficaz;
}

float **calcularSimilaridadeEficiente(const ListaCompras& lista) {
    int numClientes = lista.codigoClientes.size();
    int numProdutos = lista.produtos.size();

    int **matrizCompras = montarMatrizCompras(lista);
    int **matrizProduto = calculoMatrizEficiente(matrizCompras, numClientes, numProdutos);

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
    liberarMatrizInt(matrizProduto, numClientes);

    return matrizSimilaridade;
}

void printarSimilaridadeEficiente(ListaCompras *lista, char *codigos[]){

    cout << "Numero de clientes: " << lista->codigoClientes.size() << endl;
    cout << "Numero de produtos: " << lista->produtos.size() << endl;

    int numClientes = lista->codigoClientes.size();
    clock_t inicio = clock();
    float **matrizSimilaridade = calcularSimilaridadeEficiente(*lista);
    cout << "Tempo: " << contagemTempo(inicio) << " s" << endl;

    for (int i = 0; codigos[i] != NULL; i++) {
        string codigo(codigos[i]);

        int clienteIndex = lista->indiceClientes[codigo];
        int clienteMaisSimilarIndex = clienteMaisSimilar(matrizSimilaridade, numClientes, clienteIndex);

        if (clienteMaisSimilarIndex != -1) {
            cout << "Cliente mais similar ao cliente " << lista->codigoClientes[clienteIndex] << ": "
                      << lista->codigoClientes[clienteMaisSimilarIndex] << " (S = " << matrizSimilaridade[clienteIndex][clienteMaisSimilarIndex] << ")" << endl;
        } else {
            cout << "Cliente " << lista->codigoClientes[clienteIndex] << " nao possui clientes similares." << endl;
        }
    }

    liberarMatrizFloat(matrizSimilaridade, numClientes);
}

MatrizEsparsa montarComprasEsparsa(const ListaCompras& lista) {
    MatrizEsparsa matrizEsparsa;
    matrizEsparsa.numLinhas = lista.codigoClientes.size();
    matrizEsparsa.numColunas = lista.produtos.size();
    matrizEsparsa.naoNulos = 0;

    for (int i = 0; i < matrizEsparsa.numLinhas; i++) {
        matrizEsparsa.naoNulos += (int)lista.compras[i].size();
    }

    matrizEsparsa.values = (float *) malloc(matrizEsparsa.naoNulos * sizeof(float));
    matrizEsparsa.col_index = (int *) malloc(matrizEsparsa.naoNulos * sizeof(int));
    matrizEsparsa.row_ptr = (int *) malloc((matrizEsparsa.numLinhas + 1) * sizeof(int));

    int indiceNaoNulo = 0;
    for (int i = 0; i < matrizEsparsa.numLinhas; i++) {
        matrizEsparsa.row_ptr[i] = indiceNaoNulo;
        for (int p: lista.compras[i]) {
            matrizEsparsa.values[indiceNaoNulo] = 1; 
            matrizEsparsa.col_index[indiceNaoNulo] = p; 
            indiceNaoNulo++;
        }
    }

    matrizEsparsa.row_ptr[matrizEsparsa.numLinhas] = indiceNaoNulo;

    for (int i = 0; i < matrizEsparsa.numLinhas; i++) {
        std::sort(&matrizEsparsa.col_index[matrizEsparsa.row_ptr[i]], &matrizEsparsa.col_index[matrizEsparsa.row_ptr[i + 1]]);
    }

    return matrizEsparsa;
}

float produtoLinhas(const MatrizEsparsa& matriz, int i, int j) {
    float soma = 0.0;

    int inicioI = matriz.row_ptr[i];
    int fimI = matriz.row_ptr[i + 1];
    int inicioJ = matriz.row_ptr[j];
    int fimJ = matriz.row_ptr[j + 1];

    int indiceI = inicioI;
    int indiceJ = inicioJ;

    while (indiceI < fimI && indiceJ < fimJ) {
        if (matriz.col_index[indiceI] == matriz.col_index[indiceJ]) {
            soma += matriz.values[indiceI] * matriz.values[indiceJ];
            indiceI++;
            indiceJ++;
        } else if (matriz.col_index[indiceI] < matriz.col_index[indiceJ]) {
            indiceI++;
        } else {
            indiceJ++;
        }
    }

    return soma;
}

MatrizEsparsa multiplicarTranspostaEsparsa(const MatrizEsparsa& matriz) {
    MatrizEsparsa resultado;
    resultado.numLinhas = matriz.numLinhas;
    resultado.numColunas = matriz.numLinhas; 
    resultado.naoNulos = 0;

    for (int i = 0; i < matriz.numLinhas; i++) {
        for (int j = 0; j < matriz.numLinhas; j++) {
            float produto = produtoLinhas(matriz, i, j);
            if (produto != 0) {
                resultado.naoNulos++;
            }
        }
    }

    resultado.values = (float *) malloc(resultado.naoNulos * sizeof(float));
    resultado.col_index = (int *) malloc(resultado.naoNulos * sizeof(int));
    resultado.row_ptr = (int *) malloc((resultado.numLinhas + 1) * sizeof(int));

    int indiceNaoNulo = 0;
    for (int i = 0; i < matriz.numLinhas; i++) {
        resultado.row_ptr[i] = indiceNaoNulo;
        for (int j = 0; j < matriz.numLinhas; j++) {
            float produto = produtoLinhas(matriz, i, j);
            if (produto != 0) {
                resultado.values[indiceNaoNulo] = produto;
                resultado.col_index[indiceNaoNulo] = j;
                indiceNaoNulo++;
            }
        }
    }
    resultado.row_ptr[resultado.numLinhas] = indiceNaoNulo;

    return resultado;
}

MatrizEsparsa calcularSimilaridadeEsparsa(const ListaCompras& lista) {
    MatrizEsparsa comprasEsparsa = montarComprasEsparsa(lista);
    MatrizEsparsa similaridadeEsparsa = multiplicarTranspostaEsparsa(comprasEsparsa);

    for (int i = 0; i < similaridadeEsparsa.numLinhas; i++) {
        float totalComprasI = produtoLinhas(comprasEsparsa, i, i);
        for (int idx = similaridadeEsparsa.row_ptr[i]; idx < similaridadeEsparsa.row_ptr[i + 1]; idx++) {
            float intersecao = similaridadeEsparsa.values[idx];
            
            if (totalComprasI > 0) {
                similaridadeEsparsa.values[idx] = 1 - intersecao / totalComprasI;
            } else {
                similaridadeEsparsa.values[idx] = 1.0;
            }
        }
    }

    free(comprasEsparsa.values);
    free(comprasEsparsa.col_index);
    free(comprasEsparsa.row_ptr);

    return similaridadeEsparsa;
}

int clienteMaisSimilarEsparsa(const MatrizEsparsa& similaridade, int clienteIndex) {
    if (clienteIndex < 0 || clienteIndex >= similaridade.numLinhas) {
        return -1; 
    }

    float menorSimilaridade = 1.0;
    int clienteMaisSimilarIndex = -1;

    int inicio = similaridade.row_ptr[clienteIndex];
    int fim = similaridade.row_ptr[clienteIndex + 1];

    for (int idx = inicio; idx < fim; idx++) {
        int j = similaridade.col_index[idx];
        float valorSimilaridade = similaridade.values[idx];

        if (j != clienteIndex && valorSimilaridade < menorSimilaridade) {
            menorSimilaridade = valorSimilaridade;
            clienteMaisSimilarIndex = j;
        }
    }

    return clienteMaisSimilarIndex;
}

void liberarMatrizEsparsa(MatrizEsparsa& matriz) {
    free(matriz.values);
    free(matriz.col_index);
    free(matriz.row_ptr);
    matriz.values = NULL;
    matriz.col_index = NULL;
    matriz.row_ptr = NULL;
    matriz.numLinhas = 0;
    matriz.numColunas = 0;
    matriz.naoNulos = 0;
}

double memoriaDensa(int numLinhas, int numColunas) {
        return (double) numLinhas * numColunas * sizeof(float) +
        (double) numLinhas * sizeof(float *);
}

double memoriaEsparsa(const MatrizEsparsa& matriz) {
        return (double) matriz.naoNulos * sizeof(float) +
        (double) matriz.naoNulos * sizeof(int) +
        (double) (matriz.numLinhas + 1) * sizeof(int);
}

void printarComparacaoEsparsa(ListaCompras *lista, char *codigos[]){
    cout << "Numero de clientes: " << lista->codigoClientes.size() << endl;
    cout << "Numero de produtos: " << lista->produtos.size() << endl;

    int numClientes = lista->codigoClientes.size();
    clock_t inicioDensa = clock();
    float **matrizDensa = calcularSimilaridadeEficiente(*lista);
    cout << "Tempo (densa): " << contagemTempo(inicioDensa) << " s" << endl;
    clock_t inicioEsparsa = clock();
    MatrizEsparsa matrizSimilaridadeEsparsa = calcularSimilaridadeEsparsa(*lista);
    cout << "Tempo (esparsa): " << contagemTempo(inicioEsparsa) << " s" << endl;

    double memoriaDensaBytes = memoriaDensa(numClientes, numClientes);
    double memoriaEsparsaBytes = memoriaEsparsa(matrizSimilaridadeEsparsa);

    cout << "Memoria (densa): " << memoriaDensaBytes / (1024.0 * 1024.0) << " MB" << endl;
    cout << "Memoria (esparsa): " << memoriaEsparsaBytes / (1024.0 * 1024.0) << " MB" << endl;

    for (int i = 0; codigos[i] != NULL; i++) {
        string codigo(codigos[i]);
        
        if (lista->indiceClientes.find(codigo) == lista->indiceClientes.end()) {
            cout << "Cliente " << codigo << " nao encontrado." << endl;
            continue;
        }

        int clienteIndex = lista->indiceClientes[codigo];
        int clienteMaisSimilarIndexDensa = clienteMaisSimilar(matrizDensa, numClientes, clienteIndex);
        int clienteMaisSimilarIndexEsparsa = clienteMaisSimilarEsparsa(matrizSimilaridadeEsparsa, clienteIndex);

        cout << "Cliente: " << lista->codigoClientes[clienteIndex] << endl;
        if (clienteMaisSimilarIndexDensa != -1) {
            cout << "  Mais similar (densa): " << lista->codigoClientes[clienteMaisSimilarIndexDensa]
                      << " (S = " << matrizDensa[clienteIndex][clienteMaisSimilarIndexDensa] << ")" << endl;
        } else {
            cout << "  Mais similar (densa): Nenhum" << endl;
        }

        if (clienteMaisSimilarIndexEsparsa != -1) {
            float valorSimilaridadeEsparsa = 0.0;
            for (int idx = matrizSimilaridadeEsparsa.row_ptr[clienteIndex]; idx < matrizSimilaridadeEsparsa.row_ptr[clienteIndex + 1]; idx++) {
                if (matrizSimilaridadeEsparsa.col_index[idx] == clienteMaisSimilarIndexEsparsa) {
                    valorSimilaridadeEsparsa = matrizSimilaridadeEsparsa.values[idx];
                    break;
                }
            }
            cout << "  Mais similar (esparsa): " << lista->codigoClientes[clienteMaisSimilarIndexEsparsa]
                      << " (S = " << valorSimilaridadeEsparsa << ")" << endl;
        } else {
            cout << "  Mais similar (esparsa): Nenhum" << endl;
        }
    }

    liberarMatrizFloat(matrizDensa, numClientes);
    liberarMatrizEsparsa(matrizSimilaridadeEsparsa);
}