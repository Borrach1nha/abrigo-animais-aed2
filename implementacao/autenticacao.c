#include <stdio.h>
#include <string.h>
#include "autenticacao.h"
#include "logs.h"

int autenticar(char *usuario) {
    char login[50];
    char senha[50];
    char linha[100];
    char loginArquivo[50];
    char senhaArquivo[50];

    printf("Login: ");
    scanf("%49s", login);

    printf("Senha: ");
    scanf("%49s", senha);

    FILE *arquivo = fopen("../dados/usuarios.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir usuarios.csv\n");
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%49[^,],%49[^\n]", loginArquivo, senhaArquivo);

        if (strcmp(login, loginArquivo) == 0 &&
            strcmp(senha, senhaArquivo) == 0) {

            strcpy(usuario, login);
            fclose(arquivo);

            registrarLog(usuario, "LOGIN_SUCESSO");
            printf("Login realizado com sucesso!\n");
            return 1;
        }
    }

    fclose(arquivo);

    registrarLog(login, "LOGIN_FALHOU");
    printf("Login ou senha incorretos!\n");
 
    return 0;
}