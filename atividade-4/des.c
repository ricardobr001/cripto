/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 04 - DES
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * Aluno: Lucas Alexandre Occaso        RA: 
 * ========================================================================== */

#include <stdio.h>
#include <string.h>

int tabela_permutacao_inicial[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int tabela_expansao[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

unsigned long long int permutacaoInicial(unsigned long long int entrada);

int main()
{
    unsigned long long int entrada = 0x696E74726F647563;
    unsigned long long int permutado;

    permutado = permutacaoInicial(entrada);

    printf("%llx\n", permutado);

    return 0;
}

/* Função que faz a permutação inicial da entrada */
unsigned long long int permutacaoInicial(unsigned long long int entrada)
{
    int i;
    unsigned long long int res = 0, mask = 1;

    // Laço que percorre a tabela de permutação inicial (64-bit)
    for (i = 0 ; i < 64 ; i++)
    {
        // Salvando no res o bit de interesse, além do restante a sua esquerda
        // Ex: Supondo 8-bit (0011 1100) queremos pegar o bit na posição 4 
        // (numero >> (8 - 4)) = (0000 0011)
        // Após o shift, temos que pegar o último valor, para isso utilizamos a mascara
        // (0000 0011) & (0000 0001) = (0000 0001)
        res = res | ((entrada >> (64 - tabela_permutacao_inicial[i])) & mask);

        // Após salvarmos o bit na variavel res, precisamos dar um << de 1 posição para a esquerda
        // Para não ocorrer sobreescrita do valor recuperado
        // Não precisamos empurrar os bits na última iteração, se não perderemos 1-bit de interesse (o primeiro bit recuperado)
        if (i != 63)
        {
            res = res << 1;
        }
    }

    return res;
}