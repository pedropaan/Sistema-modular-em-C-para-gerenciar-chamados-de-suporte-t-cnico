#include "../include/fila.h"
#include "../include/pilha.h"
#include "../include/utils.h"
#include "../include/log.h"
#include <string.h> // Adicionado para usar strlen

static void menu(void){
    printf("\n--- Sistema de Chamados ---\n");
    printf("1) Cadastrar Chamado\n");
    printf("2) Listar Chamados\n");
    printf("3) Atender Chamado\n");
    printf("4) Exibir Estatisticas\n");
    printf("5) Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void){
    Fila fila; 
    Pilha pilha; 
    inicializar_fila(&fila); 
    inicializar_pilha(&pilha);
    
    FILE* logf = fopen("log.txt", "a"); 
    if(!logf){
        printf("Erro ao abrir o arquivo de log!\n"); 
        return 1;
    }
    
    int op;
    while(1){ 
        menu(); 
        
        // Validação da entrada do menu principal
        if (scanf(" %d", &op) != 1) {
            printf("Entrada invalida. Por favor, digite um numero.\n");
            // Limpa o buffer de entrada para evitar um loop infinito
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue; // Volta para o início do loop
        }
        
        if(op == 1){ 
            int id, prio;
            Status st;
            char titulo[100]; 
            
            // --- VALIDAÇÃO DO ID ---
            while (1) {
                printf("Digite o ID (numero positivo): ");
                if (scanf(" %d", &id) == 1 && id > 0) {
                    break; // Sai do loop se a entrada for válida
                }
                printf("ID invalido. Tente novamente.\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            }
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer antes do fgets

            // --- VALIDAÇÃO DO TÍTULO ---
            while (1) {
                printf("Digite o Titulo: ");
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = 0; // Remove o \n
                if (strlen(titulo) > 0) {
                    break; // Sai do loop se o título não estiver vazio
                }
                printf("O titulo nao pode ser vazio. Tente novamente.\n");
            }
            
            // --- VALIDAÇÃO DA PRIORIDADE ---
            while (1) {
                printf("Digite a Prioridade (1=Alta, 5=Baixa): ");
                if (scanf(" %d", &prio) == 1 && prio >= 1 && prio <= 5) {
                    break; // Sai do loop se a entrada for válida
                }
                printf("Prioridade invalida. Deve ser um numero entre 1 e 5.\n");
                while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            }

            // --- VALIDAÇÃO DO STATUS ---
            while (1) {
                printf("Digite o Status (0=Aberto, 1=Em Andamento): ");
                if (scanf(" %d", (int*)&st) == 1 && (st == STATUS_ABERTO || st == STATUS_EM_ANDAMENTO)) {
                    break; // Sai do loop se a entrada for válida
                }
                printf("Status invalido. Deve ser 0 ou 1.\n");
                while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer
            }
            
            cadastrar_chamado(&fila, id, titulo, prio, st, logf);
            printf("Chamado #%d cadastrado com sucesso!\n", id);
        
        } else if(op == 2){ 
            printf("\n--- Lista de Chamados na Fila ---\n");
            listar_chamados(&fila, -1, stdout);
        
        } else if(op == 3){ 
            Ticket* t = remover_maior_prioridade(&fila); 
            if(!t) {
                printf("Nenhum chamado na fila para atender.\n"); 
            } else { 
                printf("Chamado #%d atendido e movido para o historico.\n", t->id); 
                t->status = STATUS_FECHADO;
                push_pilha(&pilha, t); 
                free(t);
            } 
        
        } else if(op == 4){ 
            Estatisticas e; 
            coletar_estatisticas(&fila, &pilha, &e); 
            printf("\n--- Estatisticas ---\n");
            printf("Chamados Abertos: %zu\n", e.total_abertos);
            printf("Chamados em Andamento: %zu\n", e.total_andamento);
            printf("Chamados Fechados (Historico): %zu\n", e.total_fechados);
            printf("Percentual de Concluidos: %.1f%%\n", e.percentual_concluidos);
        
        } else if(op == 5) {
            printf("Saindo do sistema...\n");
            break; 
        
        } else {
            printf("Opcao invalida! Escolha um numero de 1 a 5.\n");
        }
    }
    
    destruir_fila(&fila); 
    destruir_pilha(&pilha); 
    fclose(logf);
    
    return 0;
}