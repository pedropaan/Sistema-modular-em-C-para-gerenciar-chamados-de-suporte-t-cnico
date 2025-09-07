# Sistema de Gerenciamento de Chamados

Este projeto usa um **Sistema de Gerenciamento de Chamados** em linguagem **C**, utilizando:

- **Estruturas dinâmicas** (Fila e Pilha)  
- **Ponteiros e alocação dinâmica**  
- **Funções recursivas**  
- **Modularização** (`src/` e `include/`)  
- **Tratamento de erros e logs**  
- **Makefile** para compilação e execução  

---

## Como executar

### Pré-requisitos
- Compilador **GCC** ou compatível  
- Utilitário **make**  

### Passos
1. Extraia o projeto em uma pasta.  
2. No terminal, acesse a pasta do projeto.  
3. Execute:  
   ```bash
   make run
   ```
   O Makefile irá **compilar** e **rodar** automaticamente o programa.  

4. Para limpar os arquivos gerados:  
   ```bash
   make clean
   ```

---

## Estrutura do Projeto
```
gerenciamento_chamados/
├── src/
│   ├── main.c        # Menu principal
│   ├── fila.c        # Implementação da fila de chamados
│   ├── pilha.c       # Implementação da pilha de finalizados
│   ├── utils.c       # Funções utilitárias (status, estatísticas)
│   └── log.c         # Registro de logs
├── include/
│   ├── fila.h
│   ├── pilha.h
│   ├── utils.h
│   └── log.h
├── Makefile
├── README.md
└── RELATORIO.md      # Evidências de depuração (gdb/valgrind)
```

---

## Funcionalidades
- **Cadastrar chamado** (ID, título, prioridade e status)  
- **Listar chamados** (com filtro opcional por status)  
- **Executar atendimento** (remove da fila o chamado de maior prioridade; se finalizado, vai para a pilha)  
- **Buscar recursivamente** chamado por ID (fila ou pilha)  
- **Gerar estatísticas**:
  - Quantidade de chamados abertos, em andamento e fechados  
  - Chamado mais antigo ainda aberto  
  - Percentual de concluídos  

---

## Depuração
- **Logs** são gravados em `log.txt`.  
- Uso de **assert** e checagens de erro (`malloc`, entradas inválidas).  
- `RELATORIO.md` contém exemplos de depuração com **gdb** e **valgrind**.  

---

## Dicas
- Use nomes curtos ao cadastrar chamados (até 100 caracteres).  
- Prioridade vai de **1 (mais urgente)** até **5 (menos urgente)**.  
- Status:  
  - `0 = aberto`  
  - `1 = em andamento`  
  - `2 = fechado`  

---