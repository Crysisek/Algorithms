#include "approximately.h"


approximately::approximately(int V): vertices(V)
{
    adjacency_list = new list<int>[V];
}

void approximately::add_edge(int v, int w)
{
    adjacency_list[v].push_back(w);
}

void approximately::vertex_cover()
{
    bool visited[vertices];
    for(int i = 1; i < vertices; i++)
        visited[i] = false;

    list<int>::iterator i;
    int counter = 0;

    for(int j = 1; j < vertices; j++)
    {
        if(!visited[j])
        {
            for(i = adjacency_list[j].begin(); i != adjacency_list[j].end(); i++)
            {
                int v = *i;

                if(!visited[v])
                {
                    visited[v] = true;
                    visited[j] = true;
                    counter += 2;
                    break;
                }
            }
        }
    }

    ofstream out("Siec_Kalinowski_9_out.txt");
    out << counter << endl;

    for(int p = 1; p < vertices; p++)
        if(visited[p])
            out << p << " ";

    out.close();
}
