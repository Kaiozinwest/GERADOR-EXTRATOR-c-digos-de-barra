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
bool verificar_arquivo_existente(const char *nome_arquivo);
bool arquivo_existe(const char *nome_arquivo);
bool verificar_cabecalho(FILE *arquivo, int *largura, int *altura);
bool carregar_matriz(FILE *arquivo, int largura, int altura, int **matriz);
void imprimir_matriz(int **matriz, int largura, int altura);
bool verificar_cabecalho(FILE *arquivo, int *largura, int *altura);
bool verificar_marcadores(int **matriz, int largura, int altura, int N, char *sequencia_binaria);
bool decodificar_digitos(const char *sequencia_binaria, char *identificador);

#endif