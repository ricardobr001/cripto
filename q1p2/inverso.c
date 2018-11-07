#include <stdio.h>

int eea(int a, int b);
int inverso(int r0, int r1);

int main()
{
    int a, b;

    scanf("%d %d", &a, &b);

    printf("%d\n", eea(a, b));
    

    return 0;
}

int eea(int a, int b)
{
    int resto, resultado;

    // a = (b * resultado) + resto
    
    // Exemplo
    // gcd(270, 192) -> 270 = (192 * 1) + 78
    // gcd(270, 192) = gcd(192, 78)
    // repete até que o resto seja diferente de 0
    printf("q[i+1]\tr[i]\n");
    while (resto != 0)
    {
        resto = a % b;
        resultado = a / b;
        a = b;
        b = resto;
        printf("%d\t%d\n", resultado, resto);
    }
    
    return a;
}

int inverso(int r0, int r1)
{
    int s0 = 1, s1 = 0, t0 = 0, t1 = 1;
    int i = 1, r, q;
    
    // r1
    
    for ( ; r != 0 ; ++i)
    {
        si = 
    }
}
