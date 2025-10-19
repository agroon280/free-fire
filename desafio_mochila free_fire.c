#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Limite de itens na mochila (10 itens, conforme solicitado)
#define MAX_COMPONENTES 10

// Variáveis globais para medir comparações
long long comparacoesGlobais = 0;
char itemChave[30] = ""; // Nome do item buscado

// Definição da estrutura
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente; // Mantendo o nome da struct Componente por convenção, mas representando um "Item"


// ====================================================================
//                       FUNÇÕES DE UTILIDADE
// ====================================================================

// Limpa o buffer de entrada (stdin)
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Exibe o vetor de itens da mochila formatado
void mostrarComponentes(Componente componentes[], int tamanho) {
    printf("\n--- Itens da Mochila (%d/%d) ---\n", tamanho, MAX_COMPONENTES);
    if (tamanho == 0) {
        printf("A mochila está vazia.\n");
        printf("----------------------------------\n");
        return;
    }
    
    printf("Pos | %-28s | %-18s | Prioridade\n", "Nome do Item", "Tipo");
    printf("----|------------------------------|--------------------|------------\n");
    for (int i = 0; i < tamanho; i++) {
        printf("%02d. | %-28s | %-18s | %d\n", 
               i + 1,
               componentes[i].nome,
               componentes[i].tipo,
               componentes[i].prioridade);
    }
    printf("------------------------------------------------------------------\n");
}

// Cria um novo item para a mochila (usando scanf e limpeza manual)
Componente criarNovoComponente(Componente componentes[], int *tamanho) {
    Componente novo;
    printf("\n--- Cadastro de Novo Item ---\n");
    
    // Leitura do Nome
    printf("Nome do Item (max 29 chars): ");
    scanf(" %29[^\n]", novo.nome); 
    
    // Leitura do Tipo
    printf("Tipo (ex: consumivel, arma, armadura) (max 19 chars): ");
    scanf(" %19[^\n]", novo.tipo); 
    
    // Leitura da Prioridade (validando 1-10)
    printf("Prioridade (1 a 10): ");
    while (scanf("%d", &novo.prioridade) != 1 || novo.prioridade < 1 || novo.prioridade > 10) {
        limparBuffer();
        printf("Prioridade inválida. Digite um número inteiro entre 1 e 10: ");
    }
    limparBuffer();
    
    printf("\n[CADASTRO] Item '%s' inserido com sucesso!", novo.nome);
    (*tamanho)++;
    return novo;
}


// ====================================================================
//                      FUNÇÕES DE ORDENAÇÃO
// ====================================================================

// Bubble Sort: Ordena por Nome (O(n^2))
void bubbleSortNome(Componente componentes[], int tamanho) {
    comparacoesGlobais = 0; 
    int trocou;
    
    for (int i = 0; i < tamanho - 1; i++) {
        trocou = 0;
        for (int j = 0; j < tamanho - 1 - i; j++) {
            // Compara strings e conta
            comparacoesGlobais++;
            if (strcmp(componentes[j].nome, componentes[j+1].nome) > 0) {
                // Swap (Troca)
                Componente temp = componentes[j];
                componentes[j] = componentes[j+1];
                componentes[j+1] = temp;
                trocou = 1;
            }
        }
        if (trocou == 0) break; // Otimização
    }
    printf("\n[ORDENAÇÃO] Bubble Sort por Nome concluído.\n");
}


// Insertion Sort: Ordena por Tipo (O(n^2))
void insertionSortTipo(Componente componentes[], int tamanho) {
    comparacoesGlobais = 0;
    int j;
    Componente chave;

    for (int i = 1; i < tamanho; i++) {
        chave = componentes[i];
        j = i - 1;
        
        // Compara strings e conta
        while (j >= 0 && (comparacoesGlobais++, strcmp(componentes[j].tipo, chave.tipo) > 0)) {
            componentes[j + 1] = componentes[j];
            j = j - 1;
        }
        componentes[j + 1] = chave;
    }
    printf("\n[ORDENAÇÃO] Insertion Sort por Tipo concluído.\n");
}

// Selection Sort: Ordena por Prioridade (O(n^2))
void selectionSortPrioridade(Componente componentes[], int tamanho) {
    comparacoesGlobais = 0;
    int min_idx;

    for (int i = 0; i < tamanho - 1; i++) {
        min_idx = i;
        for (int j = i + 1; j < tamanho; j++) {
            // Compara inteiros e conta
            comparacoesGlobais++;
            if (componentes[j].prioridade < componentes[min_idx].prioridade) {
                min_idx = j;
            }
        }
        // Swap (Troca)
        if (min_idx != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[min_idx];
            componentes[min_idx] = temp;
        }
    }
    printf("\n[ORDENAÇÃO] Selection Sort por Prioridade concluído.\n");
}

// ====================================================================
//                         FUNÇÃO DE BUSCA
// ====================================================================

// Busca Binária por Nome (O(log n)). Requer ordenação prévia por nome.
int buscaBinariaPorNome(Componente componentes[], int tamanho, const char *nomeBusca) {
    int inicio = 0;
    int fim = tamanho - 1;
    int meio;
    int comparacao;
    
    comparacoesGlobais = 0; 
    
    while (inicio <= fim) {
        meio = inicio + (fim - inicio) / 2;
        
        comparacao = strcmp(componentes[meio].nome, nomeBusca);
        comparacoesGlobais++;
        
        if (comparacao == 0) {
            return meio; // Encontrado
        } else if (comparacao < 0) {
            inicio = meio + 1; // Busca na direita
        } else {
            fim = meio - 1; // Busca na esquerda
        }
    }
    
    return -1; // Não encontrado
}


// ====================================================================
//                        FUNÇÃO DE DESEMPENHO
// ====================================================================

// Mede tempo e comparações de qualquer algoritmo de ordenação
void medirDesempenhoOrdenacao(Componente componentes[], int tamanho, 
                              void (*algoritmo)(Componente[], int), 
                              const char *nomeAlgoritmo) 
{
    if (tamanho == 0) {
        printf("\n[INFO] Não há itens para ordenar na mochila.\n");
        return;
    }
    
    // Início da medição
    clock_t inicio, fim;
    inicio = clock();
    
    // Executa a função de ordenação passada como argumento
    algoritmo(componentes, tamanho);
    
    fim = clock();
    double tempo_gasto = (double)(fim - inicio) / CLOCKS_PER_SEC * 1000;

    // Exibe o feedback
    printf("--------------------------------------------------\n");
    printf("   [PERFORMANCE %s]\n", nomeAlgoritmo);
    printf("   -> Comparações realizadas: %lld\n", comparacoesGlobais);
    printf("   -> Tempo de execução: %.3f ms\n", tempo_gasto);
    printf("--------------------------------------------------\n");
    
    mostrarComponentes(componentes, tamanho);
}


// ====================================================================
//                             MENU PRINCIPAL
// ====================================================================

int main() {
    Componente componentes[MAX_COMPONENTES];
    int tamanho = 0;
    int opcao;
    
    // Vetor de backup para restaurar o estado original antes de cada ordenação
    Componente componentesBackup[MAX_COMPONENTES]; 

    // Inicializa backup (vazio)
    memcpy(componentesBackup, componentes, sizeof(Componente) * tamanho);

    do {
        // Exibe o menu interativo
        printf("\n======================================================\n");
        printf("            MENU - MOCHILA DO JOGADOR\n");
        printf("======================================================\n");
        printf(" 1. Cadastrar Novo Item (Atual: %d/%d)\n", tamanho, MAX_COMPONENTES);
        printf(" 2. Ordenar por NOME (Bubble Sort) e medir desempenho\n");
        printf(" 3. Ordenar por TIPO (Insertion Sort) e medir desempenho\n");
        printf(" 4. Ordenar por PRIORIDADE (Selection Sort) e medir desempenho\n");
        printf(" 5. Buscar Item por NOME (Busca Binária)\n");
        printf(" 6. Exibir Itens Atuais na Mochila\n");
        printf(" 0. Sair\n");
        printf("------------------------------------------------------\n");
        printf("Escolha uma opção: ");
        
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = -1;
            printf("\nOpção inválida. Tente novamente.\n");
            continue;
        }
        limparBuffer();

        // Restaura o vetor principal a partir do backup antes da operação
        memcpy(componentes, componentesBackup, sizeof(Componente) * tamanho);

        switch (opcao) {
            case 1:
                if (tamanho < MAX_COMPONENTES) {
                    componentes[tamanho] = criarNovoComponente(componentes, &tamanho);
                    // Atualiza o backup
                    memcpy(componentesBackup, componentes, sizeof(Componente) * tamanho);
                } else {
                    printf("\n[ERRO] Limite máximo de %d itens atingido!\n", MAX_COMPONENTES);
                }
                break;
            
            case 2:
                medirDesempenhoOrdenacao(componentes, tamanho, bubbleSortNome, "Bubble Sort (Nome)");
                break;

            case 3:
                medirDesempenhoOrdenacao(componentes, tamanho, insertionSortTipo, "Insertion Sort (Tipo)");
                break;

            case 4:
                medirDesempenhoOrdenacao(componentes, tamanho, selectionSortPrioridade, "Selection Sort (Prioridade)");
                break;
            
            case 5:
                if (tamanho == 0) {
                    printf("\n[ERRO] A mochila está vazia. Não há itens para buscar.\n");
                    break;
                }
                
                printf("\n[AVISO] A busca binária exige que o vetor esteja ORDENADO por NOME!\n");
                printf("Qual o nome do item a ser buscado? ");
                // Leitura do nome da busca
                scanf(" %29[^\n]", itemChave); 
                limparBuffer();

                // Executa a busca
                int indiceEncontrado = buscaBinariaPorNome(componentes, tamanho, itemChave);

                printf("\n--- RESULTADO DA BUSCA BINÁRIA ---\n");
                if (indiceEncontrado != -1) {
                    printf("-> Item '%s' ENCONTRADO na Posição %d.\n", 
                           itemChave, indiceEncontrado + 1);
                    // Confirmação visual
                    printf("\n[BUSCA] Item CONFIRMADO VISUALMENTE.\n");
                } else {
                    printf("-> Item '%s' NÃO ENCONTRADO.\n", itemChave);
                }
                printf("-> Comparações realizadas: %lld\n", comparacoesGlobais);
                printf("------------------------------------\n");
                break;
            
            case 6:
                mostrarComponentes(componentes, tamanho);
                break;

            case 0:
                printf("\nEncerrando o gerenciamento da mochila. Até mais!\n");
                break;

            default:
                printf("\nOpção inválida. Por favor, escolha uma opção do menu.\n");
        }
        
    } while (opcao != 0);

    return 0;
}