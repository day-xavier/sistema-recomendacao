#ifndef SIMILARIDADE_H 
#define SIMILARIDADE_H
#include "listaCompras.h"

void montarMatrizCompras(const ListaCompras& lista, std::vector<std::vector<int>>& matrizCompras);

void transposta(const std::vector<std::vector<int>>& matriz, std::vector<std::vector<int>>& matrizTransposta);

void multiplicar(const std::vector<std::vector<int>>& matrizA, const std::vector<std::vector<int>>& matrizB, std::vector<std::vector<int>>& resultado);

void calcularSimilaridade(const ListaCompras& lista, std::vector<std::vector<double>>& matrizSimilaridade);

int clienteMaisSimilar(const std::vector<std::vector<double>>& matrizSimilaridade, int clienteIndex);

#endif