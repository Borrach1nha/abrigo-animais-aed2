#include <stdio.h>
#include "logs.h"

void registrarLog(char *usuario, const char *acao) {
    FILE *arquivo = fopen("../dados/logs.csv", "a");

    if (arquivo != NULL) {
        fprintf(arquivo, "%s,%s\n", usuario, acao);
        fclose(arquivo);
    }
}