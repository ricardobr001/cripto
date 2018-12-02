/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 07 - ECC
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * Aluno: Matheus Augusto Thomas        RA: 
 * ========================================================================== */

#include <stdio.h>

typedef struct ponto
{
    long long int x, y;
} Ponto;

Ponto ecc(int n, long long int a, long long int p, Ponto g);
Ponto somaPontos(Ponto g);

int main()
{
    Ponto g, res;
    int n;
    long long int a, p;

    scanf("%d", &n);

    // Enquanto não ler 0, continua...
    while (n) 
    {
        scanf("%lld %lld %lld %lld", &a, &p, &g.x, &g.y);
        res = ecc(n, a, p, g);
        printf("%lld %lld\n", res.x, res.y);
        scanf("%d", &n);
    }
    
    return 0;
}

Ponto ecc(int n, long long int a, long long int p, Ponto g)
{
    int i;
    Ponto res = g;

    // Efetua a soma n vezes
    for (i = 0 ; i < n ; i++)
    {
        // res se torna o ponto g após a soma
        res = somaPontos(res);
    }

    return res;
}

Ponto somaPontos(Ponto g)
{
    long long int lambda;
    Ponto inf, q, r;
    inf.x = 0; inf.y = 0;

    // Primeiro é necessário calcular o lambda para encontrar o ponto q
}

