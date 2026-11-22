#include "recomendacao.h"

#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int *analogos(float **matrizSimilaridade, int clientes, int indiceCliente, int *numAnalogos){
    int *vetorAnalogos = (int *) malloc(clientes* sizeof(int));

    int contador = 0;
    for (int i=0; i<clientes; i++){
        if (i !=indiceCliente && matrizSimilaridade[indiceCliente][i] < 1){
            vetorAnalogos[contador] = i;
            contador += 1;
        }
    }

    *numAnalogos = contador;
    return vetorAnalogos;
}

int *jaAdquiridos(ListaCompras *lista, int indiceCliente){
    int qtdProdutos = lista->produtos.size();

    int *adquiridos = (int *) malloc(qtdProdutos * sizeof(int));

    for (int i = 0; i < qtdProdutos; i++) {
        adquiridos[i] = 0;
    }

    for (int i = 0; i < (int) lista->compras[indiceCliente].size(); i++) {
        int indiceproduto = lista->compras[indiceCliente][i];
        adquiridos[indiceproduto] = 1;
    }

    return adquiridos;
}

Ranking *criarRank(int numProd){
    Ranking *rank = (Ranking *) malloc(numProd * sizeof(Ranking));

    for (int i = 0; i < numProd; i++) {
        rank[i].produto = i;
        rank[i].rank = 1.0;
    }

    return rank;
}

void atualizarRank(ListaCompras *lista, float **matrizSimilaridade, int indiceCliente, int *vetorAnalogos, int numAnalogos, int *vetorAdquiridos, Ranking *rank){
    for (int i = 0; i < numAnalogos; i++) {
        int vizinho = vetorAnalogos[i];
        float similaridade = matrizSimilaridade[indiceCliente][vizinho];

        for (int j = 0; j < (int)lista->compras[vizinho].size(); j++) {
            int produto = lista->compras[vizinho][j];

            if (vetorAdquiridos[produto] == 0) {
                rank[produto].rank *= similaridade;
            }
        }
    }
}

bool compararRank(const Ranking &a, const Ranking &b) {
    return a.rank < b.rank;
}

Ranking *ordenarRank(Ranking *rank, int tamanho, int k, int *vetorAdquiridos, int *candidatos){
    std::sort(rank, rank + tamanho, compararRank);

    int count = 0;
    for (int i = 0; i < tamanho && count < k && rank[i].rank < 1.0; i++) {
        if (vetorAdquiridos[rank[i].produto] == 0) {
            count++;
        }
    }

    *candidatos = count;

    return rank;
}

int *recomendar(ListaCompras *lista, float **matrizSimilaridade, int indiceCliente, int k, int *tamanho){
    int numClientes = lista->codigoClientes.size();
    int numProdutos = lista->produtos.size();

    int *vetorAnalogos;
    int numAnalogos;
    vetorAnalogos = analogos(matrizSimilaridade, numClientes, indiceCliente, &numAnalogos);

    int *vetorAdquiridos = jaAdquiridos(lista, indiceCliente);

    Ranking *rank = criarRank(numProdutos);
    atualizarRank(lista, matrizSimilaridade, indiceCliente, vetorAnalogos, numAnalogos, vetorAdquiridos, rank);

    int candidatos;
    rank = ordenarRank(rank, numProdutos, k, vetorAdquiridos, &candidatos);

    int *recomendacoes = (int *) malloc(candidatos * sizeof(int));
    for (int i = 0; i < candidatos; i++) {
        recomendacoes[i] = rank[i].produto;
    }

    free(vetorAnalogos);
    free(vetorAdquiridos);
    free(rank);

    *tamanho = candidatos;
    return recomendacoes;
}

void printarRecomendacoes(ListaCompras *lista, int k, char *codigos[]) {

    cout << "Numero de clientes: " << lista->codigoClientes.size() << endl;
    cout << "Numero de produtos: " << lista->produtos.size() << endl;

    int numClientes = lista->codigoClientes.size();
    float **matrizSimilaridade = calcularSimilaridade(*lista);

    for (int j = 0; codigos[j] != NULL; j++) {
        string codigo(codigos[j]);

        if (lista->indiceClientes.find(codigo) != lista->indiceClientes.end()) {
            int indiceCliente = lista->indiceClientes[codigo];
            int tamanho = 0;
            int *recomendacoes = recomendar(lista, matrizSimilaridade, indiceCliente, k, &tamanho);

            cout << "Recomendacoes para o cliente " << codigo << ":" << endl;
            for (int i = 0; i < tamanho; i++) {
                cout << "  " << (i + 1) << ". " << lista->produtos[recomendacoes[i]] << endl;
            }
            cout << endl;

            if (tamanho == 0) {
                cout << "Nenhuma recomendacao disponivel para o cliente " << codigo << "." << endl;
            }

            free(recomendacoes);
        } else {
            cout << "Cliente com codigo " << codigo << " nao encontrado." << endl;
        }
    }

    liberarMatrizFloat(matrizSimilaridade, numClientes);
}