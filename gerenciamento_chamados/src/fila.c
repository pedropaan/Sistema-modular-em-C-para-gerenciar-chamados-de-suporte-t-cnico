#include "../include/fila.h"
#include "../include/log.h"

static Ticket* novo_ticket(int id, const char* titulo, int prioridade, Status status, FILE* logf) {
    Ticket* t = (Ticket*)malloc(sizeof(Ticket));
    if (!t) {
        log_msg(logf, "ERRO", "Falha de alocacao de Ticket");
        return NULL;
    }
    t->id = id;
    strncpy(t->titulo, titulo, sizeof(t->titulo)-1);
    t->titulo[sizeof(t->titulo)-1] = '\0';
    t->prioridade = prioridade;
    t->status = status;
    t->next = NULL;
    return t;
}

void inicializar_fila(Fila* f) {
    f->head = f->tail = NULL;
    f->size = 0;
}

void destruir_fila(Fila* f) {
    Ticket* cur = f->head;
    while (cur) {
        Ticket* nxt = cur->next;
        free(cur);
        cur = nxt;
    }
    f->head = f->tail = NULL;
    f->size = 0;
}

int cadastrar_chamado(Fila* f, int id, const char* titulo, int prioridade, Status status, FILE* logf) {
    if (prioridade < 1 || prioridade > 5) {
        log_msg(logf, "ERRO", "Prioridade invalida");
        return 0;
    }
    Ticket* t = novo_ticket(id, titulo, prioridade, status, logf);
    if (!t) return 0;

    if (!f->tail) f->head = f->tail = t;
    else { f->tail->next = t; f->tail = t; }
    f->size++;
    log_msg(logf, "INFO", "Chamado cadastrado");
    return 1;
}

void listar_chamados(const Fila* f, int filtro, FILE* out) {
    const Ticket* cur = f->head;
    while (cur) {
        if (filtro == -1 || (int)cur->status == filtro) {
            fprintf(out, "#%d \"%s\" prio=%d status=%d\n", cur->id, cur->titulo, cur->prioridade, cur->status);
        }
        cur = cur->next;
    }
}

Ticket* remover_maior_prioridade(Fila* f) {
    if (!f->head) return NULL;
    Ticket* prev_min = NULL, *min_node = f->head, *prev = NULL, *cur = f->head;
    int min_prio = cur->prioridade;
    while (cur) {
        if (cur->prioridade < min_prio) { min_prio = cur->prioridade; min_node = cur; prev_min = prev; }
        prev = cur; cur = cur->next;
    }
    if (prev_min == NULL) f->head = min_node->next;
    else prev_min->next = min_node->next;
    if (min_node == f->tail) f->tail = prev_min;
    f->size--;
    return min_node;
}