#ifndef SIEC_PRZEWODOWA_APPROXIMATELY_H
#define SIEC_PRZEWODOWA_APPROXIMATELY_H

#include <list>
#include <fstream>

using namespace std;

class approximately
{
    int vertices;
    list<int> *adjacency_list;

public:
    explicit approximately(int);
    void add_edge(int, int);
    void vertex_cover();
};


#endif //SIEC_PRZEWODOWA_APPROXIMATELY_H
