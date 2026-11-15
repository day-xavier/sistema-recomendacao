#include "listaCompras.h"
#include <stdio.h>
#include <iostream>

int lerDados(char *caminho, ListaCompras *lista) {
    FILE *arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char data[9];
    char cliente[20];
    char produto[20];
    char nome[200];
  
    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %8[^,],%19[^,],%19[^,],%199[^\r\n]",
                  data, cliente, produto, nome) == 4) {

        std::string codCliente(cliente);
        std::string codProduto(produto);

        if (lista->indiceClientes.find(codCliente) == lista->indiceClientes.end()) {
            lista->indiceClientes[codCliente] = lista->codigoClientes.size();
            lista->codigoClientes.push_back(codCliente);
            lista->compras.push_back(std::vector<int>());
        }

        if (lista->indiceProdutos.find(codProduto) == lista->indiceProdutos.end()) {
            lista->indiceProdutos[codProduto] = lista->produtos.size();
            lista->produtos.push_back(nome);
        }
    }

    fclose(arquivo);

    arquivo = fopen(caminho, "r");
    if (arquivo == NULL) {
        printf("Erro ao reabrir o arquivo %s\n", caminho);
        return 0;
    }

    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %8[^,],%19[^,],%19[^,],%199[^\r\n]",
                  data, cliente, produto, nome) == 4) {

        int indiceC = lista->indiceClientes[std::string(cliente)];
        int indiceP = lista->indiceProdutos[std::string(produto)];

        int ha = 0;
        for (int i = 0; i < (int) lista->compras[indiceC].size(); i++) {
            if (lista->compras[indiceC][i] == indiceP) {
                ha = 1;
            }
        }
        if (ha == 0) {
            lista->compras[indiceC].push_back(indiceP);
        }
    }

    fclose(arquivo);
    return 1;
}

void printarCompras(ListaCompras *lista, char *codCliente) {
    std::string cod(codCliente);

    if (lista->indiceClientes.find(cod) == lista->indiceClientes.end()) {
        printf("Cliente %s nao encontrado\n\n", codCliente);
        return;
    }

    int indiceC = lista->indiceClientes[cod];

    printf("Produtos comprados pelo cliente %s:\n", codCliente);
    for (int i = 0; i < (int) lista->compras[indiceC].size(); i++) {
        int indiceP = lista->compras[indiceC][i];
        std::cout << "  - " << lista->produtos[indiceP] << "\n";
    }
    printf("\n");
}