#include <stdio.h>

int eea(int a, int b);
void invert_mod(int a, int p);

int main()
{
    int a, b, r;

    scanf("%d %d", &a, &b);

    invert_mod(a, b);

    return 0;
}

int eea(int a, int b)
{
    int resto = -1, resultado;

    // a = (b * resultado) + resto
    
    // Exemplo
    // gcd(270, 192) -> 270 = (192 * 1) + 78
    // gcd(270, 192) = gcd(192, 78)
    // repete até que o resto seja diferente de 0
    while (resto != 0)
    {
        
        resto = a % b;
        resultado = a / b;
        a = b;
        b = resto;
    }
    
    return a;
}

void invert_mod(int a, int p)
{
    int new = 1, old = 0, q = p, r, h;
    int pos = 0;

    while (a > 0)
    {
        r = q % a;
        q = q / a;
        h = q * new + old;
        old = new;
        new = h;
        q = a;
        a = r;
        pos = !pos;
    }

    if (pos)
    {
        printf("%d N\n", q);
    }
    else
    {
        printf("%d %d\n", q, (p - old));
    }
}
