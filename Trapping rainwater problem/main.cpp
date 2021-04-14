#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct vertex
{
    int x, y, h;

    vertex(){}
    vertex(int a, int b, int c)
    {
        x = a;
        y = b;
        h = c;
    }

    bool operator <(const vertex &v)const
    {
        return h > v.h;
    }
};


int main()
{
    ifstream in("Pot_in_9_Kalinowski.txt");
    ofstream out("Pot_out_9_Kalinowski.txt");

    int n, m, volume = 0;
    in >> n >> m;

    int **height = new int*[n];
    bool **visited = new bool*[n];
    for(int i = 0; i < n; i++)
    {
        height[i] = new int[m];
        visited[i] = new bool[m];
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
        {
            in >> height[i][j];
        }

    priority_queue<vertex> p_queue;

    // add borders to the queue
    /* left to right */
    for(int i = 0; i < n; i++)
    {
        visited[i][0] = true;
        visited[i][m - 1] = true;
        p_queue.push(vertex(i, 0, height[i][0]));
        p_queue.push(vertex(i, m - 1, height[i][m - 1]));
    }

    /* top to bottom */
    for(int i = 1; i < m - 1; i++)
    {
        visited[0][i] = true;
        visited[n - 1][i] = true;
        p_queue.push(vertex(0, i, height[0][i]));
        p_queue.push(vertex(n - 1, i, height[n - 1][i]));
    }

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // if the neighbor is shorter, collect the water it can trap and update its height as its height + water trapped
    // BFS
    while(!p_queue.empty())
    {
        vertex ver = p_queue.top(); p_queue.pop();

        for(int i = 0; i < 4; i++)
        {
            int x = ver.x + dx[i];
            int y = ver.y + dy[i];
            if(x >= 0 && x < n && y >= 0 && y < m && !visited[x][y])
            {
                visited[x][y] = true;
                volume += max(0, ver.h - height[x][y]);
                p_queue.push(vertex(x, y, max(height[x][y], ver.h)));
            }
        }
    }

    out << volume << endl;  // Tmax = O(mn*(logmn))  pamiec = O(mn)

    in.close();
    out.close();
    return 0;
}