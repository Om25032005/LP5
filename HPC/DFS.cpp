#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

vector<vector<int>> graph;
vector<int> visited;

void addEdge(int u, int v)
{
    graph[u].push_back(v);
    graph[v].push_back(u);
}

void dfs(int node)
{
    visited[node] = 1;

    cout << node << " ";

    for(int i = 0; i < graph[node].size(); i++)
    {
        int neighbor = graph[node][i];

        if(!visited[neighbor])
        {
            dfs(neighbor);
        }
    }
}

int main()
{
    omp_set_num_threads(4);

    int vertices, edges;

    cout << "Enter number of vertices: ";
    cin >> vertices;

    cout << "Enter number of edges: ";
    cin >> edges;

    graph.resize(vertices);
    visited.resize(vertices, 0);

    cout << "Enter edges:\n";

    for(int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;

        addEdge(u, v);
    }

    cout << "\nDFS Traversal: ";

    double start = omp_get_wtime();

    dfs(0);

    double end = omp_get_wtime();

    cout << "\nExecution Time: "
         << end - start << " seconds\n";

    return 0;
}



//     g++ -fopenmp DFS.cpp -o dfs

//     .\dfs.exe