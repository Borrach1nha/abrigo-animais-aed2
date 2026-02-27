#include <stdio.h>
#include "autenticacao.h"
#include "logs.h"
#include <string.h>
#include "dados.h"

void menuPrincipal(char *usuario)
{
    int opcao;

    do
    {
        printf("\n=== MENU PRINCIPAL ===\n");
        printf("\nUsuario: %s\n", usuario);
        printf("\n1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Editar\n");
        printf("4 - Remover\n");
        printf("5 - Pesquisar\n");
        printf("6 - Logout\n");
        printf("\nEscolha: ");

        if (scanf("%d", &opcao) != 1)
        {
            printf("Entrada invalida!\n");
            while (getchar() != '\n')
                ;
            continue;
        }

        switch (opcao)
        {
        case 1:
            cadastrarAnimais(usuario);
            break;
        case 2:
            listarAnimais(usuario);
            break;
        case 3:
            editarAnimal(usuario);
            break;
        case 4:
            removerAnimal(usuario);
            break;
        case 5:
            pesquisarAnimal(usuario);
            break;
        case 6:
            registrarLog(usuario, "LOGOUT");
            printf("Logout realizado.\n");
            break;
        default:
            printf("Opcao invalida!\n");
        }

    } while (opcao != 6);
}

int main()
{
    char usuario[50];
    int autenticado = 0;

    printf("=== SISTEMA DE ABRIGO DE ANIMAIS ===\n");

    while (!autenticado)
    {
        autenticado = autenticar(usuario);
    }

    menuPrincipal(usuario);

    return 0;
}