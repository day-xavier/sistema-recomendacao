#include <iostream>
#include <vector>
#include <string>
#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"

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
    
    int k = 3;

    vector<string> codigos = {"19689801", "33653401", "YZ0TYR01"};

    for (string codigo : codigos) {
        if (lista.indiceClientes.find(codigo) != lista.indiceClientes.end()) {
            int indiceCliente = lista.indiceClientes[codigo];
            int tamanho = 0;
            int *recomendacoes = recomendar(&lista, matrizSimilaridade, indiceCliente, k, &tamanho);

            cout << "Recomendacoes para o cliente " << codigo << ":" << endl;
            for (int i = 0; i < tamanho; i++) {
                cout << "  " << (i + 1) << ". " << lista.produtos[recomendacoes[i]] << endl;
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

    return 0;
}