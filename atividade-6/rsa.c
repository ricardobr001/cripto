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

void cifraDecifra(mpz_t n, mpz_t e, mpz_t texto, mpz_t cifrado);

int main()
{
    int base;
    mpz_t n, e, d, texto, cifrado; // mpz_t é um array

    // Inicializa n, e, d, p, q setando 0
    mpz_inits(n, e, d, texto, cifrado, NULL);

    printf("Insira a base <10> ou <16>: ");
    scanf("%d", &base);

    if (base == 10)
    {
        printf("Insira o modulo: ");
        gmp_scanf("%Zd", n); // Lendo o modulo n
        printf("Insira o expoente: ");
        gmp_scanf("%Zd", d); // Lendo o expoente e
        printf("Insira o texto: ");
        gmp_scanf("%Zd", cifrado);

        cifraDecifra(n, d, cifrado, texto);
        gmp_printf("RES:\n%Zd\n", texto);
    }
    else if (base == 16)
    {
        printf("Insira o modulo: ");
        gmp_scanf("%Zx", n); // Lendo o modulo n
        printf("Insira o expoente: ");
        gmp_scanf("%Zx", d); // Lendo o expoente e
        printf("Insira o texto: ");
        gmp_scanf("%Zx", cifrado);

        cifraDecifra(n, d, cifrado, texto);
        gmp_printf("RES\n%Zx\n", texto);
    }
    else
    {
        printf("Favor escolher a base <10> ou <16>!!\n");
    }

    return 0;
}

/* Função que cifra o texto, recebe o modulo n e o expoente e */
void cifraDecifra(mpz_t n, mpz_t e, mpz_t texto, mpz_t cifrado)
{
    mpz_t res, mask, auxAnd;
    int i = 0;

    mpz_inits(res, mask, auxAnd, NULL); // Inicia as variaveis
    mpz_set_ui(mask, 1); // Seta o valor 1 na varivavel 'mask'

    // Retorna POSITIVO se e > 0
    // Retorna 0 se e == 0
    // Retorna NEGATIVO se e < 0
    if (!mpz_cmp_si(e,0)) // Se for 0
    {
        mpz_set_ui(cifrado, 1); // cifrado = 1
    }
    else
    {
        mpz_set_ui(res, 1); // Seta o valor 1 na variavel res

        // Enquanto o e não for 0, faz exponenciacao
        while (mpz_cmp_si(e, 0))
        {
            mpz_and(auxAnd, e, mask); // auxAnd = e & 1

            if (!mpz_cmp_si(auxAnd, 1)) // Se auxAnd == 1
            {
                mpz_mul(res, res, texto); // res = res * texto
                mpz_mod(res, res, n); // res = res % n
            }

            mpz_mul(texto, texto, texto); // texto = texto * texto
            mpz_mod(texto, texto, n); // texto = texto % n
            mpz_div_2exp(e, e, 1); // e = e >> 1
        }

        mpz_set(cifrado, res); // cifrado = res
    }    
}