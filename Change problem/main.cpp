#include <iostream>
#include <fstream>

using namespace std;

bool used(int, int, int*, int*, int*);

int main()
{
    ifstream in("PKO_in_Kalinowski_9.txt");
    if(!in.is_open())
    {
        return 1;
    }

    int n, k;
    int* nominaly;
    int* liczebnosc;
    int* uzytych;
    int* min_banknotow;
    int* pomocnicze;

    in >> n;
    nominaly = new int[n];
    liczebnosc = new int[n];
    pomocnicze = new int[n];

    for(int i = 0; i < n; i++)
    {
        in >> nominaly[i];
    }

    for(int i = 0; i < n; i++)
    {
        in >> liczebnosc[i];
    }

    in >> k;
    min_banknotow = new int[k + 1];
    uzytych = new int[k + 1];

    in.close();

    fill(min_banknotow, min_banknotow+(k + 1), k + 1);
    min_banknotow[0] = 0;
    int sum = 0;
    for(int i = n - 1; i > -1; i--)                         // Tmax = m * k, gdzie m - ilość banknotów, k - kwota do wydania
    {
        sum += nominaly[i] * liczebnosc[i];
        for(int j = nominaly[i]; j <= sum && j <= k; j++)
        {
            if(min_banknotow[j] > min_banknotow[j - nominaly[i]] + 1 && used(j - nominaly[i], i, uzytych, nominaly, liczebnosc))
            {
                min_banknotow[j] = min_banknotow[j - nominaly[i]] + 1;
                uzytych[j] = nominaly[i];
            }
        }
    }

    int j = k;
    while(j != 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (uzytych[j] == nominaly[i])
            {
                pomocnicze[i]++;
                j -= uzytych[j];
            }
        }
    }

    ofstream out("PKO_out_Kalinowski_9.txt");
    out << min_banknotow[k] << endl;
    for(int i = 0; i < n; i++)
    {
        out << pomocnicze[i] << " ";
    }
    out.close();

    delete [] min_banknotow;
    delete [] nominaly;
    delete [] liczebnosc;
    delete [] uzytych;
    delete [] pomocnicze;
    return 0;
}

bool used(int x, int i, int *uzytych, int *nominaly, int *liczebnosc)
{
    int zlicz = 0;
    while(uzytych[x] != 0)
    {
        if (uzytych[x] == nominaly[i])
            zlicz++;
        x -= uzytych[x];
    }
    return  !(zlicz == liczebnosc[i]);
}