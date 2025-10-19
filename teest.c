#include <stdio.h>
#include <stdlib.h>
/*INTERATIVO
int main() {
    int tamanho;
    int buscar_item(int vetor[], int tamanho, int valor);
    int inicio = 0;
    int fim = tamanho- 1;

    while(inicio <= fim) {
        int meio = inicio + (inicio - fim) / 2;
        
        if (vetor[meio] == valor) {
            return meio;
        }
        else if(vetor[meio] < valor) {
            inicio = meio + 1;
        }
        else
            fim = meio - 1;

    }
    return -1;
}*/

//RECURSIVO
/*
int budcar(int vetor[], int inicio, int tamanho, int valor);
int inicio = 0;
int fim;

if(inicio > fim) {
    printf("erro")
}

int meio = inicio + ( fim - inicio) / 2;

if (vetor[meio] == valor) {
    return meio;
}

else if (vetor[meio] < valor) {
    return budcar(vetor, meio + 1, fim,  valor)
}
else 
    return budcar(vetor, inicio, meio - 1, valor)*/

int busca_sequwncial(int vetor[], int tamanho, int chave) {
    for(int i = 0; i < tamanho; i++) {
        if(vetor[i] == chave) {
            return i;
        }
    }
    return -1;
}
//BUSCA SEQUENCIAL
int main() {
    int resultado;
    int numeros[] = {1, 3, 76, 92, 100, 6};
    int tam = sizeof(numeros) / sizeof(numeros[0]); /*isso dignifica 7 elementos vezes o total de bytes que ocupa 
    dividido pelo total de bytes que ocupa o determinado tipo de dado no ex int*/
    chave1 = 6;
    resultado = busca_sequwncial(numeros, tam, chave1);

    if (resultado != -1) {
        printf("o numero %d foi encontrado no indice %d", chave1, resultado);
    }
}

//BUSCA BINARIA