#include "exact.h"
#include "approximately.h"
#include <string>
#include <sstream>

using namespace std;

int main()
{
    fstream in("Siec_Kalinowski_9_in.txt");
    int n, number_of_edges = 0;
    string line;
    getline(in, line);
    n = stoi(line);
    approximately network_apx(n + 1);
    exact network_ext;

    for(int i = 1; i <= n; i++)
    {
        getline(in, line);
        istringstream ss(line);
        int x;
        while(ss >> x)
        {
            network_apx.add_edge(i, x);
            network_ext.add_edge(i, x);
            number_of_edges++;
        }
    }
    in.close();

    cout << network_ext.vertex_cover(n, number_of_edges / 2) << endl;   // Tmax = E * (Cv/2 + Cv/4 + ... + Ck)
     for(int i = 1; i <= n; i++)
        if(network_ext.tmp[i])
            cout << i << " ";

    network_apx.vertex_cover();     // Tmax = V + E

    return 0;
}
