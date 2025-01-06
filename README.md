# Gerador e Extrator de Código de Barras EAN-8

Este projeto implementa dois programas em C para manipulação de códigos de barras no padrão EAN-8. O objetivo é gerar imagens de códigos de barras a partir de um identificador e extrair o identificador de arquivos de imagem no formato PBM.

---

## Funcionalidades

1. **Gerar Código de Barras:**
   - Gera um código de barras EAN-8 baseado em um identificador fornecido.
   - Valida o identificador, incluindo o dígito verificador.
   - Permite personalizar:
     - Espaçamento lateral do código.
     - Largura de cada barra.
     - Altura da imagem.
     - Nome do arquivo de saída.

   **Exemplo:**
   - Entrada do programa (linha de comando):
     ```bash
     ./gerador 40170725 --altura 50 --largura 3 --saida codigo.pbm
     ```
   - Resultado:
     Um arquivo `codigo.pbm` no formato PBM que contém o código de barras gerado para o identificador `40170725`.

     O arquivo gerado contém:
     ```
     P1
     209 58
     000000000000000000000000
     000011100011101100001110
     ...
     ```

---

2. **Extrair Código de Barras:**
   - Lê um arquivo PBM gerado pelo gerador.
   - Verifica se o arquivo contém um código de barras válido.
   - Extrai o identificador representado na imagem.

   **Exemplo:**
   - Arquivo de entrada: `codigo.pbm`
   - Entrada do programa (linha de comando):
     ```bash
     ./extrator codigo.pbm
     ```
   - Resultado:
     O identificador é exibido no terminal:
     ```
     Identificador: 40170725
     ```

---

## Como Funciona

### 1. Gerador de Código de Barras
- O programa recebe como entrada:
  - **Identificador obrigatório**: O número que será transformado em código de barras.
  - **Parâmetros opcionais**:
    - `--altura`: Altura do código de barras em pixels (padrão: 50).
    - `--largura`: Largura de cada barra em pixels (padrão: 3).
    - `--saida`: Nome do arquivo PBM gerado (padrão: `codigo.pbm`).

- Validação:
  - O identificador deve conter 8 dígitos numéricos.
  - O último dígito é validado como o dígito verificador.

- Exemplo de Execução:
  ```bash
  ./gerador 40170725 --altura 50 --largura 3 --saida codigo.pbm
