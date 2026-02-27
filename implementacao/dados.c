#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "logs.h"

void pesquisarAnimal(char *usuario)
{
    int idBusca;
    printf("Digite o ID que deseja pesquisar: ");
    scanf("%d", &idBusca);

    FILE *arquivo = fopen("../dados/base.csv", "r");
    FILE *saida = fopen("../saida/saida.csv", "w");

    if (arquivo == NULL || saida == NULL)
    {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    Animal animal;

    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        sscanf(linha, "%d,%49[^,],%49[^,],%d",
               &animal.id,
               animal.nome,
               animal.especie,
               &animal.idade);

        if (animal.id == idBusca)
        {
            encontrado = 1;

            printf("\nRegistro encontrado:\n");
            printf("ID: %d | Nome: %s | Especie: %s | Idade: %d\n\n",
                   animal.id,
                   animal.nome,
                   animal.especie,
                   animal.idade);

            fprintf(saida, "ID: %d | Nome: %s | Especie: %s | Idade: %d\n\n",
                    animal.id,
                    animal.nome,
                    animal.especie,
                    animal.idade);
        }
    }

    if (!encontrado)
    {
        printf("\nRegistro nao encontrado.\n\n");
        fprintf(saida, "Registro nao encontrado para ID %d\n", idBusca);
    }

    fclose(arquivo);
    fclose(saida);

    char logMsg[100];
    sprintf(logMsg, "PESQUISOU_ID_%d", idBusca);
    registrarLog(usuario, logMsg);
    
}

void removerAnimal(char *usuario)
{
    int idRemover;
    printf("Digite o ID do animal que deseja remover: ");
    scanf("%d", &idRemover);

    FILE *arquivo = fopen("../dados/base.csv", "r");
    FILE *temp = fopen("../dados/temp.csv", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("\nErro ao abrir arquivos.\n");
        return;
    }

    Animal animal;
    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        sscanf(linha, "%d,%49[^,],%49[^,],%d",
               &animal.id,
               animal.nome,
               animal.especie,
               &animal.idade);

        if (animal.id == idRemover)
        {
            encontrado = 1;
        }
        else
        {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("../dados/base.csv");
    rename("../dados/temp.csv", "../dados/base.csv");

    if (encontrado)
    {
        registrarLog(usuario, "REMOVEU_ANIMAL");
        printf("\nAnimal removido com sucesso!\n\n");
    }
    else
    {
        printf("\nID nao encontrado.\n\n");
    }
}

void editarAnimal(char *usuario)
{
    int idEditar;
    printf("Digite o ID do animal que deseja editar: ");
    scanf("%d", &idEditar);

    FILE *arquivo = fopen("../dados/base.csv", "r");
    FILE *temp = fopen("../dados/temp.csv", "w");

    if (arquivo == NULL || temp == NULL)
    {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    Animal animal;
    char linha[200];
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), arquivo))
    {

        sscanf(linha, "%d,%49[^,],%49[^,],%d",
               &animal.id,
               animal.nome,
               animal.especie,
               &animal.idade);

        if (animal.id == idEditar)
        {

            encontrado = 1;

            while (getchar() != '\n')
                ;

            printf("Novo nome: ");
            fgets(animal.nome, sizeof(animal.nome), stdin);
            animal.nome[strcspn(animal.nome, "\n")] = '\0';

            printf("Nova especie: ");
            fgets(animal.especie, sizeof(animal.especie), stdin);
            animal.especie[strcspn(animal.especie, "\n")] = '\0';

            int valido = 0;

            while (!valido)
            {
                printf("Nova idade: ");
                if (scanf("%d", &animal.idade) != 1)
                {
                    printf("Entrada invalida. Digite um numero.\n");
                    while (getchar() != '\n')
                        ;
                }
                else if (animal.idade < 0)
                {
                    printf("Idade nao pode ser negativa.\n");
                }
                else
                {
                    valido = 1;
                }
            }

            fprintf(temp, "%d,%s,%s,%d\n",
                    animal.id, animal.nome, animal.especie, animal.idade);
        }
        else
        {
            fprintf(temp, "%s", linha);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("../dados/base.csv");
    rename("../dados/temp.csv", "../dados/base.csv");

    if (encontrado)
    {
        registrarLog(usuario, "EDITOU_ANIMAL");
        printf("\nAnimal editado com sucesso!\n\n");
    }
    else
    {
        printf("\nID nao encontrado.\n\n");
    }
}

int gerarProximoId()
{
    FILE *arquivo = fopen("../dados/base.csv", "r");

    if (arquivo == NULL)
    {
        return 1;
    }

    char linha[200];
    int maiorId = 0;
    int id;

    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (sscanf(linha, "%d,", &id) == 1)
        {
            if (id > maiorId)
            {
                maiorId = id;
            }
        }
    }

    fclose(arquivo);

    return maiorId + 1;
}

void cadastrarAnimais(char *usuario)
{

    FILE *arquivo = fopen("../dados/base.csv", "a");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir base.csv\n");
        return;
    }

    Animal animal;

    while (getchar() != '\n')
        ;

    printf("Qual o nome do animal? ");
    fgets(animal.nome, sizeof(animal.nome), stdin);
    animal.nome[strcspn(animal.nome, "\n")] = '\0';

    printf("Qual a especie do animal? ");
    fgets(animal.especie, sizeof(animal.especie), stdin);
    animal.especie[strcspn(animal.especie, "\n")] = '\0';

    int valido = 0;

    while (!valido)
    {
        printf("Qual a idade do animal? ");

        if (scanf("%d", &animal.idade) != 1)
        {
            printf("Entrada invalida. Digite um numero.\n");
            while (getchar() != '\n')
                ;
        }
        else if (animal.idade < 0)
        {
            printf("Idade nao pode ser negativa.\n");
        }
        else
        {
            valido = 1;
        }
    }

    animal.id = gerarProximoId();

    fprintf(arquivo, "%d,%s,%s,%d\n",
            animal.id,
            animal.nome,
            animal.especie,
            animal.idade);
    fclose(arquivo);

    registrarLog(usuario, "CADASTROU_ANIMAL");

    printf("\nAnimal cadastrado com sucesso!\n\n");
}

void listarAnimais(char *usuario)
{
    FILE *arquivo = fopen("../dados/base.csv", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir base.csv\n");
        return;
    }

    Animal animal;
    char linha[200];

    printf("\n=== LISTA DE ANIMAIS ===\n\n");

    while (fgets(linha, sizeof(linha), arquivo))
    {
        sscanf(linha, "%d,%49[^,],%49[^,],%d",
               &animal.id,
               animal.nome,
               animal.especie,
               &animal.idade);

        printf("ID: %d\n", animal.id);
        printf("Nome: %s\n", animal.nome);
        printf("Especie: %s\n", animal.especie);
        printf("Idade: %d anos\n\n", animal.idade);
    }

    fclose(arquivo);
    printf("\n");
    registrarLog(usuario, "LISTOU_ANIMAIS");
}
