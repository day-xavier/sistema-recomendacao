#include "listaCompras.h"
#include <stdio.h>
#include <algorithm>

void lerDados(std::string caminho, ListaCompras* lista) {
    FILE *arquivo = fopen(caminho.c_str(), "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
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
        }

        if (lista->indiceProdutos.find(codProduto) == lista->indiceProdutos.end()) {
            lista->indiceProdutos[codProduto] = lista->produtos.size();
            lista->produtos.push_back(nome);
        }
    }

    lista->compras.resize(lista->codigoClientes.size());

    rewind(arquivo);
    fscanf(arquivo, "%*[^\n]");

    while (fscanf(arquivo, " %8[^,],%19[^,],%19[^,],%199[^\r\n]",
                  data, cliente, produto, nome) == 4) {

        int indiceC = lista->indiceClientes[std::string(cliente)];
        int indiceP = lista->indiceProdutos[std::string(produto)];

        if (std::find(lista->compras[indiceC].begin(), lista->compras[indiceC].end(), indiceP)
            == lista->compras[indiceC].end()) {
            lista->compras[indiceC].push_back(indiceP);
        }
    }

    fclose(arquivo);
}