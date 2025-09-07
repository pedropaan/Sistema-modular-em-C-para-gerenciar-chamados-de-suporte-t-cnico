#ifndef FILA_H
#define FILA_H

#include <stddef.h>
#include "utils.h"

typedef struct Ticket {
    int id;
    char titulo[100];
    int prioridade; /* 1 (high) to 5 (low) */
    Status status;
    struct Ticket* next;
} Ticket;

typedef struct {
    Ticket* head;
    Ticket* tail;
    size_t size;
} Fila;

void inicializar_fila(Fila* f);
void destruir_fila(Fila* f);
int cadastrar_chamado(Fila* f, int id, const char* titulo, int prioridade, Status status, FILE* logf);
void listar_chamados(const Fila* f, int filtro, FILE* out);
Ticket* remover_maior_prioridade(Fila* f);

#endif