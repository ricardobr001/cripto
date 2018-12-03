/* ==========================================================================
 * Universidade Federal de São Carlos - Campus Sorocaba
 * Disciplina: Introdução à Criptografia
 * Profa. Yeda Venturini
 *
 * Homework 07 - ECC
 *
 * Aluno: Ricardo Mendes Leal Junior    RA: 562262
 * Aluno: Matheus Augusto Thomas        RA: 620599
 * ========================================================================== */

#include <stdio.h>

typedef struct ponto
{
    long long int x, y;
} Ponto;

Ponto ecc(int n, long long int a, long long int p, Ponto g);
Ponto somaPontos(Ponto g);
long long int mod(long long int a, long long int m);
Ponto soma(Ponto g, Ponto q, long long int a, long long int primo);
Ponto lambdaUm(Ponto g, Ponto q, long long int a, long long int primo);
Ponto lambdaDois(Ponto g, Ponto q, long long int a, long long int primo, int flagPontoR);
Ponto geraPontoQ(Ponto g, long long int lambda, long long int primo);
Ponto geraPontoR(Ponto g, Ponto q, long long int lambda, long long int primo);

int inverso(int a, int m) 
{ 
    printf("INVERSO: a = %d\n", a);
    a = a%m;
    // printf("INVERSO: a = %d\n", a);
    for (int x=1; x<m; x++)
    {
        if ((a*x) % m == 1)
        {
            return x;
        }
    }
       
    printf("Nao fez o for\n");
    return 0;
}

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
    for (i = 0 ; i < n-1; i++)
    {
        printf("soma! i = %d\n", i);
        res = soma(res, g, a, p);
    }

    return res;
}

long long int mod(long long int a, long long int m)
{
    if(a < 0) {
        return (a % m) + m;
    } else {
        return a % m;
    }
}

Ponto soma(Ponto g, Ponto q, long long int a, long long int primo)
{
    Ponto r;

    // O ponto r depende de algumas condições para ser calculado
    // q(0, 0)
    if (!q.x && !q.y)
    {
        r = g;
    } 
    // g(0, 0)
    else if (!g.x && !g.y)
    {
        r = q;
    }
    // g == -q ou q == -g (- significa inverso!)
    // g = (x, y)
    // -g = (x, ((primo - y) mod primo))
    else if ((g.x == q.x && g.y == mod(primo - q.y, primo)) || (q.x == g.x && q.y == mod(primo - g.y, primo)))
    {
        r.x = 0; r.y = 0;
    }
    // q != +- q
    // q && g != (0,0)
    else if ((q.x != g.x) && (q.y != g.y) && (q.y != (mod(primo - g.y, primo))) && q.x && q.y && g.x && g.y)
    {
        printf("um - qx: %lld qy: %lld gx: %lld gy: %lld mod: %lld\n", q.x, q.y, g.x, g.y, mod(primo - g.y, primo));
        r = lambdaUm(g, q, a, primo);
    }
    else
    {
        printf("dois - qx: %lld qy: %lld gx: %lld gy: %lld mod: %lld\n", q.x, q.y, g.x, g.y,mod(primo - g.y, primo));
        r = lambdaDois(g, q, a, primo, 1);
        // printf("Retorno r\n\n");
    }

    printf("Fim da soma!\n\n");
    return r;
}

Ponto lambdaUm(Ponto g, Ponto q, long long int a, long long int primo)
{
    long long int lambda;

    // Calculo do lambda
    printf("g.x = %lld\tq.x = %lld\n", g.x, q.x);
    long long int x = mod((g.y - q.y), primo);
    long long int y = mod((g.x - q.x), primo);
    int s =  mod((x * (inverso(y, primo))), primo);

    return geraPontoR(g, q, s, primo);
}

Ponto lambdaDois(Ponto g, Ponto q, long long int a, long long int primo, int flagPontoR)
{
    long long int lambda;

    if (flagPontoR)
    {
        // Calculo do lambda
        printf("q.y = %lld\n", q.y);
        int x = mod((3 * (q.x * q.x) + a), primo);
        int y = mod((2 * q.y), primo);

        printf("inverso %d e %lld: %d\n", y, primo,inverso(y,primo));
        printf("x: %d , y: %d\n", x, y);
        int s = mod((x*(inverso(y,primo))), primo) ;

        
        lambda = mod(s, primo);
        printf("lambda = %lld\n", lambda);

        return geraPontoR(g, q, lambda, primo);
    }

    // Calculo do lambda
    lambda = (3 * g.x * g.x) + a;
    lambda = lambda / (2 * g.y);
    lambda = mod(lambda, primo);

    return geraPontoQ(g, lambda, primo);
}

Ponto geraPontoQ(Ponto g, long long int lambda, long long int primo)
{
    Ponto q;

    // Calculo do q.x
    q.x = (lambda * lambda) - (2 * g.x);
    q.x = mod(q.x, primo);

    // Calculo do q.y
    q.y = (lambda * (g.x - q.x)) - g.y;
    q.y = mod(q.y, primo);

    return q;
}

Ponto geraPontoR(Ponto g, Ponto q, long long int lambda, long long int primo)
{
    Ponto r;

    // Calculo do q.x
    r.x = (lambda * lambda) - q.x - g.x;
    r.x = mod(r.x, primo);

    // Calculo do q.y
    r.y = (lambda * (q.x - r.x)) - q.y;
    r.y = mod(r.y, primo);

    printf("rx: %lld, ry: %lld\n", r.x, r.y);
    return r;
}
