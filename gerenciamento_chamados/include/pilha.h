#ifndef PILHA_H
#define PILHA_H

#include "utils.h"
#include "fila.h"

typedef struct PilhaNode {
    Ticket data;
    struct PilhaNode* next;
} PilhaNode;

typedef struct {
    PilhaNode* top;
    size_t size;
} Pilha;

void inicializar_pilha(Pilha* p);
void destruir_pilha(Pilha* p);
void push_pilha(Pilha* p, const Ticket* t);
const PilhaNode* buscar_recursivo_pilha(const PilhaNode* node, int id, FILE* logf);

// Função que precisa conhecer tanto Fila quanto Pilha
void coletar_estatisticas(const Fila* f, const Pilha* p, Estatisticas* e);

#endif