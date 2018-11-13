/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 05 - Quebra RSA
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * ========================================================================== */

#include <stdio.h>

unsigned long long int phi(unsigned long long int p, unsigned long long int q);
void breakRSA(unsigned long long int produtoPrimos, unsigned long long int chavePub, unsigned long long int mensagem);
unsigned long long int inversoModular(unsigned long long int a, unsigned long long int b);
unsigned long long int eleva(unsigned long long int a, unsigned long long int b, unsigned long long int mod);
unsigned long long int elevaDois(int vezes);
unsigned long long int elevaReal(unsigned long long int a, unsigned long long int n);

// http://mathforum.org/library/drmath/view/65801.html <- encontrando o primo
unsigned long long int x(unsigned long long int numero, unsigned long long int N);
unsigned long long int d(unsigned long long int numero, unsigned long long int N);
unsigned long long int gcd(unsigned long long int a, unsigned long long int b);

int main()
{
    unsigned long long int n, e, c;

    scanf("%lld %lld %lld", &n, &e, &c);

    breakRSA(n, e, c);

    return 0;
}

unsigned long long int phi(unsigned long long int p, unsigned long long int q)
{
    return (p - 1) * (q - 1);
}

void breakRSA(unsigned long long int produtoPrimos, unsigned long long int chavePub, unsigned long long int mensagem)
{
    unsigned long long int i = 1, primeiroPrimo, segundoPrimo, resPhi, chavePriv;

    primeiroPrimo = d(i, produtoPrimos);

    while(1)
    {
        i++;
        // Se o resultado de d(), estiver entre 1 e o produto primo, ele é o primeiro primo
        if (1 < primeiroPrimo && primeiroPrimo < produtoPrimos)
        {
            break;
        }
        // Se nao, não encontrou o primo e procura de novo incrementando o i
        else
        {
            primeiroPrimo = d(i, produtoPrimos);
        }
    }

    // Para encontrar o segundo primo, basta dividir o produto dos primos pelo primeiro primo, assim teremos o segundo
    segundoPrimo = produtoPrimos / primeiroPrimo;
    resPhi = phi(primeiroPrimo, segundoPrimo);
    chavePriv = inversoModular(chavePub, resPhi);

    printf("primo 1 = %lld\tprimo 2 = %lld\n", primeiroPrimo, segundoPrimo);
    printf("totien = %lld\n", resPhi);

    printf("%lld\n", eleva(mensagem, chavePriv, produtoPrimos));
    // printf("%lld\n", )
    

}

unsigned long long int inversoModular(unsigned long long int a, unsigned long long int p)
{
    unsigned long long int novo = 1, velho = 0, q = p, r, h;
    unsigned long long int pos = 0;

    while (a > 0)
    {
        r = q % a;
        q = q / a;
        h = q * novo + velho;
        velho = novo;
        novo = h;
        q = a;
        a = r;
        pos = !pos;
    }
    // if (pos)
    // {
    //     printf("%d N\n", q);
    // }
    // else
    // {
    //     printf("%d %d\n", q, (p - velho));
    // }

    return (p - velho);
}

unsigned long long int eleva(unsigned long long int a, unsigned long long int b, unsigned long long int mod)
{
    unsigned long long int i;
    unsigned long long int res = a, aux;
    // int i, mask = 1;

    printf("m = %lld, priv = %lld, mod = %lld\n", a, b, mod);


    if (b == 0)
    {
        return 1;
    }

    for (i = 1 ; i < b ; i++)
    {
        // printf("res = %llu\n", res);
        res = res * a;
        res = res % mod;
    }

    // printf("i = %lld\n", i);

    // for (i = 0 ; i < 64 ; i++)
    // {
    //     aux = (b >> i) & 1;

    //     if (aux)
    //     {
    //         // printf("pow(2,%d) = %lld\n", i, elevaDois(i));
    //         printf("pow(%lld,%lld)=%lld, mod %lld = %lld\n", a, elevaDois(i), elevaReal(a, elevaDois(i)), mod, elevaReal(a, elevaDois(i)) %mod);
    //         // 436 ^ 8 > 2^64 -- overflow!
    //         res = res * elevaReal(a, elevaDois(i));
    //         res = res % mod;
    //     }
    // }

    // for (i = 1 ; i < b ; i++)
    // {
    //     res = res * a;
    // }
    return res;
}

unsigned long long int elevaDois(int vezes)
{
    int i;
    unsigned long long int res = 2;

    if (vezes == 0)
    {
        return 1;
    }

    for (i = 1 ; i < vezes ; i++)
    {
        res = res * 2;
    }

    return res;
}

unsigned long long int elevaReal(unsigned long long int a, unsigned long long int n)
{
    unsigned long long int i, res = a;

    if (n == 0)
    {
        return 1;
    }

    for (i = 1 ; i < n ; i++)
    {
        res = res * a;
    }

    return res;
}

unsigned long long int x(unsigned long long int numero, unsigned long long int N)
{
    unsigned long long int res;
    if (numero == 0)
    {
        return 2;
    }
    else
    {
        res = x(numero - 1, N);
        res *= res;
        return (res - 1) % N;
    }
}

unsigned long long int d(unsigned long long int numero, unsigned long long int N)
{
    return gcd(N, x(2 * numero, N) - x(numero, N));
}

unsigned long long int gcd(unsigned long long int a, unsigned long long int b)
{
    if (a == 0)
    {
        return b;
    }

    return gcd(b % a, a);
}