#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "geral.h"



// mostrar a lista
void printLista(int lista[], int n) {

    for (int i = 0; i< n; i ++){
        
        printf("%d ", lista[i]);

    }

    printf("\n");

}


int* ler_arquivo(const char* nome_arquivo, int* n) {
    FILE* arq = fopen(nome_arquivo, "r");
    if (arq == NULL) return NULL;

    int contador = 0;
    int temp;

    // contador descobre n
    while (fscanf(arq, "%d", &temp) != EOF) {
        contador++;
    }

    // aproveitando o contador para salvar o n
    *n = contador;

    //cria o espaço para a memória da lista
    int* lista = (int*)malloc(contador * sizeof(int));
    
    rewind(arq);
    for (int i = 0; i < contador; i++) {
        fscanf(arq, "%d", &lista[i]);
    }

    fclose(arq);
    return lista;
}




// Função auxiliar para resetar a lista antes de cada teste
void copiar_lista(int destino[], int origem[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}



