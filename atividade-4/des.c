/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 03 - Espionagem
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * Aluno: Lucas Alexandre Occaso        RA: 
 * ========================================================================== */

#include <stdio.h>

void permutacao(char *v);

int main()
{
    char textoClaro[9], chave[9];

    scanf("%[^\n]s", textoClaro);
    scanf("\n%[^\n]s", chave);

    return 0;
}

void permutacao(char *v)
{
    int i, j, metadeBaixo = 4, metadeCima = 0;
    char auxChars[9] = {
        0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00,
        '\0'
    };
    char mask = 0x80; // 1000 0000
    char auxBitsMascara;

    // Laços que iram efetuar as trocas
    for (i = 0 ; i < 8 ; i++)
    {
         if (i % 2 == 0) // Se a coluna que estiver sendo copiada for par (0 -> 4), (2 -> 5), (4 -> 6), (6 -> 7)
        {
            for (j = 0 ; j < 8 ; j++){
                auxBitsMascara = v[j] & mask; // Recuperando o bit que nos interessa para efetuar o OR
                auxChars[i + metadeBaixo] = auxChars[i + metadeBaixo] | auxBitsMascara; // Efetuando o OR e salvando o bit na "matriz"
            }
            metadeBaixo++;
        }
        else // Caso contrário, é uma coluna impar (1 -> 0), (3 -> 1), (5 -> 2), (7 -> 3)
        {
            for (j = 0 ; j < 8 ; j++){
                auxBitsMascara = v[j] & mask; // Recuperando o bit que nos interessa para efetuar o OR
                auxChars[i + metadeCima] = auxChars[i + metadeCima] | auxBitsMascara; // Efetuando o OR e salvando o bit na "matriz"
            }
            metadeCima++;
        }

        mask = (mask >> 1); // Movendo o bit da mascara (1000 0000 -> 0100 0000)
    }

    // No final do laço teremos a "matriz" permutada na variavel auxChars
}