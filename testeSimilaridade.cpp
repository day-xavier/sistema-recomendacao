#include <vector>
#include <iostream>
#include "similaridade.h"
#include "listaCompras.h"

using namespace std;

int main() {

    ListaCompras lista;

    char caminho[] = "dados/dados/dados_venda_cluster_17.csv";

    if (lerDados(caminho, &lista) == 0) {
        return 1;
    }

    cout << "Numero de clientes: " << lista.codigoClientes.size() << endl;
    cout << "Numero de produtos: " << lista.produtos.size() << endl;

    int numClientes = lista.codigoClientes.size();
    float **matrizSimilaridade = calcularSimilaridade(lista);

    vector<int> testes = {0, 1, 2, 3};

    for (int clienteIndex : testes) {
        int clienteMaisSimilarIndex = clienteMaisSimilar(matrizSimilaridade, numClientes, clienteIndex);

        if (clienteMaisSimilarIndex != -1) {
            cout << "Cliente mais similar ao cliente " << lista.codigoClientes[clienteIndex] << ": " 
                      << lista.codigoClientes[clienteMaisSimilarIndex] << " (S = " << matrizSimilaridade[clienteIndex][clienteMaisSimilarIndex] << ")" << endl;
        } else {
            cout << "Cliente " << lista.codigoClientes[clienteIndex] << " nao possui clientes similares." << endl;
        }
    }

    liberarMatrizFloat(matrizSimilaridade, numClientes);

    return 0;
}