#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

typedef enum {
    STATUS_ABERTO = 0,
    STATUS_EM_ANDAMENTO = 1,
    STATUS_FECHADO = 2
} Status;

typedef struct {
    size_t total_abertos;
    size_t total_andamento;
    size_t total_fechados;
    int id_chamado_mais_antigo_aberto;
    double percentual_concluidos;
} Estatisticas;

const char* status_to_str(Status s);
int str_to_status(const char* s, Status* out);

#endif