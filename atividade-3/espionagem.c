/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 03 - Espionagem
 *
 * RA: 562262
 * Aluno: Ricardo Mendes Leal Junior
 * ========================================================================== */

// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void stringParaInt(int *vetInt, char *vetChar);
void descobreChave(int *original, int *cifrado, int *chave);
int descobreValorTransferido(int *chave, int *cifrado);

int main()
{
    // int = 4 bytes
    int numerosOriginal[5], numerosCifrado[5], chave[5], msgCapturadas, i, total = 0;
    char entrada[11], cifrado[11];

    scanf("%[^\n]s", entrada);
    scanf("\n%[^\n]s", cifrado);

    stringParaInt(numerosOriginal, entrada); // Transformando a entrada para int
    stringParaInt(numerosCifrado, cifrado); // Transformando a entrada cifrada para int
    descobreChave(numerosOriginal, numerosCifrado, chave); // Descobrindo a chave

    scanf("%d", &msgCapturadas);

    for (i = 0 ; i < msgCapturadas ; i++)
    {
        scanf("\n%[^\n]s", cifrado);
        stringParaInt(numerosCifrado, cifrado); // Transformando a entrada cifrada para int
        total += descobreValorTransferido(chave, numerosCifrado);   // Somando o valor transferido
    }

    printf("%d\n", total);

    return 0;
}

/* Função que trata a entrada, transformando a string lida para int */
void stringParaInt(int *vetInt, char *vetChar)
{
    char aux[3];
    int i, j;

    for (i = 0, j = 0 ; i < 10 ; i += 2, j++)
    {
        strncpy(aux, &vetChar[i], 2); // Copiando os dois bytes do vetChar para aux a partir da posição i
        vetInt[j] = atoi(aux); // Salvando os números copiados para aux no vetInt como int
    }
}

/* Função que faz a função inversa do XOR, com a entrada e o texto cifrado (a inversa do XOR é o próprio XOR) */
void descobreChave(int *original, int *cifrado, int *chave)
{
    int i;

    // Laço que fará a inversa do XOR, fazendo o texto original XOR texto cifrado, teremos a chave
    for (i = 0 ; i < 5 ; i++)
    {
        chave[i] = original[i] ^ cifrado[i];
    }
}

/* Função que retorna o valor transferido, recebe a chave e a transação cifrada */
int descobreValorTransferido(int *chave, int *cifrado)
{
    return chave[4] ^ cifrado[4]; // XOR para descobrir a verdadeira quantia transferida
}