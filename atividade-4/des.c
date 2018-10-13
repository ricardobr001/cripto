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

int permutacao_inicial[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int permutacao_um[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

int permutacao_dois[48] = {
    14, 17, 11, 24,  1,  5,  3, 28,
    15,  6, 21, 10, 23, 19, 12,  4,
    26,  8, 16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

int circular_shift[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

int tabela_expansao[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};

unsigned long long int permutacaoInicial(unsigned long long int entrada);
unsigned long long int permutacaoUm(unsigned long long int chave);
unsigned long long int shiftCircular(unsigned long long int chave, int shift);
unsigned long long int expansao(unsigned long long int texto);
unsigned long long int permutacaoDois(unsigned long long int chave);

int main()
{
    unsigned long long int entrada = 0x696E74726F647563, chave = 0x3132333435363738;
    unsigned long long int entradaPermutada, chavePermutada, res, aux1, aux2, auxLeft, auxRight;
    unsigned long long int maskLeft = 0x00fffffff0000000, maskRight = 0x000000000fffffff;
    int i;

    // Permutação inicial da entrada e permutação um da chave
    entradaPermutada = permutacaoInicial(entrada); // 64-bit
    chavePermutada = permutacaoUm(chave); // 56-bit

    // printf("%012llx\n", expansao(entradaPermutada));

    res = shiftCircular(chavePermutada, circular_shift[0]);
    printf("chave (56-bit): %014llx\n", res);
    printf("chave (48-bit): %014llx\n", permutacaoDois(res));
    // for (i = 1 ; i < 16 ; i++)
    // {
    //     res = shiftCircular(res, circular_shift[i]);
    //     printf("%014llx\n", res);
    // }

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
        res = res | ((entrada >> (64 - permutacao_inicial[i])) & mask);

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

/* Função que faz a permutação um da chave, retorna chave permutada de 56-bit */
unsigned long long int permutacaoUm(unsigned long long int chave)
{
    int i;
    unsigned long long int res = 0, mask = 1;

    // Laço que percorre a tabela de permutação um (56-bit)
    for (i = 0 ; i < 56 ; i++)
    {
        // Mesmo raciocínio utilizado da função (permutacaoInicial) para recuperar os 56-bit de interesse
        // A chave possui 64-bit, precisamos subtrair 64 para efetuar o shift corretamente
        res = res | ((chave >> (64 - permutacao_um[i])) & mask);

        if (i != 55)
        {
            res = res << 1;
        }
    }

    return res;
}

/* 
 * Função que faz o shift circular da chave de 56-bit
 * Separa a chave em duas partes de 28-bit e faz o shift de cada parte
 * Retorna a nova chave de 56-bit
 */
unsigned long long int shiftCircular(unsigned long long int chave, int shift)
{
    unsigned long long int maskLeft = 0x00fffffff0000000, maskRight = 0x000000000fffffff;
    unsigned long long int auxLeft, auxRight;

    auxLeft = chave & maskLeft;    // 0000fff0000000 (28-bit esquerda)
    auxRight = chave & maskRight;  // 0000000667880f (28-bit direita)

    // Shift circular
    auxLeft = ((auxLeft << shift) | (auxLeft >> (27 - (shift - 1)))) & maskLeft;
    auxRight = ((auxRight << shift) | (auxRight >> (27 - (shift - 1)))) & maskRight;

    return auxLeft | auxRight;
}

/* 
 * Função que faz a expansão do texto, de 32-bit para 48-bit
 * A função pode receber um texto de 64-bit
 * Porém só ira fazer a expansão dos 32-bit da direita
 * Retorna o texto da direita expandido para 48-bit
 */
unsigned long long int expansao(unsigned long long int texto)
{
    int i;
    unsigned long long int res = 0, mask = 1;

    // Laço que percorre a tabela de expansão (48-bit)
    for (i = 0 ; i < 48 ; i++)
    {
        res = res | ((texto >> (32 - tabela_expansao[i])) & mask);

        if (i != 47)
        {
            res = res << 1;
        }
    }

    return res;
}

/* 
 * Função que faz a redução da chave, de 56-bit para 48-bit
 * A função recebe uma chave de 56-bit
 * Retorna a chave reduzida de 48-bit
 */
unsigned long long int permutacaoDois(unsigned long long int chave)
{
    int i;
    unsigned long long int res = 0, mask = 1;

    // Laço que percorre a tabela permutação dois (48-bit)
    for (i = 0 ; i < 48 ; i++)
    {
        // Aqui a chave possui 56-bit
        res = res | ((chave >> (56 - permutacao_dois[i])) & mask);

        if (i != 47)
        {
            res = res << 1;
        }
    }

    return res;
}