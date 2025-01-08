#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"


int main(int argc, char *argv[]){
    int largura = LARGURA_PADRAO;
    int espacamento = ESPACO_LATERAL_PADRAO;
    int altura = ALTURA_PADRAO;

    const char *identificador = argv[1];

    if(validar_id(identificador)){
        printf("Identificador válido! \n");
    } else{
        printf("Identificador inválido \n");
        exit(EXIT_FAILURE);
    }

    if(argc > 2){
        espacamento = atoi(argv[2]);
    }
    if(argc > 3){
        largura = atoi(argv[3]);
    }

    if(argc > 4){
        altura = atoi(argv[4]);
    }
    
    const char *nome_arquivo = (argc > 5) ? argv[5] : NOME_ARQUIVO_PADRAO;

    char *sequencia = gerar_sequencia_binaria(identificador);
    gerar_pbm(sequencia, largura, altura, espacamento, nome_arquivo);
    


}
