#ifndef UTILS_H
#define UTILS_H
#include <stdbool.h>


#define LARGURA_PADRAO 3
#define ALTURA_PADRAO 50
#define ESPACO_LATERAL_PADRAO 4 
#define NOME_ARQUIVO_PADRAO "Codigo_barras.pbm"

//funções
bool validar_id(const char *id);
char *gerar_sequencia_binaria(const char *id);
void gerar_pbm(const char *sequencia_binaria, int larguraModulo, int altura, int espacamentoLateral, const char *nomeArquivo);

#endif