#include <stdio.h>
#include <math.h>

typedef unsigned long long int max_int;

max_int silnia(max_int);
max_int algorytm_naiwny(int, int);
max_int algorytm_optymalny(int, int);
max_int algorytm_z_uzyciem_logarytmow(int, int);



int main()
{
    FILE *in = fopen("in_A_9_Kalinowski.txt", "r");
    if (in == NULL)
    {
        printf("Nie udalo sie otworzyc pliku.");
        return 1;
    }

    int n;
    int m;
    fscanf(in, "%d%d", &n, &m);
    fclose(in);

    FILE *out = fopen("out_A_9_Kalinowski.txt", "w");
    if (out == NULL)
    {
        printf("Nie udalo sie otworzyc pliku.");
        return 1;
    }

    fprintf(out, "%llu\n\n", algorytm_naiwny(n, m));
    fprintf(out, "%llu\n\n", algorytm_optymalny(n, m));
    fprintf(out, "%llu", algorytm_z_uzyciem_logarytmow(n, m));
    fclose(out);

    return 0;
}

max_int algorytm_naiwny(int n, int m) // Tmax = 2n - 1
{
    if(n == m || m == 0 || n > 20)
        return 1;
    return silnia(n) / (silnia(n - m) * silnia(m));
}

max_int algorytm_optymalny(int n, int m) // Tmax = 2m - 2
{
    if(n == m || m == 0)
        return 1;
    max_int wynik = (n - m > m) ? (n - m + 1) : (m + 1);
    for(int i = wynik + 1, j = 2; i <= n; i++, j++)
    {
        wynik *= i;
        wynik /= j;
    }
    return wynik;
}

max_int algorytm_z_uzyciem_logarytmow(int n, int m) // Tmax =  2m - 2 + 2r | r - czas oblicznia log
{
    if(n == m || m == 0)
        return 1;
    int i;
    long double wynik;
    if(n - m > m)
    {
        wynik = log(n - m + 1);
        i = n - m + 2;
    }
    else
    {
        wynik = log(m + 1);
        i = m + 2;
    }
    for(int j = 2; i <= n; i++, j++)
    {
        wynik += log(i);
        wynik -= log(j);
    }
    return roundl(expl(wynik));
}

max_int silnia(max_int k)
{
    for(int i = k - 1; i > 1; i--)
    {
        k *= i;
    }
    return k;
}

