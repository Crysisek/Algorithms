#ifndef SIEC_PRZEWODOWA_EXACT_H
#define SIEC_PRZEWODOWA_EXACT_H

#include<bits/stdc++.h>
#include <list>

using namespace std;

class exact
{
    bool graph[31][31];
    bool visited[31][31];
    bool check_cover(int, int, int);

public:
    bool tmp[31];
    exact();
    void add_edge(int, int);
    int vertex_cover(int, int);
};


#endif //SIEC_PRZEWODOWA_EXACT_H
