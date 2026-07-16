#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

class Graph
{
    int v;
    list<int> *l;

public:
    Graph(int v)
    {
        this->v = v;
        l = new list<int>[v];
    }

    void addEdge(int u, int v)
    {
        l[u].push_back(v);
        l[v].push_back(u);
    }
    void bfs()
    {
        queue<int> q;
        vector<bool> vis(v, false);
        q.push(0);
        vis[0] = true;

        while (q.size() > 0)
        {
            int u = q.front();
            q.pop();
            cout << u << " ";

            for (int v : l[u])
            {
                if (!vis[v])
                {
                    vis[v] = true;
                    q.push(v);
                }
            }
        }

        cout << endl;
    }

    void dfshelper(int u, vector<bool>&vis){
        cout << u << " ";
        vis[u] = true;
        for(int v: l[u]){
            if(!vis[v]){
                dfshelper(v, vis);
            }
        }
    }
    void dfs(){
        int src = 0;
        vector<bool> vis(v, false);
        dfshelper(src, vis);
        cout << endl;
    }
};

int main()
{
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);

    cout << "dfs:";
    g.dfs();

    cout << "bfs:";
    g.bfs();
    return 0;
}