/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Algoritmo ecc (Euclidean Extended)
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * ========================================================================== */

#include <stdio.h>

long long int gcd(long long int x, long long int n);
long long int inv(long long int a, long long int n);

int main()
{
    long long int x, n, res, i;

    scanf("%lld %lld", &x, &n);

    res = gcd(x, n);
    i = inv(x, n);

    if (i == -1)
    {
        printf("%lld N\n", res);
    }
    else
    {
        printf("%lld %lld\n", res, i);
    }

    return 0;
}

long long int gcd(long long int x, long long int n)
{
    while (x != n)
    {
        if (x > n)
        {
            x -= n;
        }
        else
        {
            n -= x;
        }
    }

    return x;
}

long long int inv(long long int x, long long int n)
{
    long long int t = 0, novoT = 1, r = n, novoR = x, q, aux;

    while(novoR != 0)
    {
        q = r / novoR;
        aux = t;
        t = novoT;
        novoT = aux - q * novoT;
        aux = r;
        r = novoR;
        novoR = aux - q * novoR;
    }

    if(r > 1)
    {
        return -1;
    }
    else
    {
        if (t < 0)
        {
            return t + n;
        }
        
        return t;
    }
}