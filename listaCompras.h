#ifndef LISTACOMPRAS_H
#define LISTACOMPRAS_H

#include <vector>
#include <map>
#include <string>

struct ListaCompras{
    std::vector<std::string> codigoClientes;
    std::map<std::string, int> indiceClientes;
    std::vector<std::string> produtos;
    std::map<std::string, int> indiceProdutos;
    std::vector<std::vector<int>> compras;
};

void lerDados(std::string caminho, ListaCompras* lista);

#endif