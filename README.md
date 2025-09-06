# 💳 Sistema de Caixa Eletrônico em C

Projeto acadêmico desenvolvido em C para simular o funcionamento de um **caixa eletrônico**, incluindo cadastro de clientes, operações bancárias e geração de relatórios.  
O sistema foi projetado em **arquitetura modular**, com foco em boas práticas de programação e simulação de cenários reais de um caixa eletrônico.

---

## 🚀 Funcionalidades

- **Gerenciamento de clientes**  
  - Incluir novo cliente (CPF e conta corrente gerados automaticamente)  
  - Mostrar clientes cadastrados  
  - Alterar dados de clientes (CPF ou conta)  
  - Excluir cliente (quando não houver saques associados)  

- **Operações bancárias**  
  - Realizar saques liberando a **menor quantidade de cédulas possível**  
  - Impressão do valor sacado por extenso  
  - Validação de conta corrente existente  

- **Relatórios**  
  - Histórico de valores sacados por cliente  
  - Valor total do saldo existente no caixa  
  - Quantidade de cédulas disponíveis  

---

## 🏗️ Estrutura do Projeto

```bash
📂 caixa-eletronico
├── main.c              # Menu principal e controle do fluxo
├── cliente.c           # Funções para cadastro, alteração e exclusão de clientes
├── saque.c             # Lógica de saque e manipulação de cédulas
├── relatorio.c         # Geração de relatórios
├── utils.c             # Funções auxiliares (ex: geração de CPF, conta corrente)
└── README.md           # Documentação do projeto