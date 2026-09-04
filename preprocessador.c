#include <stdio.h>
#include "preprocessador.h"

void preprocessar(const char *entrada, const char *saida) { //inicio da função que vai pegar o arquivo de entrada e saída.
    FILE *in = fopen(entrada, "r"); //abre o arquivo de entrada para leitura.
    FILE *out = fopen(saida, "w"); //abre o arquivo de saída para escrita. 

    if (!in || !out) {
        printf("Erro ao abrir os arquivos.\n");// verifica se algum dos arquivos deu algum erro na hora de abrir e executa o return.
        return;
    }

    char linha[256];// vetor para guardar o texto da linha original.

    while (fgets(linha, sizeof(linha), in)) { //Lê o arquivo linha por linha perfeitamente.
        char limpa[256]; //Char para armazenar a linha limpa
        int i = 0, j = 0, espaco = 0; // I = leitor da linha original, J = escritor na linha nova (limpa), espaco = 0: Funciona como uma chave liga/desliga. Se for 0, significa "o último caractere não foi um espaço". Se for 1, significa "o último caractere foi um espaço".

        // Ignores espaços e tabs do início
        while (linha[i] == ' ' || linha[i] == '\t') i++; //Ou seja se ele encontra ' ' ou "\t" aumenta o valor de i, não ecrevendo nada na linha limpa, ignorando os espaços em branco.

        // Processa caractere por caractere
        while (linha[i] != '\0' && linha[i] != '\n' && linha[i] != '#') { //O programa processa a linha caractere por caractere e continua apenas enquanto não achar: \0, \n, #. Ao encontrar o #, o laço encerra na hora, descartando o comentário e tudo o que estivesse à direita dele.
            if (linha[i] == ' ' || linha[i] == '\t') {
                if (!espaco) {
                    limpa[j++] = ' ';//alva um único espaço na linha limpa (limpa[j++] = ' ') e liga a chave (espaco = 1).
                    espaco = 1;
                }//Se encontrar um caractere normal (letra, número, símbolo):
            } else {
                limpa[j++] = linha[i]; // desliga a chave de espaço (espaco = 0).
                espaco = 0;
            }
            i++;
        }

        // Remove espaço sobressalente do fim
        if (j > 0 && limpa[j - 1] == ' ') j--;

        limpa[j] = '\0';

        // Salva se a linha não ficou vazia
        if (j > 0) fprintf(out, "%s\n", limpa);
    }

    fclose(in);
    fclose(out);
}