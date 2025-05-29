# 📁 Projeto de Estrutura de Dados

Este projeto em linguagem C implementa um sistema para **armazenamento, ordenação e visualização de registros de pacientes**. Os dados são persistidos em disco por meio de arquivos binários, e podem ser exibidos ordenadamente usando diferentes critérios (dia, mês, ano de entrada ou idade do paciente), por meio de uma **árvore binária de busca (BST)**.

## ⚠️ OBSERVAÇÃO IMPORTANTE!
- Se estiver executando no Windows, recomendável que troque os comandos **system("clear")** por **system("cls")**

## 🧠 Funcionalidades

- 📦 **Persistência de dados** com arquivos binários (`lista.bin`)
- 🌳 **Árvore binária de busca (AVL)** para ordenação e pesquisa
- 🔍 Exibição dos dados ordenados por:
  - Dia de entrada
  - Mês de entrada
  - Ano de entrada
  - Idade do paciente
- 🧾 Interface textual para interação com o usuário
- 🧼 Gerenciamento de memória dinâmica e limpeza de buffers

## 📂 Estrutura do Projeto
```bash
📁 include/
├── atendimento_prioritario.h
├── atendimento.h
├── cadastro.h
├── limpabuffer.h
├── main.h
├── pesquisa.h
├── salvar.h
└── sobre.h
📁 src/
├── atendimento_prioritario.c
├── atendimento.c
├── cadastro.c
├── limpabuffer.c
├── main.c
├── pesquisa.c
├── salvar.c
└── sobre.c
```
## 🏗️ Como funciona

1. Os dados dos pacientes são armazenados em uma lista encadeada simples.
2. Essa lista pode ser salva em um arquivo binário (`salvar_lista`) e carregada posteriormente (`carregar_lista`).
3. Após isso, os pacientes podem ser enfileirados em uma fila de atendimento (prioritário ou não), ou pesquisados usando a árvore binária.
4. Ao selecionar um modo de ordenação, os registros são inseridos em uma árvore binária de acordo com o critério selecionado.
5. Em seguida, uma travessia **in-ordem** (em ordem simétrica) é realizada para exibir os dados de forma crescente.

## 💡 Tecnologias Utilizadas

- Linguagem C
- Estruturas de dados (lista encadeada, fila, pilha e árvore binária)
- Manipulação de arquivos binários (`fread`, `fwrite`)

## 🚀 Como Compilar

Compile usando `gcc`:

```bash
gcc -o src/*.c
```

Execute com:
```bash
./a.out
```
