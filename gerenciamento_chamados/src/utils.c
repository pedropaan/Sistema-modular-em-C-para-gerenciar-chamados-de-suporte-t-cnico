#include "../include/utils.h"
#include "../include/fila.h"
#include "../include/pilha.h"

const char* status_to_str(Status s) {
    switch(s) { 
        case STATUS_ABERTO: return "aberto"; 
        case STATUS_EM_ANDAMENTO: return "em andamento"; 
        case STATUS_FECHADO: return "fechado"; 
        default: return "?"; 
    }
}

int str_to_status(const char* s, Status* out) {
    if (strcmp(s,"aberto")==0) { *out=STATUS_ABERTO; return 1; }
    if (strcmp(s,"em andamento")==0) { *out=STATUS_EM_ANDAMENTO; return 1; }
    if (strcmp(s,"fechado")==0) { *out=STATUS_FECHADO; return 1; }
    return 0;
}

void coletar_estatisticas(const Fila* f, const Pilha* p, Estatisticas* e) {
    e->total_abertos = e->total_andamento = e->total_fechados = 0;
    e->id_chamado_mais_antigo_aberto = -1;
    
    // Percorre a fila contando tickets por status
    const Ticket* cur = f->head;
    while(cur) { 
        if(cur->status == STATUS_ABERTO) { 
            e->total_abertos++; 
            if(e->id_chamado_mais_antigo_aberto == -1) {
                e->id_chamado_mais_antigo_aberto = cur->id; 
            }
        } else if(cur->status == STATUS_EM_ANDAMENTO) {
            e->total_andamento++; 
        } else {
            e->total_fechados++; 
        }
        cur = cur->next; 
    }
    
    // Percorre a pilha contando tickets fechados
    const PilhaNode* pn = p->top;
    while(pn) { 
        if(pn->data.status == STATUS_FECHADO) {
            e->total_fechados++; 
        }
        pn = pn->next; 
    }
    
    // Calcula percentual de concluídos
    size_t total = e->total_abertos + e->total_andamento + e->total_fechados;
    e->percentual_concluidos = total ? 100.0 * e->total_fechados / total : 0;
}