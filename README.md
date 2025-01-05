# GERADOR-EXTRATOR-c-digos-de-barra
Projeto para a disciplina introdução a técnicas de programação 


## Descrição
Este projeto implementa um **Gerador** e um **Extrator** de códigos de barras no padrão **EAN-8** utilizando a linguagem C. O objetivo é permitir:

1. **Gerar um arquivo PBM** contendo a representação gráfica de um código EAN-8 a partir de um identificador fornecido.
2. **Extrair o identificador** de um arquivo PBM contendo um código de barras EAN-8.

O projeto utiliza arquivos separados para organização das funções e segue padrões claros para a validação e manipulação do padrão EAN-8 e do formato PBM.

---

## Funcionalidades

### Gerador
- **Validação do identificador**:
  - Confirma se o identificador tem 8 dígitos.
  - Calcula e valida o dígito verificador.
- **Geração do código de barras**:
  - Transforma o identificador em uma sequência binária (`1`s e `0`s).
  - Cria um arquivo PBM com o espaçamento e dimensões configuráveis.
- **Sobrescrita de arquivos existentes**:
  - Verifica se o arquivo de saída já existe e pergunta se o usuário deseja sobrescrevê-lo.

### Extrator
- **Leitura do arquivo PBM**:
  - Verifica se o arquivo existe e é válido.
- **Identificação do código de barras**:
  - Extrai a sequência binária representando as barras.
  - Decodifica o identificador numérico EAN-8.

---

## Como Executar

### Requisitos
- **Compilador C** (ex.: GCC).

### Compilação
1. Navegue até o diretório do projeto.
2. Compile os arquivos:
   ```bash
   gcc -o gerador gerador.c utils.c -lm
   gcc -o extrator extrator.c utils.c -lm
   ```

### Uso

#### Gerador
Para gerar um código de barras PBM:
```bash
./gerador <identificador> [largura_area] [altura_codigo] [espaco_lateral] [nome_arquivo]
```
**Exemplo**:
```bash
./gerador 40170725 3 50 4 "codigo.pbm"
```
- `40170725`: Identificador do código de barras.
- `3`: Largura de cada barra em pixels.
- `50`: Altura do código de barras em pixels.
- `4`: Espaço lateral (esquerda/direita) em pixels.
- `"codigo.pbm"`: Nome do arquivo gerado (opcional).

#### Extrator
Para extrair o identificador de um arquivo PBM:
```bash
./extrator <nome_arquivo>
```
**Exemplo**:
```bash
./extrator codigo.pbm
```

---

## Estrutura do Projeto

```
/
|-- gerador.c      // Função principal para gerar códigos de barras
|-- extrator.c     // Função principal para extrair identificadores
|-- utils.c        // Funções compartilhadas entre gerador e extrator
|-- utils.h        // Definições de structs e protótipos de funções
|-- README.md      // Documentação do projeto
```

---

## Exemplo de Saída (Gerador)

Arquivo gerado para o identificador `40170725` com espaço lateral de 4 pixels:
```
P1
103 58
0000000000000000000000000
0000000000000000000000000
... (conteúdo do código de barras)
0000000000000000000000000
```

---

## Licença
Este projeto está licenciado sob a licença MIT. Consulte o arquivo LICENSE para mais informações.

