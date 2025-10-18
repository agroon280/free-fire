#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define TAM_MAX 10
#define MAX_STR_LEN 50

// Estrutura do nó
typedef struct {
    char dado[TAM_MAX][MAX_STR_LEN];
    int quantidade;
}lista_estatica;

void inicializar_lista_estica(lista_estatica* lista);
void inserir_nalista_estatica(lista_estatica* lista, const char texto);
void remover_dalista_estatica(lista_estatica* lista, const char texto);
void mostrar_lista_estatica(const lista_estatica* lista);

typedef struct No {
    char* dado;
    struct No* proximo;

}No;

typedef No* lista_encadeada;

void iniciar_lista_encadeada(lista_encadeada* lista);
void inserir_lista_encadeada(lista_encadeada* lista, const char* texto);
void remover_lista_encadeada(lista_encadeada* lista, const char* texto);

void listar_lista_encadeada(const lista_encadeada lista);
void liberar_lista_encadeada(lista_encadeada* lista);

void menulista_estatica();
void menulista_encadeada();

int main() 
{
int opcao;
do{
    printf("========== MANIPULACAO DE LISTA ==========\n");
    Printf("1 - LISTA ESTATICA\n2 - LISTA ENCADEADA\n0 - SAIR DO PROGRAMA\nESCOLHA UMA DAS OPCOES ACIMA: ");
    scanf("%d", &opcao);

    switch (opcao){
        case 1:
             menulista_estatica();
             break;

        case 2:
             menulista_encadeada();
             break;

        case 0:
            printf("SAINDO DO PROGRAMA....\n");
            break;
    
        default:
             printf("opcao invalida, tente novamente\n");
             break;
}
}while(opcao != NULL);

return 0;
}

void inicializar_lista_estica(lista_estatica* lista) {
    lista->quantidade = 0;

}

void inserir_nalista_estatica(lista_estatica* lista, const char texto) {
    if (lista->quantidade == TAM_MAX) {
        printf("erro lista cheia\n");
        return;
    }
    strcpy(lista->dado[lista->quantidade], texto);
    lista->quantidade++;

    printf("texto: %s\ninserido com sucesso", texto);
}

void remover_dalista_estatica(lista_estatica* lista, const char texto) {
    int i, pos = -1;

    for(i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dado[i], texto) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("erro, texto nao encontrado");
        return;
    }

    for (i = pos; i < lista->quantidade - 1; i ++) {
        strcpy(lista->dado[i], lista->dado[i +1]);
    }

    lista->quantidade--;
    printf("removido da lista com sucesso!\n");
}


void mostrar_lista_estatica(const lista_estatica* lista) {

    
}