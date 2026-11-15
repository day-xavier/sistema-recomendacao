#include <stdio.h>
#include "listaCompras.h"

int main(int argc, char *argv[]) {

    if (argc < 5) {
        printf("Uso: %s <arquivo.csv> <cliente1> <cliente2> <cliente3>\n", argv[0]);
        return 1;
    }

    ListaCompras lista;
    if (lerDados(argv[1], &lista) == 0) {
        return 1;
    }

    printf("Base carregada: %d clientes e %d produtos\n\n",
           (int) lista.codigoClientes.size(), (int) lista.produtos.size());

    for (int i = 2; i < argc; i++) {
        printarCompras(&lista, argv[i]);
    }

    return 0;
}