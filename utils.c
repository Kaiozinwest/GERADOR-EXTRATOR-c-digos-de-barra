#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <ctype.h> //para usar o isdigit

bool validar_id(const char *id){
    //verificar se há apenas dígitos
    for(int i = 0; i < 8; i++){
        if(!isdigit(id[i])){
            return false;
        }
    }

    //verifica se possui extamente 8 dígitos
    if(strlen(id) != 8){
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
   return (id[7] - '0') == digito_verificador;
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

    //liberar a matriz
    for (int i = 0; i < alturaTotal; i++){
        free(matriz[i]);
    }
    free(matriz);
}
