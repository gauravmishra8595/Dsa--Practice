#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    int V;
    vector<vector<pair<int, int>>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // u -> v with weight wt
    void addEdge(int u, int v, int wt) {
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});   // Remove this line for directed graph
    }

    void dijkstra(int src) {
        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> pq;

        vector<int> dist(V, 1e9);

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {

            int currDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (currDist > dist[node])
                continue;

            for (auto edge : adj[node]) {

                int neigh = edge.first;
                int wt = edge.second;

                if (dist[node] + wt < dist[neigh]) {

                    dist[neigh] = dist[node] + wt;
                    pq.push({dist[neigh], neigh});
                }
            }
        }

        cout << "Shortest distances from source " << src << ":\n";

        for (int i = 0; i < V; i++) {
            cout << src << " -> " << i << " = " << dist[i] << endl;
        }
    }
};

int main() {

    Graph g(5);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 1);

    g.dijkstra(0);

    return 0;
}