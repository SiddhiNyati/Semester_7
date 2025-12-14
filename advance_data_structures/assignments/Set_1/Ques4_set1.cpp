#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

bool bfs(vector<vector<int>>& rGraph, int s, int t,
         vector<int>& parent, int V) {

    vector<bool> visited(V, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; v++) {
            if (!visited[v] && rGraph[u][v] > 0) {
                parent[v] = u;
                visited[v] = true;
                q.push(v);
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

void dfsMinCut(vector<vector<int>>& rGraph, int s,
               vector<bool>& visited, int V) {
    visited[s] = true;
    for (int v = 0; v < V; v++) {
        if (rGraph[s][v] > 0 && !visited[v])
            dfsMinCut(rGraph, v, visited, V);
    }
}

int main() {
    int V;
    cout << "Enter number of vertices: ";
    cin >> V;

    vector<vector<int>> graph(V, vector<int>(V));

    cout << "Enter adjacency matrix (capacities):\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            cin >> graph[i][j];

    int source, sink;
    cout << "Enter source vertex: ";
    cin >> source;
    cout << "Enter sink vertex: ";
    cin >> sink;

    vector<vector<int>> rGraph = graph;
    vector<int> parent(V);
    int maxFlow = 0;
    int step = 1;

    cout << "\nAugmenting Paths and Flow Updates:\n";

    while (bfs(rGraph, source, sink, parent, V)) {

        int pathFlow = INT_MAX;
        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            pathFlow = min(pathFlow, rGraph[u][v]);
        }

        cout << "Step " << step++ << " Path: ";
        for (int v = sink; v != -1; v = parent[v])
            cout << v << " ";
        cout << "| Flow Added = " << pathFlow << endl;

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= pathFlow;
            rGraph[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
        cout << "Current Max Flow = " << maxFlow << "\n\n";
    }

    cout << "Final Maximum Flow = " << maxFlow << endl;

    vector<bool> visited(V, false);
    dfsMinCut(rGraph, source, visited, V);

    cout << "\nMinimum Cut Edges:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (visited[i] && !visited[j] && graph[i][j] > 0)
                cout << i << " -> " << j << endl;
        }
    }

    return 0;
}
