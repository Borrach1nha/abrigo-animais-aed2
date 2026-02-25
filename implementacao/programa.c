#include <stdio.h>
#include "autenticacao.h"

int main() {
    char usuario[50];
    int autenticado = 0;

    printf("=== SISTEMA DE ABRIGO DE ANIMAIS ===\n");

    while (!autenticado) {
        autenticado = autenticar(usuario);
    }

    return 0;
}