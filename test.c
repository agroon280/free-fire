#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

#define TAM_MAX 10
#define MAX_STR_LEN 50

// Estrutura da Lista Estática
typedef struct {
    char dado[TAM_MAX][MAX_STR_LEN];
    int quantidade;
} lista_estatica;

void inicializar_lista_estica(lista_estatica* lista);
// Alterado o tipo do parâmetro de 'const char' para 'const char*' (string)
void inserir_nalista_estatica(lista_estatica* lista, const char* texto); 
// Alterado o tipo do parâmetro de 'const char' para 'const char*' (string)
void remover_dalista_estatica(lista_estatica* lista, const char* texto); 
void mostrar_lista_estatica(const lista_estatica* lista);

// Estrutura do Nó da Lista Encadeada
typedef struct No {
    char* dado;
    struct No* proximo;
} No;

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
    // O usuário pediu que as respostas fossem em português brasileiro.
    // Embora o código C seja universal, manter as strings de interface em português.
    int opcao;
    do{
        printf("========== MANIPULACAO DE LISTA ==========\n");
        // CORREÇÃO: Printf para printf
        printf("1 - LISTA ESTATICA\n2 - LISTA ENCADEADA\n0 - SAIR DO PROGRAMA\nESCOLHA UMA DAS OPCOES ACIMA: "); 
        // Lidar com o \n pendente após o scanf
        if (scanf("%d", &opcao) != 1) { 
            // Limpa o buffer de entrada em caso de falha no scanf
            while (getchar() != '\n'); 
            opcao = -1; // Opção inválida
        }

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
                printf("Opcao invalida, tente novamente\n");
                break;
        }
    // CORREÇÃO: do...while(opcao != NULL) para do...while(opcao != 0)
    } while(opcao != 0);

    return 0;
}

// ====================================================================
// FUNÇÕES DA LISTA ESTÁTICA
// ====================================================================

void inicializar_lista_estica(lista_estatica* lista) {
    lista->quantidade = 0;
}

// CORREÇÃO: Alterado const char texto para const char* texto
void inserir_nalista_estatica(lista_estatica* lista, const char* texto) {
    if (lista->quantidade == TAM_MAX) {
        printf("ERRO: lista cheia\n");
        return;
    }
    // O tamanho da string não pode exceder o limite de MAX_STR_LEN - 1
    if (strlen(texto) >= MAX_STR_LEN) {
        printf("ERRO: O texto excede o tamanho maximo de %d caracteres.\n", MAX_STR_LEN - 1);
        return;
    }
    
    // CORREÇÃO: A chamada estava correta, mas o tipo do parâmetro na declaração da função estava errado
    strcpy(lista->dado[lista->quantidade], texto); 
    lista->quantidade++;

    // CORREÇÃO: Adicionado um \n para formatacao e retirado a virgula antes do texto
    printf("Texto: '%s' inserido com sucesso.\n", texto); 
}

// CORREÇÃO: Alterado const char texto para const char* texto
void remover_dalista_estatica(lista_estatica* lista, const char* texto) {
    int i, pos = -1;

    for(i = 0; i < lista->quantidade; i++) {
        if (strcmp(lista->dado[i], texto) == 0) {
            pos = i;
            break;
        }
    }

    if (pos == -1) {
        printf("ERRO: texto '%s' nao encontrado.\n", texto);
        return;
    }

    // Move os elementos à direita para a esquerda
    for (i = pos; i < lista->quantidade - 1; i ++) {
        strcpy(lista->dado[i], lista->dado[i + 1]);
    }

    lista->quantidade--;
    printf("Texto '%s' removido da lista com sucesso!\n", texto);
}


void mostrar_lista_estatica(const lista_estatica* lista) {
    if(lista->quantidade == 0) {
        // CORREÇÃO: printf estava com um '0' no final
        printf("Nao existe item na lista.\n"); 
        return;
    }
    printf("\nITENS DA LISTA ESTATICA (Total: %d):\n", lista->quantidade);
    for (int i = 0; i < lista->quantidade; i++){
        // Adicionada uma quebra de linha para cada item, para melhor visualizacao
        printf("[%d] %s\n", i + 1, lista->dado[i]); 
    }
    printf("\n");
}

// ====================================================================
// FUNÇÕES DA LISTA ENCADEADA
// ====================================================================

void iniciar_lista_encadeada(lista_encadeada* lista) {
    *lista = NULL;
}


void inserir_lista_encadeada(lista_encadeada* lista, const char* texto) {

    No* novoNo = (No*)malloc(sizeof(No));
    
    if(novoNo == NULL) {
        printf("ERRO: falha ao alocar memoria para o novo no.\n");
        return;
    }

    // O ponteiro 'dado' precisa de memória alocada para armazenar a string
    // CORREÇÃO: O ponteiro estava sendo referenciado com 'novoNO' (maiúsculo)
    novoNo->dado = (char*)malloc(strlen(texto) + 1); 

    if(novoNo->dado == NULL) {
        printf("ERRO: falha ao alocar memoria para o dado da string.\n");
        free(novoNo); // Libera o nó se não conseguir alocar o dado
        return;
    }

    // CORREÇÃO: strcp para strcpy
    strcpy(novoNo->dado, texto); 

    // Inserção no início da lista
    novoNo->proximo = *lista;
    *lista = novoNo;

    printf("Texto '%s' inserido com sucesso!\n", texto);
}

void remover_lista_encadeada(lista_encadeada* lista, const char* texto) {
    No* atual = *lista;
    No* anterior = NULL; // Começa como NULL

    // Percorre a lista para encontrar o nó e manter o anterior
    while(atual != NULL && strcmp(atual->dado, texto) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if(atual == NULL) {
        printf("ERRO: texto '%s' nao encontrado na lista.\n", texto);
        return;
    }

    // Se o anterior for NULL, significa que o nó a ser removido é o primeiro (*lista)
    if(anterior == NULL) {
        *lista = atual->proximo;
    } else {
        // CORREÇÃO: Estava apenas 'anterior =' o que é incorreto.
        // O próximo do anterior deve apontar para o próximo do atual
        anterior->proximo = atual->proximo; 
    }

    // Libera a memória alocada para a string (dado) e para o nó
    free(atual->dado); 
    // CORREÇÃO: Estava 'free(atual->proximo)' o que é incorreto
    free(atual); 
    
    printf("Dado '%s' removido com sucesso.\n", texto);
}

void listar_lista_encadeada(const lista_encadeada lista) {
    No* temp = lista;
    if(temp == NULL) {
        printf("Lista encadeada vazia.\n");
        return;
    }
    printf("\nITENS DA LISTA ENCADEADA:\n");
    // CORREÇÃO: A condição estava 'while(temp == NULL)'
    while(temp != NULL) { 
        // Adicionada quebra de linha para formatacao
        printf("%s\n", temp->dado); 
        temp = temp->proximo;
    }
    printf("\n");
}

void liberar_lista_encadeada(lista_encadeada* lista) {
    No* atual = *lista;
    No* proximo;
    
    // CORREÇÃO: A condição estava 'while(atual == NULL)'
    while(atual != NULL) { 
        proximo = atual->proximo;
        free(atual->dado); // Libera a string
        free(atual); // Libera o nó
        atual = proximo;
    }
    *lista = NULL; // A lista deve ser NULL após a liberação
    printf("Lista encadeada liberada.\n");
}

// ====================================================================
// FUNÇÕES DE MENU
// ====================================================================

void menulista_estatica() {
    lista_estatica lista;
    inicializar_lista_estica(&lista);
    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("\n========== MENU DA LISTA ESTATICA ==========\n");
        printf("1 - Inserir texto na lista\n");
        printf("2 - Remover texto da lista\n");
        printf("3 - Mostrar lista\n");
        printf("0 - Voltar para o menu principal\n");
        printf("Escolha uma opcao: ");
        
        // CORREÇÃO: O scanf deve usar o & comercial para a variável 'opcao'
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }
        
        // Limpar o buffer de entrada (importante para o scanf a seguir)
        while (getchar() != '\n'); 

        switch (opcao)
        {
            case 1:
                if (lista.quantidade < TAM_MAX) {
                    printf("Digite o texto a ser inserido (max %d caracteres): ", MAX_STR_LEN - 1);
                    // Uso de fgets para ler a string de forma segura
                    if (fgets(texto, MAX_STR_LEN, stdin) != NULL) {
                        // Remove o '\n' que o fgets adiciona
                        texto[strcspn(texto, "\n")] = 0; 
                        inserir_nalista_estatica(&lista, texto);
                    }
                } else {
                    printf("Lista cheia. Nao e possivel inserir mais itens.\n");
                }
                break;
            case 2:
                if (lista.quantidade > 0) {
                    printf("Digite o texto a ser removido: ");
                    if (fgets(texto, MAX_STR_LEN, stdin) != NULL) {
                        texto[strcspn(texto, "\n")] = 0;
                        remover_dalista_estatica(&lista, texto);
                    }
                } else {
                    printf("Lista vazia. Nada para remover.\n");
                }
                break;
            case 3:
                mostrar_lista_estatica(&lista);
                break;
            case 0:
                printf("Voltando ao menu principal.\n");
                break; // Apenas quebra o switch, o do...while encerra a função
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}

void menulista_encadeada() {
    lista_encadeada lista;
    iniciar_lista_encadeada(&lista);
    int opcao;
    char texto[MAX_STR_LEN];

    do {
        printf("\n========== MENU DA LISTA ENCADEADA ==========\n");
        printf("1 - Inserir texto na lista\n");
        printf("2 - Remover texto da lista\n");
        printf("3 - Mostrar lista\n");
        printf("4 - Liberar toda a lista\n");
        printf("0 - Voltar para o menu principal\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1;
        }
        
        while (getchar() != '\n'); // Limpar o buffer de entrada

        switch (opcao)
        {
            case 1:
                printf("Digite o texto a ser inserido (max %d caracteres): ", MAX_STR_LEN - 1);
                if (fgets(texto, MAX_STR_LEN, stdin) != NULL) {
                    texto[strcspn(texto, "\n")] = 0;
                    inserir_lista_encadeada(&lista, texto);
                }
                break;
            case 2:
                printf("Digite o texto a ser removido: ");
                if (fgets(texto, MAX_STR_LEN, stdin) != NULL) {
                    texto[strcspn(texto, "\n")] = 0;
                    remover_lista_encadeada(&lista, texto);
                }
                break;
            case 3:
                listar_lista_encadeada(lista);
                break;
            case 4:
                liberar_lista_encadeada(&lista);
                break;
            case 0:
                // Garante que a memória seja liberada ao sair do menu
                liberar_lista_encadeada(&lista); 
                printf("Voltando ao menu principal.\n");
                break; 
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 0);
}