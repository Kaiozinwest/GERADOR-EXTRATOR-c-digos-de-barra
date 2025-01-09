#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char *argv[]) {
    const char *nome_arquivo;
    FILE *arquivo;
    int largura, altura;

    if (argc < 2) {
        fprintf(stderr, "Erro! O nome do arquivo deve ser informado.\n");
        return 1;
    }

    nome_arquivo = argv[1];

    arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro! Não foi possível abrir o arquivo: %s\n", nome_arquivo);
        return 1;
    }

    if (!verificar_cabecalho(arquivo, &largura, &altura)) {
        fclose(arquivo);
        return 1;
    }
    fclose(arquivo);
    
    return 0;
}
