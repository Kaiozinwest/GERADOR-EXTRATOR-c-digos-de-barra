#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Erro! O nome do arquivo deve ser informado.\n");
        return 1;
    }

    const char *nome_arquivo = argv[1];
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro! Não foi possível abrir o arquivo: %s\n", nome_arquivo);
        return 1;
    }

    int largura, altura;

    // Verificar o cabeçalho
    if (!verificar_cabecalho(arquivo, &largura, &altura)) {
        fclose(arquivo);
        return 1;
    }

    // Alocar memória para a matriz
    int **matriz = (int **)malloc(altura * sizeof(int *));
    for (int i = 0; i < altura; i++) {
        matriz[i] = (int *)malloc(largura * sizeof(int));
    }

    // Ler a matriz do arquivo PBM
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            fscanf(arquivo, "%d", &matriz[i][j]);
        }
    }
    fclose(arquivo);

    // Calcular a largura de cada módulo
    int N = largura / 67; // 67 áreas no padrão EAN-8

    char sequencia_binaria[68]; // 67 áreas + 1 para '\0'
    if (verificar_marcadores(matriz, largura, altura, N, sequencia_binaria)) {
        printf("\nSequência binária válida: %s\n", sequencia_binaria);

        // Decodificar dígitos
        char identificador[9];
        if (decodificar_digitos(sequencia_binaria, identificador)) {
            printf("Identificador decodificado: %s\n", identificador);
        } else {
            printf("Erro ao decodificar os dígitos.\n");
        }
    } else {
        printf("Erro: Código de barras inválido.\n");
    }

    // Liberar memória
    for (int i = 0; i < altura; i++) free(matriz[i]);
    free(matriz);

    return 0;
}
