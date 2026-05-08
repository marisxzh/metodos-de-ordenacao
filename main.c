#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "include/geral.h"

#include "include/heap_max.h"
#include "include/heap_min.h"
#include "include/heap_d.h"
#include "include/smoothsort.h"


void executar(int lista_original[], int n) {
    // array temporário para as cópias
    int *lista_teste = (int*)malloc(n * sizeof(int));
    clock_t inicio, fim;
    double tempo;

    printf("\n--- RESULTADOS DOS TESTES (N = %d) ---\n", n);
    printf("%-20s | %-15s\n", "Algoritmo", "Tempo (s)");
    printf("------------------------------------------\n");

    // TESTE 1: HeapSort Max
    copiar_lista(lista_teste, lista_original, n);
    inicio = clock();
    heapSortMax(lista_teste, n);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%-20s | %-15.6f\n", "HeapSort Max", tempo);

    //TESTE 2: HeapSort Min
    copiar_lista(lista_teste, lista_original, n);
    inicio = clock();
    heapSortMin(lista_teste, n);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%-20s | %-15.6f\n", "HeapSort Min", tempo);

    //TESTE 3: Heap D-ário (D=3)
    copiar_lista(lista_teste, lista_original, n);
    inicio = clock();
    heapSortD(lista_teste, n, 3); 
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%-20s | %-15.6f\n", "Heap D-ario (D=3)", tempo);

    //TESTE 4: Smoothsort
    copiar_lista(lista_teste, lista_original, n);
    inicio = clock();
    smoothSort(lista_teste, n);
    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("%-20s | %-15.6f\n", "Smoothsort", tempo);

    printf("------------------------------------------\n");

    free(lista_teste);
}


int main() {

    int n; 
    
    printf("Números aleatórios\n");

    int* listaA = ler_arquivo("aleatorio.txt", &n);

    if (listaA == NULL) {
        printf("Falha ao carregar dados.\n");
        return 1;
    }

    executar(listaA, n);
    free(listaA);



    printf("Números invertidos\n");

    int* listaI = ler_arquivo("invertido.txt", &n);

    if (listaI == NULL) {
        printf("Falha ao carregar dados.\n");
        return 1;
    }

    executar(listaI, n);
    free(listaI);


    printf("Números ordenados\n");


    int* listaO = ler_arquivo("ordenado.txt", &n);

    if (listaO == NULL) {
        printf("Falha ao carregar dados.\n");
        return 1;
    }

    executar(listaO, n);
    free(listaO);
    return 0;
}

