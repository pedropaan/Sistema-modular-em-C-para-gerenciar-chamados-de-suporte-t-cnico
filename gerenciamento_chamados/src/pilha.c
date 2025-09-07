#include "../include/pilha.h"
#include "../include/log.h"

void inicializar_pilha(Pilha* p) { p->top = NULL; p->size = 0; }

void destruir_pilha(Pilha* p) {
    PilhaNode* cur = p->top;
    while (cur) { PilhaNode* nxt = cur->next; free(cur); cur = nxt; }
    p->top = NULL; p->size = 0;
}

void push_pilha(Pilha* p, const Ticket* t) {
    PilhaNode* node = (PilhaNode*)malloc(sizeof(PilhaNode));
    if (!node) return;
    node->data = *t;
    node->next = p->top;
    p->top = node; p->size++;
}

const PilhaNode* buscar_recursivo_pilha(const PilhaNode* node, int id, FILE* logf) {
    if (!node) return NULL;
    if (node->data.id == id) return node;
    return buscar_recursivo_pilha(node->next, id, logf);
}