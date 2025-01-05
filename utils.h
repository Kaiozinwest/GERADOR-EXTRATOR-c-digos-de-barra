#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>


#define LARGURA_PADRAO 3
#define ALTURA_PADRAO 50
#define ESPACO_LATERAL_PADRAO 4 
#define NOME_ARQUIVO_PADRAO "Codigos_barras.pbm"

typedef struct {
    int largura_area;
    int altura_codigo;
    int espacamento;
    char nome_arquivo;
} Img_configs;

//funções
bool validar_id(const char *id);
void gerar_sequencia_binaria(const char *id, char *barras);


#endif