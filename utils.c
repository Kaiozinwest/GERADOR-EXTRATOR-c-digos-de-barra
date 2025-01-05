#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// valida o identificador
bool validar_EAN8(const char *id)
{
    if (strlen(id) != 8)
    {
        return false;
    }
    for (int i = 0; i < 8; i++)
    {
        if (!isdigit(id[i]))
        {
            return false;
        }
    }

    int soma = 0;
    for (int i = 0; i < 7; i++)
    {
        int digito = id[i] - '0';
        soma += (i % 2 == 0 ? digito * 3 : digito);
    }

    int digito_verificador = (10 - (soma % 10)) % 10;

    return id[7] - '0' == digito_verificador;
}

// cria a config padrao
ConfigImagem config_padrao(void)
{
    ConfigImagem config;
    config.largura_area = LARGURA_PADRAO;
    config.altura_codigo = ALTURA_PADRAO;
    config.espaco_lateral = ESPACO_LATERAL_PADRAO;
    config.nome_arquivo = NOME_ARQUIVO_PADRAO;
    return config;
}

// gerar a sequencia de Os e 1s para a geracao das barras
void gerar_barras(const char *id, char *barras)
{
    const char *L_code[] = {"0001101", "0011001", "0010011", "0111101", "0100011",
                            "0110001", "0101111", "0111011", "0110111", "0001011"};
    const char *R_code[] = {"1110010", "1100110", "1101100", "1000010", "1011100",
                            "1001110", "1010000", "1000100", "1001000", "1110100"};

    strcpy(barras, "101"); // marcador inicial

    // L-code para os 4 primeiros dígitos
    for (int i = 0; i < 4; i++)
    {
        strcat(barras, L_code[id[i] - '0']);
    }

    strcat(barras, "01010"); // Marcador central

    // R-code para os 4 últimos dígitos
    for (int i = 4; i < 8; i++)
    {
        strcat(barras, R_code[id[i] - '0']);
    }

    strcat(barras, "101"); // Marcador final
}
