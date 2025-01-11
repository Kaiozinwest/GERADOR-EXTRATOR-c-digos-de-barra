#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h> //para usar o isdigit

bool validar_id(const char *id){
    //verificar se há apenas dígitos
    for(int i = 0; i < strlen(id); i++){
        if(!isdigit(id[i])){
            printf("Erro, o identificador deve possuir apenas dígitos. \n");
            return false;
        }
    }

    //verifica se possui extamente 8 dígitos
    if(strlen(id) != 8){
        printf("Erro!, o identificador deve possuir exatamente 8 dígitos. \n");
        return false;
    }

    //verificando se o id é válido
   int soma = 0;
   for(int i = 0; i < 7; i++){
    int digito = id[i] - '0';
    if(i % 2 == 0){
        soma += digito * 3;
    }else{
        soma += digito;
    }
   }
   
   //calculo do digito verificador 
   int digito_verificador = 10 - (soma % 10) % 10;

   if((id[7] - '0') != digito_verificador){
        printf("O dígito verificador não corresponde a os dígitos anteriores! \n");
        return false;
   }
   return true;
}

//gerar a sequencia de 0s e 1s
char *gerar_sequencia_binaria(const char *id) {
    
    const char *L_code[] = {
    "0001101", "0011001", "0010011", "0111101", "0100011",
    "0110001", "0101111", "0111011", "0110111", "0001011"
};

const char *R_code[] = {
    "1110010", "1100110", "1101100", "1000010", "1011100",
    "1001110", "1010000", "1000100", "1001000", "1110100"
};
    
    int tamanho = 3 + (7 * 4) + 5 + (7 * 4) + 3 + 1; // Tamanho total da sequência binária
    char *barras = (char *)malloc(tamanho * sizeof(char));
    if (!barras) {
        fprintf(stderr, "Erro ao alocar memória para a sequência binária.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(barras, "101"); // Marcador inicial

    for (int i = 0; i < 4; i++) {
        strcat(barras, L_code[id[i] - '0']);
    }

    strcat(barras, "01010"); // Marcador central

    for (int i = 4; i < 8; i++) {
        strcat(barras, R_code[id[i] - '0']);
    }

    strcat(barras, "101"); // Marcador final

    return barras; // Retorna a sequência binária
}

void gerar_pbm(const char *sequencia_binaria, int larguraModulo, int altura, int espacamentoLateral, const char *nomeArquivo){
    int larguraCodigo = strlen(sequencia_binaria) * larguraModulo;
    int larguraTotal = larguraCodigo + 2 * espacamentoLateral;
    int alturaTotal = altura + 2 * espacamentoLateral;

    //alocar memoria para a matriz
    int **matriz = (int**)malloc(alturaTotal * sizeof(int*));
    for (int i = 0; i < alturaTotal; i++){
        matriz[i] = (int*)malloc(larguraTotal * sizeof(int));
    }

    //preencher toda a matriz com 0s
    for(int i = 0; i < alturaTotal; i++){
        for(int j = 0; j < larguraTotal; j++){
            matriz[i][j] = 0;        
            }
    }

    //preencher a area com o codigo
    for(int i = espacamentoLateral; i < espacamentoLateral + altura; i++){
        for (int j = espacamentoLateral, index = 0; index < strlen(sequencia_binaria); index++){
            char bit = sequencia_binaria[index];
            for(int u = 0; u < larguraModulo; u++, j++){
                matriz[i][j] = bit - '0';
            }
        }
    }


    // Escrever o arquivo PBM 
    FILE *arquivo = fopen(nomeArquivo, "w");
    if(!arquivo){
        fprintf(stderr, "Erro, não foi possível criar o arquivo %s.\n", nomeArquivo);
    }   

    fprintf(arquivo, "P1\n");
    fprintf(arquivo, "%d %d\n", larguraTotal, alturaTotal);


    for(int i = 0; i < alturaTotal; i++){
        for(int j = 0; j < larguraTotal; j++){
            fprintf(arquivo, "%d ", matriz[i][j]);
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);

     // Converter PBM para imagem (ex: PNG) usando ImageMagick
    char comando[256];
    snprintf(comando, sizeof(comando), "convert %s %s.png", nomeArquivo, nomeArquivo);
    if (system(comando) != 0) {
        fprintf(stderr, "Erro ao converter o arquivo PBM para imagem.\n");
    } else {
        printf("Imagem gerada com sucesso: %s.png\n", nomeArquivo);
    }
    

    //liberar a matriz
    for (int i = 0; i < alturaTotal; i++){
        free(matriz[i]);
    }
    free(matriz);
}

bool arquivo_existe(const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo){
        fclose(arquivo);
        return true;
    } else{
        return false;
    }
}

bool verificar_arquivo_existente(const char *nome_arquivo){
    if(arquivo_existe(nome_arquivo)){
        printf("Deseja sobreesvrever o arquivo? (S / N)");
        char resposta;
        scanf("%c", &resposta);
        if(resposta != 's' && resposta != 'S'){
            return false;
        }
    }
    return true;
}

bool verificar_cabecalho(FILE *arquivo, int *largura, int *altura) {
    char linha[256];

    // Pular linhas ou espaços em branco no início do arquivo
    int ch;
    do {
        ch = fgetc(arquivo);
    } while (isspace(ch));

    if (ch == EOF) {
        fprintf(stderr, "Erro: O arquivo está vazio ou mal formatado.\n");
        return false;
    }

    // Recolocar o caractere não espaço de volta no fluxo
    ungetc(ch, arquivo);

    // Ler o formato (primeira linha do arquivo)
    if (!fgets(linha, sizeof(linha), arquivo)) {
        fprintf(stderr, "Erro: Não foi possível ler o formato.\n");
        return false;
    }

    // Remover caracteres invisíveis
    linha[strcspn(linha, "\r\n")] = '\0';

    // Verificar o formato P1
    if (strcmp(linha, "P1") != 0) {
        fprintf(stderr, "Erro: O arquivo não segue o formato PBM esperado (P1).\n");
        return false;
    }

    // Ler as dimensões (segunda linha do arquivo)
    if (!fgets(linha, sizeof(linha), arquivo) || sscanf(linha, "%d %d", largura, altura) != 2) {
        fprintf(stderr, "Erro: Dimensões inválidas no cabeçalho do arquivo.\n");
        return false;
    }
    printf("%d %d", *largura, *altura);
    return true; // Cabeçalho válido
}





bool verificar_marcadores(int **matriz, int largura, int altura, int N, char *sequencia_binaria) {
    int margem = (largura - (N * 67)) / 2; // Espaço lateral
    int pos = 0;

    // Extrair a sequência binária
    for (int i = margem; i < largura - margem; i += N) {
        int soma = 0;
        for (int j = i; j < i + N; j++) {
            soma += matriz[altura / 2][j]; // Considerar linha central
        }
        sequencia_binaria[pos++] = (soma > (N / 2)) ? '1' : '0';
    }
    sequencia_binaria[pos] = '\0';

    // Calcular índices dos marcadores
    int inicio = 0;                     // Marcador inicial
    int central = 3 + 28;               // Após marcador inicial + L-code
    int fim = central + 5 + 28;         // Após marcador central + R-code

    // Verificar marcadores
    if (strncmp(&sequencia_binaria[inicio], "101", 3) != 0) {
        printf("Erro: Marcador de início inválido.\n");
        return false;
    }

    if (strncmp(&sequencia_binaria[central], "01010", 5) != 0) {
        printf("Erro: Marcador central inválido.\n");
        return false;
    }

    if (strncmp(&sequencia_binaria[fim], "101", 3) != 0) {
        printf("Erro: Marcador de fim inválido.\n");
        return false;
    }

    return true;
}

bool decodificar_digitos(const char *sequencia_binaria, char *identificador) {
    const char *L_code[] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};
    const char *R_code[] = {"1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100"};

    int pos = 0;

    // Decodificar L-code (4 primeiros dígitos)
    for (int i = 3; i < 31; i += 7) {
        bool encontrado = false;
        for (int j = 0; j < 10; j++) {
            if (strncmp(&sequencia_binaria[i], L_code[j], 7) == 0) {
                identificador[pos++] = '0' + j;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            printf("Erro: Sequência L-code inválida.\n");
            return false;
        }
    }

    // Decodificar R-code (4 últimos dígitos)
    for (int i = 36; i < 64; i += 7) {
        bool encontrado = false;
        for (int j = 0; j < 10; j++) {
            if (strncmp(&sequencia_binaria[i], R_code[j], 7) == 0) {
                identificador[pos++] = '0' + j;
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            printf("Erro: Sequência R-code inválida.\n");
            return false;
        }
    }

    identificador[pos] = '\0';
    return true;
}










