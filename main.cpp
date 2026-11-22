#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Uso:\n");
        printf("  %s 1 <arquivo.csv> <cliente1> [cliente2 ...]      (compras)\n", argv[0]);
        printf("  %s 2 <arquivo.csv> <cliente1> [cliente2 ...]      (similaridade)\n", argv[0]);
        printf("  %s 3 <arquivo.csv> <k> <cliente1> [cliente2 ...]  (recomendacoes)\n", argv[0]);
        return 1;
    }

    int escolha = atoi(argv[1]);

    ListaCompras lista;
    if (lerDados(argv[2], &lista) == 0) {
        return 1;
    }


    switch (escolha){
    case 1:
        for (int i = 3; i < argc; i++) {
            printarCompras(&lista, argv[i]);
        }
        break;

    case 2:
    printarSimilaridade(&lista, &argv[3]);
        break;

    case 3:
    printarRecomendacoes(&lista, atoi(argv[3]), &argv[4]);
        break;
    }


    return 0;
}