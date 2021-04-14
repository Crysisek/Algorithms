#include <stdio.h>
#include <stdlib.h>

typedef struct dane
{
    int pole;
    int* pointer;
}dane;

int k_ty_iteracyjnie(dane *, int, int , int );
int k_ty_rekurencyjnie(dane *, int, int , int );

void swap(dane*, int, int);
int mediana(dane*, int, int);
int partition(dane*, int, int, int);

int main()
{
    FILE *in = fopen("DK_in_9_Kalinowski.txt", "r");
    if(in == NULL)
        return 1;


    int n, k;
    fscanf(in, "%d", &n);
    int *wspolrzedne = malloc(n * sizeof(dane));
    dane *tablica = malloc(n * sizeof(dane));
    for(int i = 0, j = 0; i < n; i++, j += 4)
    {
        fscanf(in, "%d%d%d%d", &wspolrzedne[j], &wspolrzedne[j + 1], &wspolrzedne[j + 2], &wspolrzedne[j + 3]);
        tablica[i].pole = (wspolrzedne[j + 2] - wspolrzedne[j]) * (wspolrzedne[j + 3] - wspolrzedne[j + 1]);
        tablica[i].pointer = &wspolrzedne[j];
    }
    fscanf(in, "%d", &k);
    fclose(in);


    FILE *out = fopen("DK_out_9_Kalinowski.txt", "w");
    if(out == NULL)
        return 1;

    //int index = k_ty_iteracyjnie(tablica, 0, n - 1, k - 1);
    int index = k_ty_rekurencyjnie(tablica, 0, n - 1, k - 1);
    for(int i = 0; i < 4; i++)
    {
        fprintf(out, "%d ", *(tablica[index].pointer + i));
    }

    fclose(out);

    return 0;
}

int k_ty_iteracyjnie(dane *tab, int pocz, int kon, int k) // Tmax = n (n^2 jezeli najmniejszy/najwiekszy pivot)
{
    while(pocz <= kon)
    {
        int pivot_index = mediana(tab, pocz, kon);
        int sr = partition(tab, pocz, kon, pivot_index);

        if(sr == k)
            return sr;
        else if(sr > k)
            kon = sr - 1;
        else
            pocz = sr + 1;
    }
}

int k_ty_rekurencyjnie(dane *tab, int pocz, int kon, int k) // Tmax = n (n^2 jezeli najmniejszy/najwiekszy pivot)
{
    if(pocz < kon)
    {
        int pivot_index = mediana(tab, pocz, kon);
        int sr = partition(tab, pocz, kon, pivot_index);

        if(sr == k)
            return sr;
        else if(sr > k)
            return k_ty_rekurencyjnie(tab, pocz, sr - 1, k);
        else
            return k_ty_rekurencyjnie(tab, sr + 1, kon, k);
    }
}

int partition(dane *tab, int pocz, int kon, int pivot_index)
{
    int pivot = tab[pivot_index].pole;
    int docelowe = pocz;

    swap(tab, pivot_index, kon);

    for(int i = pocz; i < kon; i++)
    {
        if(tab[i].pole < pivot)
        {
            swap(tab, i, docelowe);
            docelowe++;
        }
    }

    swap(tab, kon, docelowe);

    return docelowe;
}

void swap(dane *tab, int l, int p)
{
    int temp1 = tab[l].pole;
    int *temp2 = tab[l].pointer;
    tab[l].pole = tab[p].pole;
    tab[l].pointer = tab[p].pointer;
    tab[p].pole = temp1;
    tab[p].pointer = temp2;
}


int mediana(dane *tab, int p, int k)
{
    int s = (k + p) / 2;
    if((tab[p].pole < tab[k].pole && tab[k].pole < tab[s].pole)
    || (tab[s].pole < tab[k].pole && tab[k].pole < tab[p].pole))
        return k;
    else if((tab[k].pole < tab[p].pole && tab[p].pole < tab[s].pole)
    || (tab[s].pole < tab[p].pole && tab[p].pole < tab[k].pole))
        return p;
    else
        return s;
}