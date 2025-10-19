#include <stdio.h>    // Para printf, scanf, etc.
#include <string.h>   // Para strcpy, strcmp, etc.
#include <stdlib.h>   // Para exit, system (opcional para limpar tela)

// Define a capacidade máxima da mochila, conforme o requisito de até 10 itens.
#define MAX_ITENS 10

// REQUISITO FUNCIONAL: Criação da struct
// Definição da estrutura Item para armazenar os dados de cada item.

typedef struct {
    char nome[30];     // Nome do item (máx. 29 caracteres + '\0')
    char tipo[20];     // Tipo do item (ex: arma, munição, cura)
    int quantidade;    // Quantidade em estoque
} Item;

Item mochila[MAX_ITENS];
int totalItens = 0; // REQUISITO: Começa com 0 itens.


void listarItens() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", totalItens, MAX_ITENS);
    if (totalItens == 0) {
        printf("A mochila está vazia.\n");
        return;
    }
    
    // Laço 'for' para percorrer o vetor de itens.
    for (int i = 0; i < totalItens; i++) {
        printf("Nome: %s | Tipo: %s | Qtd: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("----------------------------------\n");
}

int buscarItem(const char *nomeBusca) {
    // Laço 'for' para percorrer o vetor sequencialmente.
    for (int i = 0; i < totalItens; i++) {
        // Usa strcmp para comparar strings (nomes).
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Item encontrado
        }
    }
    return -1; // Item não encontrado
}

void inserirItem() {
    // Verifica se a mochila está cheia
    if (totalItens >= MAX_ITENS) {
        // REQUISITO: Usabilidade - Mensagem orientativa.
        printf("\nERRO: A mochila está cheia! Remova um item antes de adicionar.\n");
        return;
    }
    
    // Variável temporária para armazenar a entrada do usuário.
    Item novoItem;
    char nomeBusca[30];

    printf("\n--- CADASTRO DE NOVO ITEM ---\n");
    
    // Leitura do Nome.
    printf("Nome do Item: "); 
    // Em produção, fgets com limpeza de buffer seria mais robusto.
    scanf("%29s", nomeBusca); 
    strcpy(novoItem.nome, nomeBusca);
    
    // Verifica se o item já existe para evitar duplicatas simples (boa prática).
    if (buscarItem(novoItem.nome) != -1) {
        printf("ERRO: Item com o nome '%s' já existe na mochila. Tente a opção '2' para remoção.\n", novoItem.nome);
        return;
    }

    // Leitura do Tipo.
    printf("Tipo do Item (ex: arma, munição, cura): ");
    scanf("%19s", novoItem.tipo); 
    
    // Leitura da Quantidade.
    printf("Quantidade: ");
    // Uso de scanf() para ler valores inteiros.
    if (scanf("%d", &novoItem.quantidade) != 1) {
        printf("ERRO: Entrada inválida para quantidade.\n");
        // Limpa o buffer de entrada em caso de erro.
        while (getchar() != '\n'); 
        return;
    }
    
    // Adiciona o novo item na próxima posição livre do vetor (totalItens).
    mochila[totalItens] = novoItem;
    totalItens++; // Incrementa o contador de itens.
    
    printf("\nSUCESSO: Item '%s' cadastrado com sucesso!\n", novoItem.nome);
}

void removerItem() {
    if (totalItens == 0) {
        printf("\nA mochila está vazia. Nada a remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- REMOÇÃO DE ITEM ---\n");
    printf("Informe o NOME do item a ser removido: ");
    scanf("%29s", nomeRemover); 
    
    int indice = buscarItem(nomeRemover);
    
    if (indice == -1) {
        // Mensagem orientativa.
        printf("ERRO: Item '%s' não encontrado na mochila.\n", nomeRemover);
        return;
    }
    
    for (int i = indice; i < totalItens - 1; i++) {
        // Copia a estrutura completa da posição seguinte para a atual.
        mochila[i] = mochila[i+1]; 
    }
    
    // 3. Atualiza o contador.
    totalItens--; 

    printf("\nSUCESSO: Item '%s' removido da mochila.\n", nomeRemover);
}

/**
 * @brief Ponto de entrada do programa e loop principal do menu.
 * * O menu atende ao REQUISITO: Usabilidade, sendo claro e orientativo.
 */
int main() {
    int opcao;
    
    // Configurações iniciais (opcional, para estética).
    #ifdef _WIN32
        system("chcp 65001 > NUL"); // Configura console para UTF-8 no Windows
    #endif

    printf("==========================================\n");
    printf("   SISTEMA DE MOCHILA DE ITENS \n");
    printf("==========================================\n");

    // Uso de laço 'while' para o loop de menu principal.
    while (1) {
        listarItens(); 
        
        printf("\n--- MENU DE OPÇÕES ---\n");
        printf("1. Cadastrar Novo Item\n");
        printf("2. Remover Item pelo Nome\n");
        printf("3. Buscar Item pelo Nome\n");
        printf("4. Sair do Sistema\n");
        printf("----------------------\n");
        printf("Escolha uma opção: ");
        
        // Leitura da opção
        if (scanf("%d", &opcao) != 1) {
            // Em caso de entrada não-numérica, limpa o buffer e tenta novamente.
            printf("\nOpção inválida. Digite um número.\n");
            while (getchar() != '\n'); 
            continue;
        }

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3: {
                char nomeBusca[30];
                printf("\n--- BUSCA DE ITEM ---\n");
                printf("Informe o NOME do item para buscar: ");
                scanf("%29s", nomeBusca);
                
                int indice = buscarItem(nomeBusca);
                
                if (indice != -1) {
                    // Item encontrado - exibe seus dados.
                    printf("\nITEM ENCONTRADO:\n");
                    printf("  Nome: %s\n", mochila[indice].nome);
                    printf("  Tipo: %s\n", mochila[indice].tipo);
                    printf("  Quantidade: %d\n", mochila[indice].quantidade);
                } else {
                    printf("\nITEM NÃO ENCONTRADO: O item '%s' não está na mochila.\n", nomeBusca);
                }
                break;
            }
            case 4:
                printf("\nEncerrando o Sistema. Até logo!\n");
                return 0; // Sai do loop e encerra o programa.
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }

    return 0;
}