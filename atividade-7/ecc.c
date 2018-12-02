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

long long int mod(long long int a, long long int m) {
    if(a < 0) {
        return (a % m) + m;
    } else {
        return a % m;
    }
}

int inverso(int a, int m) 
{ 
    a = a%m; 
    for (int x=1; x<m; x++) 
       if ((a*x) % m == 1) 
          return x; 
} 

void toBinValue(unsigned int in, int count, int* out)
{
    unsigned int mask = 1U << (count-1);
    int i;
    for (i = 0; i < count; i++) {
        out[i] = (in & mask) ? 1 : 0;
        in <<= 1;
    }
}

int size(unsigned int n) {
    int size = 0;
    while(n != 0) {
        n = n/2;
        size++;
    }

    return size;
}

int doubleLambda(Ponto p, long long int a, long long int prime) {

    int x = mod((3*(p.x * p.x)+a) , prime);
    int y = mod((2*p.y) , prime);

    printf("inverso %d e %lld: %d\n", y, prime,inverso(y,prime));

    int s = mod((x*(inverso(y,prime))), prime) ;

    printf("Doub s: %d\n", s);
    return s;
}

int addLambda(Ponto p, Ponto q, int prime) {

    long long int x = mod((q.y - p.y),prime);
    long long int y = mod((q.x - p.x),prime);
    int s =  mod((x*(inverso(y,prime))), prime);

    printf("x: %lld, y:%lld\n", x, y);

    printf("Add s: %d\n", s);
    return s;
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

Ponto generatePoint(Ponto p, Ponto q, int s, long long int prime) {
    Ponto newPoint;

    newPoint.x = mod(((s*s) - p.x - q.x), prime);
    newPoint.y = mod(((s*(p.x - newPoint.x)) - p.y),prime);

    return newPoint;
}

Ponto ecc(int n, long long int a, long long int p, Ponto g)
{
    int i, s, binValue[32];

    toBinValue(n, size(n), binValue);
    Ponto T = g;

    // Efetua a soma n vezes
    for (i = 1 ; i < size(n) ; i++)
    {
        printf("Number: %d\n", binValue[i]);
        s = doubleLambda(T, a, p);
        T = generatePoint(T, T, s, p);
        printf("px: %lld py: %lld\n", T.x, T.y);
        if(binValue[i] == 1) {
            s = addLambda(T, g, p);
            T = generatePoint(T, g, s, p);
        }
    }

    return T;
}

