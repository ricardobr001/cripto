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

/* Função que calcula o valor de phi para dois primos p e q */
unsigned long long int phi(unsigned long long int p, unsigned long long int q)
{
    return (p - 1) * (q - 1);
}

/* Função que quebra o RSA, encontrando os dois primos que formam N
 * Depois encontra a chave privada e descriptografa o mensagem
 */
void breakRSA(unsigned long long int produtoPrimos, unsigned long long int chavePub, unsigned long long int mensagem)
{
    unsigned long long int i = 1, primeiroPrimo, segundoPrimo, resPhi, chavePriv;

    primeiroPrimo = d(i, produtoPrimos); // Chamando a função d para i = 1

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
            primeiroPrimo = d(i, produtoPrimos); // Para i > 1
        }
    }

    // Para encontrar o segundo primo, basta dividir o produto dos primos pelo primeiro primo, assim teremos o segundo
    segundoPrimo = produtoPrimos / primeiroPrimo;
    resPhi = phi(primeiroPrimo, segundoPrimo); // Calculando o phi do primeiro e segundo primo
    chavePriv = inversoModular(chavePub, resPhi); // encontrando a chave privada (inverso modular do resultado da função phi)

    // printf("primo 1 = %lld\tprimo 2 = %lld\n", primeiroPrimo, segundoPrimo);
    // printf("totien = %lld\n", resPhi);

    // Descriptografando a mensagem
    printf("%lld\n", eleva(mensagem, chavePriv, produtoPrimos));
}

unsigned long long int inversoModular(unsigned long long int a, unsigned long long int p)
{
    unsigned long long novo = 1, velho = 0, q = p, r, h;
    int pos = 0;

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

    if (pos)
    {
        return velho;
    }
    else
    {
        return p - velho;
    }
}

unsigned long long int eleva(unsigned long long int num, unsigned long long int vezes, unsigned long long int mod)
{
    unsigned long long int i;
    unsigned long long int res = num;
    // printf("m = %lld, priv = %lld, mod = %lld\n", num, vezes, mod);

    if (vezes == 0)
    {
        return 1;
    }

    for (i = 1 ; i < vezes ; i++)
    {
        res = res * num;
        res = res % mod;
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