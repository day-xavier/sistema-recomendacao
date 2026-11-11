#ifndef LISTACOMPRAS.H

#include <vector>
#include <map>
#include <list>
#include <string>

extern std::vector<int> clientes;
extern std::map<int, int> indiceClientes;
extern std::vector<std::string> produtos;
extern std::map<std::string, int> indiceProdutos;
extern std::vector<std::list<int>> compras;

void lerCSV(std::string caminho);

void adicionarCompra(std::string codigoCliente,
                     std::string codigoProduto,
                     std::string nomeProduto);

void exibirCompras(std:: string codigoCliente);

#endif