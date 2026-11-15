#include <vector>
#include <iostream>
#include "similaridade.h"
#include "listaCompras.h"

int main() {

    ListaCompras lista;

    lerDados("dados/dados/dados_venda_cluster_17.csv", &lista);
    
    std::cout << "Numero de clientes: " << lista.codigoClientes.size() << std::endl;
    std::cout << "Numero de produtos: " << lista.produtos.size() << std::endl;

    std::vector<std::vector<double>> matrizSimilaridade;
    calcularSimilaridade(lista, matrizSimilaridade);

    std::vector<int> testes = {0, 1, 2, 3};

    for (int clienteIndex : testes) {
        int clienteMaisSimilarIndex = clienteMaisSimilar(matrizSimilaridade, clienteIndex);

        if (clienteMaisSimilarIndex != -1) {
            std::cout << "Cliente mais similar ao cliente " << lista.codigoClientes[clienteIndex] << ": " 
                      << lista.codigoClientes[clienteMaisSimilarIndex] << " (S = " << matrizSimilaridade[clienteIndex][clienteMaisSimilarIndex] << ")" << std::endl;
        } else {
            std::cout << "Cliente " << lista.codigoClientes[clienteIndex] << " nao possui clientes similares." << std::endl;
        }
    }

    return 0;
}
