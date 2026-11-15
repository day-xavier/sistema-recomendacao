#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <vector>
#include <map>
#include <string>

typedef struct{
    std::vector<std::string> codigoClientes;
    std::map<std::string, int> indiceClientes;

    std::vector<std::string> produtos;
    std::map<std::string, int> indiceProdutos;
        
    std::vector<std::vector<int>> compras;
} ListaCompras;

int lerDados(char *caminho, ListaCompras *lista);
void printarCompras(ListaCompras *lista, char *codCliente);

#endif