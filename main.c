#include <stdio.h>
#include "preprocessador.h"

int main(int argc, char *argv[]) {
    // Valida se o usuário forneceu os argumentos corretos no terminal
    if (argc < 3) {
        printf("Uso correto: %s <arquivo_entrada.asm> <arquivo_saida.asm>\n", argv[0]);
        return 1;
    }

    // Executa o pré-processador usando os nomes passados na linha de comando
    preprocessar(argv[1], argv[2]);
    
    printf("Processamento concluido com sucesso!\n");
    return 0;
}