/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 04 - DES
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * Aluno: Lucas Alexandre Occaso        RA: 620505
 * ========================================================================== */

#include <stdio.h>

int permutacao_inicial[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
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

int S_box[8][4][16] = {
    {
        //S1
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
        0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
        4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
    },
    {
        //S2
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
        3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
        0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
    },
    {
        //S3
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
        1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
    },
    {
        //S4
        7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
        3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
    },
    {
        //S5
        2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
        4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
    },
    {
        //S6
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
        9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
        4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
    },{
        //S7
        4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
        1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
        6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
    },
    {
        //S8
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
        1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
        7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
        2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
    }
};

int tabela_permutacao_p[32] = {
    16,  7, 20, 21, 29, 12, 28, 17,
     1, 15, 23, 26,  5, 18, 31, 10,
     2,  8, 24, 14, 32, 27,  3,  9,
    19, 13, 30,  6, 22, 11,  4, 25
};

int permutacao_final[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

unsigned long long int permutacaoInicial(unsigned long long int entrada);
unsigned long long int permutacaoUm(unsigned long long int chave);
unsigned long long int shiftCircular(unsigned long long int chave, int shift);
unsigned long long int expansao(unsigned long long int texto);
unsigned long long int permutacaoDois(unsigned long long int chave);
unsigned long long int substituicaoSBOX(unsigned long long int valor);
unsigned long long int permutacaoP(unsigned long long int valor);
unsigned long long int permutacaoFinal(unsigned long long int valor);

int main()
{
    unsigned long long int entrada = 0x696E74726F647563, chave = 0x3132333435363738; // Teste
    unsigned long long int entradaPermutada, chavePermutada,
    // Auxiliares
    auxChaveShift, auxChavePermDois, auxExpansao, auxXOR, auxLeft, auxRight, auxSBox, auxPermP, resDir, res,
    // Mascaras para salvar os 32-bit esq e 32-bit dir
    maskLeft = 0xffffffff00000000, maskRight = 0x00000000ffffffff;
    int i;

    // Lendo a entrada e chave
    // scanf("%llx", &entrada);
    // scanf("%llx", &chave);

    // Permutação inicial da entrada e permutação um da chave
    entradaPermutada = permutacaoInicial(entrada); // 64-bit
    printf("PLAIN TEXT: %016llx\n", entrada);
    printf("IP: %016llx\n\n", entradaPermutada);

    chavePermutada = permutacaoUm(chave); // 56-bit
    printf("CHAVE: %016llx\n", chave);
    printf("PC1: %014llx\n\n", chavePermutada);

    // Copiando a entrada permutada para o res para usar o valor correto na primeira iteração
    res = entradaPermutada;
    auxChaveShift = chavePermutada; // O mesmo vale para a chave permutada


    for (i = 0 ; i < 16 ; i++)
    {
        printf("CHAVE DE ROUND %d\n", i+1);
        // Preparando a chave para o XOR com o texto permutado
        auxChaveShift = shiftCircular(auxChaveShift, circular_shift[i]); // Shift Circular da chave (primeira vez)
        printf("DESLOCAMENTO: %014llx\n", auxChaveShift);

        auxChavePermDois = permutacaoDois(auxChaveShift); // Permutação dois da chave após o shift (primeira vez)
        printf("PC2: %012llx\n\n", auxChavePermDois);

        // Antes de efetuar a expansão, devemos salvar os 32-bit da direita em uma variavél auxiliar
        auxLeft = res & maskLeft;
        auxRight = res & maskRight;

        printf("ROUND %d\n", i+1);
        // Preparando o texto permutado para o XOR com a chave
        printf("%016llx\n", res);
        auxExpansao = expansao(res); // Expansao da entrada permutada (primeira vez)
        printf("EXPANCAO: %012llx\n", auxExpansao);

        // XOR do texto permutado com a chave perm 2 (primeira vez -> 48-bit)
        auxXOR = auxExpansao ^ auxChavePermDois;
        printf("ADD KEY: %012llx\n", auxXOR);

        // Após o XOR, fazer a substituição utilizando a sBox
        auxSBox = substituicaoSBOX(auxXOR);
        printf("S-BOX: %08llx\n", auxSBox);

        // Após a substituição, fazer a permutação P
        auxPermP = permutacaoP(auxSBox);
        printf("PERM P: %08llx\n", auxPermP);

        // Agora devemos fazer o XOR entre o auxLeft e o auxRight (MODIFICADO)
        resDir = (auxLeft >> 32) ^ auxPermP;
        printf("ADD LEFT: %08llx\n", resDir);

        // Salvamos os 32-bit da direita na auxLeft
        auxLeft = auxRight << 32;

        // E salvamos os 64-bit, 32-bit da auxLeft e 32-bit da resDir na variavel res
        res = auxLeft | resDir;
        printf("%016llx\n\n", res);
    }

    // Após os 16 rounds, precisamos trocar os 32-bit da esquerda com os 32-bit da direita
    // Recuperando os 32-bit da esquerda e da direita
    auxLeft = res & maskLeft;
    auxRight = res & maskRight;

    resDir = auxRight;
    auxRight = auxLeft >> 32;
    auxLeft = resDir << 32;

    res = auxLeft | auxRight;
    printf("SWAP: %016llx\n\n", res);

    // Para finalizar, fazemos a pemutação final (permutação inicial inversa)
    res = permutacaoFinal(res);
    printf("IP INVERSO: %016llx\n", res);

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

/*
 * Função que faz a permutação um da chave,
 * Recebe a chave de 64-bit
 * Retorna chave permutada de 56-bit
 */
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
        // Aqui o texto possui 32-bit
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

/*
 * Função que faz a redução/substituição do texto da direita após o XOR, de 48-bit para 32-bit
 * A função recebe um valor de 48-bit
 * Retorna um valor reduzido de 32-bit
 */
unsigned long long int substituicaoSBOX(unsigned long long int valor)
{
    int i, j;
    unsigned long long int res = 0, aux, linha, coluna, mask = 0x000000000000003f; // (... 0011 1111) 6 bits de interesse

    for (i = 0 ; i < 8 ; i++)
    {
        // Salva na aux os 6 bits de interesse de cada s-box (0 até 7)
        aux = (valor >> ((7 - i) * 6)) & mask;

        // Recupera a linha da sbox que queremos utilizar
        // (110 110) >> 4 -> (000 010)
        // (000 010) AND (000 010) -> (000 010)     // (110 110) AND (000 001) -> (000 000)
        // (000 010) OR (000 000) -> (000 010)
        linha = ((aux >> 4) & 2) | (aux & 1);

        // Recuperando a coluna
        // (110 110) AND (011 110) -> (010 110)
        // (010 110) >> 1 -> (001 011)
        coluna = (aux & 0x1e) >> 1;

        res = res | S_box[i][linha][coluna];

        if (i != 7)
        {
            res = res << 4;
        }

        // Testes
        // printf("num - ");
        // for (j = 0 ; j < 6 ; j++)
        //     printf("%lld", (linha >> j) & 1);
        // printf("\n");

        // printf("num - ");
        // for (j = 0 ; j < 6 ; j++)
        //     printf("%lld", (aux >> j) & 1);
        // printf("\taux - %2llx   linha - %llx  coluna - %lld\n\n", aux, linha, coluna);
    }

    return res;
}

/*
 * Função que faz a permutação final do texto da direita após a substituicão da S-BOX
 * A função recebe um valor de 32-bit
 * Retorna um valor permutado de 32-bit
 */
unsigned long long int permutacaoP(unsigned long long int valor)
{
    int i;
    unsigned long long int res = 0, mask = 1;

    // Laço que percorre a tabela permutação dois (32-bit)
    for (i = 0 ; i < 32 ; i++)
    {
        // Aqui a variável (valor) possui 32-bit
        res = res | ((valor >> (32 - tabela_permutacao_p[i])) & mask);

        if (i != 31)
        {
            res = res << 1;
        }
    }

    return res;
}

/*
 * Função que faz a permutação final do texto (permutação inicial inversa)
 * A função recebe um valor de 64-bit
 * Retorna um valor permutado de 64-bit
 */
unsigned long long int permutacaoFinal(unsigned long long int valor)
{
    int i;
    unsigned long long int res = 0, mask = 1;

    // Laço que percorre a tabela de permutação final (64-bit)
    for (i = 0 ; i < 64 ; i++)
    {
        // Aqui a variável (valor) possui 64-bit
        res = res | ((valor >> (64 - permutacao_final[i])) & mask);

        if (i != 63)
        {
            res = res << 1;
        }
    }

    return res;
}
