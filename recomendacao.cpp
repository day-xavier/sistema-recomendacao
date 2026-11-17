#include "recomendacao.h"
#include <stdlib.h>

int *analogos(double **matrizSimilaridade, int clientes, int indiceCliente, int *numAnalogos){
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

    for (int i = 0; i < lista->compras[indiceCliente].size(); i++) {
        int indiceproduto = lista->compras[indiceCliente][i];
        adquiridos[indiceproduto] = 1;
    }

    return adquiridos;
}