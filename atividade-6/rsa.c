/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 06 - RSA usando lib GMP
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * ========================================================================== */

#include <stdio.h>
#include <gmp.h> // brew install gmp
// gcc rsa.c -lgmp -o rsa

int main()
{
    mpz_t var;

    printf("size= %ld\n", sizeof(mpz_t)); // 16 bytes -- 128 BIT
    gmp_printf("VAR: %Zx\n", var);
    mpz_init(var);
    gmp_printf("VAR: %Zx\n", var);

    return 0;
}