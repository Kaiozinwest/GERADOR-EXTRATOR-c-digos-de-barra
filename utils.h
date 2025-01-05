#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>

#define LARGURA_PADRAO 3
#define ALTURA_PADRAO 50
#define ESPACO_LATERAL_PADRAO 4 
#define NOME_ARQUIVO_PADRAO "Códigos_barras.pbm"

typedef struct {
    int largura_area;      
    int altura_codigo;    
    int espaco_lateral;    
    const char *nome_arquivo; 
} ConfigImagem;

bool validar_EAN8(const char *id);




#endif 