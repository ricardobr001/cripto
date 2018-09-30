/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 02 - RC4
 *
 * RA: 562262
 * Aluno: Ricardo Mendes Leal Junior
 * ========================================================================== */

// Bibliotecas
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void inicia(unsigned char *s, unsigned char *t, unsigned char *chave);
void troca(unsigned char *x, unsigned char *y);
void fluxo(unsigned char *s, unsigned char *mensagem, unsigned char *cifra);

int main()
{
    // char [-127 - 127]
    // unsigned char [0 - 255]
    unsigned char chave[257], mensagem[257], vetorS[256], vetorT[256], *string, textoCifrado[257];
    int i;

    scanf("%[^\n]s", mensagem);
    scanf("\n%[^\n]s", chave);

    // Precisamos gerar um chave do tamanho da mensagem, para ser possível fazer o XOR com a mensagem
    // e ser possível criptografar a mensagem
    // Para isso, usando a chave entrada pelo usuario, geramos uma chave do tamanho da mensagem
    // Agora com a chave de fluxo do tamanho mensagem, efetuamos mais algumas trocas e fazemos a operação
    // XOR com cada byte da mensagem com a nossa chave de fluxo

    // Para descriptografar a mensagem cifrada, fazemos a mesma coisa, invertendo, onde a mensagem será
    // Nosso texto cifrado, e a chave precisa ser a MESMA, se não a chave de fluxo gerada será diferente
    // Fazendo as operações teremos a mensagem de volta
    inicia(vetorS, vetorT, chave);
    fluxo(vetorS, mensagem, textoCifrado);

    printf("CRIPTOGRAFANDO!\n");
    printf("mensagem = '%s' (%d)\n", mensagem, strlen(mensagem));
    printf("cifra = '%s' (%d)\n", textoCifrado, strlen(textoCifrado));

    inicia(vetorS, vetorT, chave);
    fluxo(vetorS, textoCifrado, mensagem);

    printf("DESCRIPTOGRAFANDO!\n");
    printf("mensagem = '%s' (%d)\n", textoCifrado, strlen(mensagem));
    printf("cifra = '%s' (%d)\n", mensagem, strlen(textoCifrado));

    return 0;
}

/* Função que inicia os vetores i e t */
void inicia(unsigned char *s, unsigned char *t, unsigned char *chave)
{
    int i, j, tamanhoChave = strlen(chave);
    printf("tamanho chave = %d\n", tamanhoChave);

    // O vetor s receberá o valor de i na posição s[i]
    // Para facilitar, o vetor t, receberá na posição i o valor existente na posição (i % tamanho da chave) da chave
    for (i = 0 ; i < 255 ; i++)
    {
        s[i] = i;
        t[i] = chave[i % tamanhoChave];
    }

    // Neste laço ocorre a troca das posições no vetor s
    // Calculamos a posição j, onde o valor existente na posição i, será trocado com o valor existente na posição j
    for (i = 0, j = 0 ; i < 255 ; i++)
    {
        j = (j + s[i] + t[i]) % 256;
        troca(&s[i], &s[j]);
    }

    // Agora temos o vetor S, trocado, com tamanho de 256 bytes e com as trocas feitas baseadas na chave do usuario
}

/* Função que troca o valor de uma variavel com outra */
void troca(unsigned char *x, unsigned char *y)
{
    unsigned char temp = *x;
    *y = *x;
    *y = temp;
}

/* Função que faz o XOR, para cada byte da mensagem */
void fluxo(unsigned char *s, unsigned char *mensagem, unsigned char *cifra)
{
    int i, j, k, t, tam = strlen(mensagem);

    for (i = 0, j = 0, k = 0 ; k < tam ; k++)
    {
        i = (i + 1) % 256;  // Calculando a posição de i
        j = (j + s[i]) % 256; // Calculando a posição de j
        troca(&s[i], &s[j]); // Efetuando a troca
        t = (s[i] + s[j]) % 256; // Calculando a posição t
        cifra[k] = mensagem[k] ^ s[t]; // XOR do byte k da mensagem com o byte t da chave de fluxo
    }

    cifra[tam] = '\0';
}