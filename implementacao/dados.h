#ifndef DADOS_H
#define DADOS_H

typedef struct {
    int id;
    char nome[50];
    char especie[50];
    int idade;
} Animal;

void cadastrarAnimais(char *usuario);
void listarAnimais(char *usuario);
void editarAnimal(char *usuario);
void removerAnimal(char *usuario);
void pesquisarAnimal(char *usuario);
int gerarProximoId();

#endif