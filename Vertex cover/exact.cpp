#include "exact.h"

exact::exact()
{
    memset(graph, false, sizeof graph);
}

void exact::add_edge(int v, int u)
{
    graph[v][u] = true;
}

int exact::vertex_cover(int n, int m)
{
    int left = 1, right = n;
    while(right > left)
    {
        int mid = (left + right) / 2;
        if(check_cover(n, mid, m))
            right = mid;
        else
            left = mid + 1;
    }
    return right;
}

bool exact::check_cover(int V, int k, int E)
{
    /* Gosper’s Hack */
    int set = (1 << k) - 1;
    int limit = (1 << V);
    int temp[31];
    while(set < limit)
    {
        memset(visited, false, sizeof visited);
        memset(temp, false, sizeof temp);
        short int counter = 0;

        for(int i = 1, v = 1; i < limit; i = i << 1, v++)
        {
            if(set & i)
            {
                for(k = 1; k <= V; k++)
                {
                    if(graph[v][k] && !visited[v][k])
                    {
                        visited[v][k] = true;
                        visited[k][v] = true;
                        counter++;
                        temp[v] = true;
                    }
                }
            }
        }

        if(counter == E)
        {
            for(int i = 1; i <= V; i++)
                tmp[i] = temp[i];
            return true;
        }

        int c = set & -set;
        int r = set + c;
        set = (((r ^ set) >> 2) / c) | r;
    }
    return false;
}

