
# RELATORIO.md - Evidências de Depuração

Este relatório documenta como foi feita a **depuração** e as verificações de memória
do projeto *Sistema de Gerenciamento de Chamados*.

---

## 1. Uso do GDB (GNU Debugger)

Exemplos de breakpoints sugeridos:
```bash
gdb ./chamados
(gdb) break cadastrar_chamado
(gdb) break remover_maior_prioridade
(gdb) break push_pilha
(gdb) break coletar_estatisticas
(gdb) run
```
Durante a execução:
- `step` → executa linha a linha.
- `print variavel` → inspeciona valores.
- `bt` → mostra stack trace.
- `info locals` → exibe variáveis locais.

Exemplo:
```
Breakpoint 1, cadastrar_chamado (f=0x7fffffffde20, id=1, titulo="Teste", prioridade=1, status=0, logf=0x5555555592a0)
(gdb) print *f
$1 = { head = 0x0, tail = 0x0, size = 0 }
```

---

## 2. Uso do Valgrind

Para verificar vazamentos de memória:
```bash
valgrind --leak-check=full ./chamados
```
Exemplo de saída esperada sem vazamentos:
```
==12345== HEAP SUMMARY:
==12345==     in use at exit: 0 bytes in 0 blocks
==12345== All heap blocks were freed -- no leaks are possible
```

---

## 3. Tratamento de Erros e Logs

- Falhas de alocação (`malloc`) → `log_msg("ERRO", "...")`.
- Prioridade inválida → `log_msg("ERRO", "Prioridade invalida")`.
- Entrada incorreta → log e retorno seguro.
- Logs são gravados em **log.txt** com timestamp.

Exemplo de `log.txt`:
```
[2025-09-06 15:10:45] INFO: Chamado cadastrado
[2025-09-06 15:11:03] ERRO: Prioridade invalida
```

---

## 4. Boas Práticas Implementadas

- Modularização em `src/` e `include/`.
- Escopo controlado (`static` em funções internas).
- Comentários e README para orientação.
- `assert` em inicializações e pontos críticos.
- Liberação de memória em `destruir_fila()` e `destruir_pilha()`.

---

## 5. Conclusão

- O projeto cumpre os requisitos de **ponteiros**, **alocação dinâmica**, **recursividade**, **tratamento de erros/logs**, **estruturas dinâmicas (fila/pilha)**, e boas práticas.
- A depuração pode ser feita com **gdb** (lógica) e **valgrind** (memória).

---
