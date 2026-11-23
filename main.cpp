#include "listaCompras.h"
#include "similaridade.h"
#include "recomendacao.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Uso:\n");
        printf("  %s 1 <arquivo.csv> <cliente1> [cliente2 ...]      (compras)\n", argv[0]);
        printf("  %s 2 <arquivo.csv> <cliente1> [cliente2 ...]      (similaridade padrão)\n", argv[0]);
        printf("  %s 3 <arquivo.csv> <cliente1> [cliente2 ...]      (similaridade eficiente)\n", argv[0]);
        printf("  %s 4 <arquivo.csv> <k> <cliente1> [cliente2 ...]  (recomendacoes)\n", argv[0]);
        printf("  %s 5 <qtdArquivos> <arquivo1.csv> ... <cliente1> [cliente2 ...]  (densa x esparsa)\n", argv[0]);
        return 1;
    }

    int escolha = atoi(argv[1]);
    if (escolha == 5) {
        int qtdArquivos = atoi(argv[2]);
        if (argc < 3 + qtdArquivos) {
            printf("Faltam arquivos.\n");
            return 1;
        }
        ListaCompras lista;
        for (int i = 0; i < qtdArquivos; i++) {
            if (lerDados(argv[3 + i], &lista) == 0) {
                return 1;
            }
        }

        printarComparacaoEsparsa(&lista, &argv[3 + qtdArquivos]);
        return 0;
    }

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
    printarSimilaridadeEficiente(&lista, &argv[3]);
        break;

    case 4:
    printarRecomendacoes(&lista, atoi(argv[3]), &argv[4]);
        break;
    }


    return 0;
}