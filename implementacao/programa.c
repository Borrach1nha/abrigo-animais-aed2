#include <stdio.h>
#include "autenticacao.h"
#include "logs.h"

int gerarProximoId() {
    FILE *arquivo = fopen("../dados/base.csv", "r");

    if (arquivo == NULL) {
        return 1; 
    }

    char linha[200];
    int maiorId = 0;
    int id;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (sscanf(linha, "%d,", &id) == 1) {
            if (id > maiorId) {
                maiorId = id;
            }
        }
    }

    fclose(arquivo);

    return maiorId + 1;
}

void cadastrarAnimais(char *usuario) {

    FILE *arquivo = fopen("../dados/base.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir base.csv\n");
        return;
    }

    char nome[50];
    char especie[50];
    int idade;

    printf("Qual o nome do animal? ");
    scanf("%49s", nome);
    printf("Qual a especie do animal? ");
    scanf("%49s", especie);
    printf("Qual a idade do animal? ");
    scanf("%d", &idade);

    int id = gerarProximoId();

    fprintf(arquivo, "%d,%s,%s,%d\n", id, nome, especie, idade);
    fclose(arquivo);

    registrarLog(usuario, "CADASTROU_ANIMAL");

    printf("Animal cadastrado com sucesso!\n");
}

void listarAnimais(char *usuario) {
    FILE *arquivo = fopen("../dados/base.csv", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir base.csv\n");
        return;
    }

    char linha[200];
    int id, idade;
    char nome[50], especie[50];

    printf("\n=== LISTA DE ANIMAIS ===\n");

    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d,%49[^,],%49[^,],%d",
               &id, nome, especie, &idade);

        printf("ID: %d\n", id);
        printf("Nome: %s\n", nome);
        printf("Especie: %s\n", especie);
        printf("Idade: %d anos\n", idade);
        printf("----------------------\n");
    }

    fclose(arquivo);
    registrarLog(usuario, "LISTOU_ANIMAIS");
}

void menuPrincipal(char *usuario) {
    int opcao;

    do {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("Usuario: %s\n", usuario);
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Editar\n");
        printf("4 - Remover\n");
        printf("5 - Logout\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while (getchar() != '\n');
            continue;
        }

        switch(opcao) {
            case 1:
                cadastrarAnimais(usuario);
                printf("\n");
                break;
            case 2:
                listarAnimais(usuario);
                printf("\n");
                break;
            case 3:
                printf("Editar...\n");
                break;
            case 4:
                printf("Remover...\n");
                break;
            case 5:
                registrarLog(usuario, "LOGOUT");
                printf("Logout realizado.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 5);
}

int main() {
    char usuario[50];
    int autenticado = 0;

    printf("=== SISTEMA DE ABRIGO DE ANIMAIS ===\n");

    while (!autenticado) {
        autenticado = autenticar(usuario);
    }

    menuPrincipal(usuario);

    return 0;
}