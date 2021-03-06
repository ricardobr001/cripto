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

unsigned int descobreChave(unsigned int original, unsigned int cifrado);
void descobreValorTransferido(unsigned int chave, unsigned int cifrado, unsigned int conta, unsigned int agencia);

int main()
{
    // int = 4 bytes = 32 bits
    unsigned int original, cifrado, chave, conta, agencia, msgCapturadas, i;

    scanf("%u", &original);
    scanf("%u", &cifrado);

    chave = descobreChave(original, cifrado); // Descobrindo a chave

    // 1111 0000 0000 0000 0000 0000 0000 0000 = F0000000 (nossa máscara para extrair os primeiros 4 bits)
    //  F    0    0    0    0    0    0    0
    conta = original & 0xF0000000;
    // 0000 1111 0000 0000 0000 0000 0000 0000 = 0F000000 (nossa máscara para extrair os bits 4 a 8)
    agencia = original & 0x0F000000;

    scanf("%u", &msgCapturadas);

    for (i = 0 ; i < msgCapturadas ; i++)
    {
        scanf("%u", &cifrado);
        descobreValorTransferido(chave, cifrado, conta, agencia);   // Somando o valor transferido
    }

    return 0;
}

/* Função que faz a função inversa do XOR, com o texto original e o texto cifrado (a inversa do XOR é o próprio XOR) */
unsigned int descobreChave(unsigned int original, unsigned int cifrado)
{    
    return original ^ cifrado;
}

/* Função que verifica se a conta de origem e destino são a mesma da transfeência não cifrada */
void descobreValorTransferido(unsigned int chave, unsigned int cifrado, unsigned int conta, unsigned int agencia)
{

    int aux = chave ^ cifrado; // XOR para descobrir a verdadeira quantia transferida

    // Caso forem da mesa agência e conta, imprime o valor transferido
    if (((aux & 0xF0000000) == conta) && ((aux & 0x0F000000) == agencia))
    {
        // 0000FFFF = 0000 0000 0000 0000 1111 1111 1111 1111 (nossa máscara para extrair os últimos 16 bits)
        printf("%u\n", aux & 0x0000FFFF);
    }
}